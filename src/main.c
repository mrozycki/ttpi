/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *                    sekigon-gonnoc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

// This example runs both host and device concurrently. The USB host receive
// reports from HID device and print it out over USB Device CDC interface.
// For TinyUSB roothub port0 is native usb controller, roothub port1 is
// pico-pio-usb.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "bsp/board_api.h"
#include "class/hid/hid.h"
#include "hardware/clocks.h"
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/bootrom.h"

#include "pio_usb.h"
#include "tusb.h"
#include "keymap.h"

#define UART_ID uart0
#define BAUD_RATE 1200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY UART_PARITY_NONE

#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define UART_CTS_PIN 2

static uint8_t leds = KEYBOARD_LED_NUMLOCK;
static uint8_t prev_leds = 0xFF;

static uint8_t keybd_dev_addr = 0xFF;
static uint8_t keybd_instance;

typedef enum {
  WRITING,
  CORRECTING  
} direction;

static void set_direction(direction new_direction) {
  static direction previous_direction = false;

  if (new_direction == CORRECTING && previous_direction == WRITING) {
    printf("now correcting\n");
    uart_putc(UART_ID, TW_CORRECTING);
    uart_putc(UART_ID, TW_BACKWARDS);
    previous_direction = new_direction;
  } else if (new_direction == WRITING && previous_direction == CORRECTING) {
    printf("now writing\n");
    uart_putc(UART_ID, TW_WRITING);
    uart_putc(UART_ID, TW_FORWARDS);
    previous_direction = new_direction;
  }
}

static bool print_char_to_typewriter(uint8_t iso_code) {
  printf("%c\n", iso_code);
  bool printed = false;

  uint8_t const table_size = sizeof(iso2erika[iso_code]) / sizeof(iso2erika[iso_code][0]);
  for (uint8_t i = 0; i < table_size; ++i) {
    uint8_t const ch = iso2erika[iso_code][table_size - i - 1];
    if (ch == 0)
      continue;
    printf("print me pls %d", ch);
    uart_putc(UART_ID, ch);
    printed = true;
  }
  
  return printed;
}

static void print_char_to_tty(uint8_t iso_code) {
  tud_cdc_write_char(iso_code);
  tud_cdc_write_flush();
}

/*------------- MAIN -------------*/

void hid_app_task(void)
{
  // update keyboard leds
  if (keybd_dev_addr != 0xFF)
  { // only if keyboard attached
    if (leds != prev_leds)
    {
      tuh_hid_set_report(keybd_dev_addr, keybd_instance, 0, HID_REPORT_TYPE_OUTPUT, &leds, sizeof(leds));
      prev_leds = leds;
    }
  }
}

void core1_main() {
  sleep_ms(10);

  tud_init(0);
  while (true) {
    tud_task();
    tud_cdc_write_flush();
  }
}

int main(void)
{
  // default 125MHz is not appropreate. Sysclock should be multiple of 12MHz.
  set_sys_clock_khz(120000, true);

  sleep_ms(10);
  
  multicore_reset_core1();
  multicore_launch_core1(core1_main);

  board_init();
  stdio_init_all();

  // Use tuh_configure() to pass pio configuration to the host stack
  // Note: tuh_configure() must be called before
  pio_usb_configuration_t pio_cfg = PIO_USB_DEFAULT_CONFIG;
  pio_cfg.pin_dp = 16;
  tuh_configure(1, TUH_CFGID_RPI_PIO_USB_CONFIGURATION, &pio_cfg);

  uart_init(UART_ID, BAUD_RATE);
  gpio_set_function(UART_TX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_TX_PIN));
  gpio_set_function(UART_RX_PIN, UART_FUNCSEL_NUM(UART_ID, UART_RX_PIN));
  gpio_set_function(UART_CTS_PIN, GPIO_FUNC_UART);
  uart_set_baudrate(UART_ID, BAUD_RATE);
  uart_set_hw_flow(UART_ID, true, false);
  uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
  uart_set_fifo_enabled(UART_ID, false);

  uart_putc(UART_ID, TW_WRITING);
  uart_putc(UART_ID, TW_FORWARDS);

  // To run USB SOF interrupt in core1, init host stack for pio_usb (roothub
  // port1) on core1
  tuh_init(1);

  while (true)
  {
    tuh_task(); // tinyusb host task
    hid_app_task();
  }

  return 0;
}

//--------------------------------------------------------------------+
// Device CDC
//--------------------------------------------------------------------+

// Invoked when CDC interface received data from host
void tud_cdc_rx_cb(uint8_t itf)
{
  (void) itf;

  char buf[64];
  uint32_t count = tud_cdc_read(buf, sizeof(buf));
  set_direction(WRITING);
  for (uint32_t i = 0; i < count; ++i) {
    print_char_to_typewriter(buf[i]);
  }

  // TODO control LED on keyboard of host stack
  (void) count;
}

//--------------------------------------------------------------------+
// Host HID
//--------------------------------------------------------------------+

// Invoked when device with hid interface is mounted
// Report descriptor is also available for use. tuh_hid_parse_report_descriptor()
// can be used to parse common/simple enough descriptor.
// Note: if report descriptor length > CFG_TUH_ENUMERATION_BUFSIZE, it will be skipped
// therefore report_desc = NULL, desc_len = 0
void tuh_hid_mount_cb(uint8_t dev_addr, uint8_t instance, uint8_t const *desc_report, uint16_t desc_len)
{
  (void)desc_report;
  (void)desc_len;

  // Interface protocol (hid_interface_protocol_enum_t)
  const char *protocol_str[] = {"None", "Keyboard", "Mouse"};
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  uint16_t vid, pid;
  tuh_vid_pid_get(dev_addr, &vid, &pid);

  printf("[%04x:%04x][%u] HID Interface%u, Protocol = %s\r\n", vid, pid, dev_addr, instance, protocol_str[itf_protocol]);

  // Receive report from boot keyboard only
  // tuh_hid_report_received_cb() will be invoked when report is available
  if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD)
  {
    // Turn off keyboard LEDs
    tuh_hid_set_report(dev_addr, instance, 0, HID_REPORT_TYPE_OUTPUT, &leds, sizeof(leds));
    prev_leds = leds;

    keybd_dev_addr = dev_addr;
    keybd_instance = instance;
    uart_putc(UART_ID, 0x91);
    
    if (!tuh_hid_receive_report(dev_addr, instance))
    {
      printf("Error: cannot request report\r\n");
    }
  }
}

// Invoked when device with hid interface is un-mounted
void tuh_hid_umount_cb(uint8_t dev_addr, uint8_t instance)
{
  uart_putc(UART_ID, 0x92);
  printf("[%u] HID Interface%u is unmounted\r\n", dev_addr, instance);
  keybd_dev_addr = 0xFF;
}

// look up new key in previous keys
static inline bool find_key_in_report(hid_keyboard_report_t const *report, uint8_t keycode)
{
  for (uint8_t i = 0; i < 6; i++)
  {
    if (report->keycode[i] == keycode)
      return true;
  }

  return false;
}

// convert hid keycode to ascii and print via usb device CDC (ignore non-printable)
static void process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report)
{
  (void)dev_addr;
  static hid_keyboard_report_t prev_report = {0, 0, {0}}; // previous report to check key released
  static bool caps_lock = false;
  static uint8_t line_buffer[150];
  static uint8_t line_position = 0;
  static uint8_t line_end = 0;
  bool flush = false;

  for (uint8_t i = 0; i < 6; i++)
  {
    uint8_t keycode = report->keycode[i];
    if (keycode)
    {
      if (find_key_in_report(&prev_report, keycode))
      {
        // exist in previous report means the current key is holding
      }
      else if (keycode == KC_CAPS_LOCK)
      {
        caps_lock = !caps_lock;
        leds ^= KEYBOARD_LED_CAPSLOCK;
      }
      else if (keycode == KC_BACKSPACE && line_position > 0)
      {
        if (line_position == line_end) {
          --line_end;
        }
        uint8_t iso = line_buffer[--line_position];
        set_direction(CORRECTING);
        print_char_to_typewriter(iso);
        line_buffer[line_position] = ' ';
        flush = true;
      }
      else if (keycode == KC_ESCAPE) {
        while (line_position != line_end) {
          set_direction(WRITING);
          uart_putc(UART_ID, TW_SPACE);
          ++line_position;
        }
      }
      else
      {
        // not existed in previous report means the current key is pressed
        bool const is_alpha = keycode >= KC_A && keycode <= KC_Z;
        bool const is_shift = report->modifier & (KEYBOARD_MODIFIER_LEFTSHIFT | KEYBOARD_MODIFIER_RIGHTSHIFT) || (is_alpha && caps_lock);
        bool const is_alt = report->modifier & KEYBOARD_MODIFIER_RIGHTALT;
        uint8_t const iso = keycode2iso[keycode][is_shift + 2 * is_alt];
        
        if (iso)
        {
          if (line_position == line_end) {
            ++line_end;
          }
          line_buffer[line_position++] = iso;
          set_direction(WRITING);
          if (print_char_to_typewriter(iso))
            print_char_to_tty(iso);

          flush = true;

          if (iso == '\n') {
            line_position = 0;
            line_end = 0;
          }

          continue;
        }

        uint8_t const special_key = special_keycode2erika[keycode];
        if (special_key)
        {
          printf("special key: %d\n", special_key);
          set_direction(WRITING);
          uart_putc(UART_ID, special_key);
        }
        if (keycode == KC_LEFT && line_position > 0) {
          --line_position;
        } else if (keycode == KC_RIGHT) {
          if (line_position == line_end) {
            line_buffer[line_position++] = ' ';
            ++line_end;
          } else {
            ++line_position;
          }
        }
      }
    }
    // TODO example skips key released
  }

  if (flush)
    printf("\n");

  prev_report = *report;
}

// Invoked when received report from device via interrupt endpoint
void tuh_hid_report_received_cb(uint8_t dev_addr, uint8_t instance, uint8_t const *report, uint16_t len)
{
  (void)len;
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  switch (itf_protocol)
  {
  case HID_ITF_PROTOCOL_KEYBOARD:
    process_kbd_report(dev_addr, (hid_keyboard_report_t const *)report);
    break;

  default:
    break;
  }

  // continue to request to receive report
  if (!tuh_hid_receive_report(dev_addr, instance))
  {
    printf("Error: cannot request report\r\n");
  }
}
