#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdbool.h>
#include <stdint.h>

// ISO 8859-2
#define A_OGONEK_LOWER 0xB1
#define A_OGONEK_UPPER 0xA1
#define C_KRESKA_LOWER 0xE6
#define C_KRESKA_UPPER 0xC6
#define E_OGONEK_LOWER 0xEA
#define E_OGONEK_UPPER 0xCA
#define L_KRESKA_LOWER 0xB3
#define L_KRESKA_UPPER 0xA3
#define N_KRESKA_LOWER 0xF1
#define N_KRESKA_UPPER 0xD1
#define O_KRESKA_LOWER 0xF3
#define O_KRESKA_UPPER 0xD3
#define S_KRESKA_LOWER 0xB6
#define S_KRESKA_UPPER 0xA6
#define Z_KRESKA_LOWER 0xBC
#define Z_KRESKA_UPPER 0xAC
#define Z_KROPKA_LOWER 0xBF
#define Z_KROPKA_UPPER 0xAF
#define SECTION_SIGN 0xA7
#define DEGREE_SIGN 0xB0
#define BACKSPACE 0x08

#define KC_A 0x04
#define KC_Z 0x1d

static uint8_t const keycode2iso[128][4] = {
    [0x04] = {'a', 'A', A_OGONEK_LOWER, A_OGONEK_UPPER},
    [0x05] = {'b', 'B', 'b', 'B'},
    [0x06] = {'c', 'C', C_KRESKA_LOWER, C_KRESKA_UPPER},
    [0x07] = {'d', 'D', 'd', 'D'},
    [0x08] = {'e', 'E', E_OGONEK_LOWER, E_OGONEK_UPPER},
    [0x09] = {'f', 'F', 'f', 'F'},
    [0x0a] = {'g', 'G', 'g', 'G'},
    [0x0b] = {'h', 'H', 'h', 'H'},
    [0x0c] = {'i', 'I', 'i', 'I'},
    [0x0d] = {'j', 'J', 'j', 'J'},
    [0x0e] = {'k', 'K', 'k', 'K'},
    [0x0f] = {'l', 'L', L_KRESKA_LOWER, L_KRESKA_UPPER},
    [0x10] = {'m', 'M', 'm', 'M'},
    [0x11] = {'n', 'N', N_KRESKA_LOWER, N_KRESKA_UPPER},
    [0x12] = {'o', 'O', O_KRESKA_LOWER, O_KRESKA_UPPER},
    [0x13] = {'p', 'P', 'p', 'P'},
    [0x14] = {'q', 'Q', 'q', 'Q'},
    [0x15] = {'r', 'R', 'r', 'R'},
    [0x16] = {'s', 'S', S_KRESKA_LOWER, S_KRESKA_UPPER},
    [0x17] = {'t', 'T', 't', 'T'},
    [0x18] = {'u', 'U', 'u', 'U'},
    [0x19] = {'v', 'V', 'v', 'V'},
    [0x1a] = {'w', 'W', 'w', 'W'},
    [0x1b] = {'x', 'X', Z_KRESKA_LOWER, Z_KRESKA_UPPER},
    [0x1c] = {'y', 'Y', 'y', 'Y'},
    [0x1d] = {'z', 'Z', Z_KROPKA_LOWER, Z_KROPKA_UPPER},
    [0x1e] = {'1', '!', '1', '!'},
    [0x1f] = {'2', '@', '2', '@'},
    [0x20] = {'3', '#', '3', '#'},
    [0x21] = {'4', '$', '4', '$'},
    [0x22] = {'5', '%', '5', '%'},
    [0x23] = {'6', '^', '6', '^'},
    [0x24] = {'7', '&', '7', '&'},
    [0x25] = {'8', '*', '8', '*'},
    [0x26] = {'9', '(', '9', '('},
    [0x27] = {'0', ')', '0', ')'},
    [0x28] = {'\n', '\n', '\n', '\n'},
    [0x29] = {0, 0, 0, 0}, // Escape
    [0x2a] = {'\b', '\b', '\b', '\b'},
    [0x2b] = {'\t', '\t', '\t', '\t'},
    [0x2c] = {' ', ' ', ' ', ' '},
    [0x2d] = {'-', '_', '-', '_'},
    [0x2e] = {'=', '+', '=', '+'},
    [0x2f] = {'[', '{', '[', '{'},
    [0x30] = {']', '}', ']', '}'},
    [0x31] = {'\\', '|', '\\', '|'},
    [0x32] = {'#', '~', '#', '~'},
    [0x33] = {';', ':', ';', ':'},
    [0x34] = {'\'', '\"', '\'', '\"'},
    [0x35] = {'`', '~', '`', '~'},
    [0x36] = {',', '<', ',', '<'},
    [0x37] = {'.', '>', '.', '>'},
    [0x38] = {'/', '?', '/', '?'},

    [0x54] = {'/', '/', '/', '/'},
    [0x55] = {'*', '*', '*', '*'},
    [0x56] = {'-', '-', '-', '-'},
    [0x57] = {'+', '+', '+', '+'},
    [0x58] = {'\n', '\n', '\n', '\n'},
    [0x59] = {'1', 0, '1', 0},
    [0x5a] = {'2', 0, '2', 0},
    [0x5b] = {'3', 0, '3', 0},
    [0x5c] = {'4', 0, '4', 0},
    [0x5d] = {'5', '5', '5', '5'},
    [0x5e] = {'6', 0, '6', 0},
    [0x5f] = {'7', 0, '7', 0},
    [0x60] = {'8', 0, '8', 0},
    [0x61] = {'9', 0, '9', 0},
    [0x62] = {'0', 0, '0', 0},
    [0x63] = {'.', 0, '.', 0},

    [0x67] = {'=', '=', '=', '='},
};

static const uint8_t iso2erika[256][4] = {
    ['1'] = {47},
    ['2'] = {45},
    ['3'] = {43},
    ['4'] = {41},
    ['5'] = {39},
    ['6'] = {37},
    ['7'] = {35},
    ['8'] = {33},
    ['9'] = {31},
    ['0'] = {29},
    ['!'] = {61},
    ['"'] = {63},
    [':'] = {2},
    ['?'] = {55},
    ['%'] = {51},
    ['+'] = {27},
    ['_'] = {1},
    ['('] = {59},
    [')'] = {57},
    ['='] = {26},
    ['`'] = {14, 113},
    [BACKSPACE] = {}, // This is handled in code
    ['\''] = {118, 99, 117},
    ['a'] = {81},
    [A_OGONEK_LOWER] = {15},
    ['b'] = {72},
    ['c'] = {84},
    [C_KRESKA_LOWER] = {104},
    ['d'] = {85},
    ['e'] = {82},
    [E_OGONEK_LOWER] = {20},
    ['f'] = {94},
    ['g'] = {79},
    ['h'] = {91},
    ['i'] = {86},
    ['j'] = {92},
    ['k'] = {83},
    ['l'] = {88},
    [L_KRESKA_LOWER] = {18},
    ['m'] = {93},
    ['n'] = {77},
    [N_KRESKA_LOWER] = {103},
    ['o'] = {76},
    [O_KRESKA_LOWER] = {101},
    ['p'] = {89},
    ['q'] = {87},
    ['r'] = {80},
    ['s'] = {90},
    [S_KRESKA_LOWER] = {102},
    ['t'] = {78},
    ['u'] = {75},
    ['v'] = {74},
    ['w'] = {95},
    ['x'] = {73},
    ['y'] = {97},
    ['z'] = {96},
    [Z_KRESKA_LOWER] = {105},
    [Z_KROPKA_LOWER] = {24},
    ['.'] = {100},
    [','] = {99},
    ['-'] = {22},
    [' '] = {113},
    ['#'] = {7},
    ['|'] = {4},
    ['~'] = {25},
    ['$'] = {19},
    [DEGREE_SIGN] = {8},
    [';'] = {6},
    [SECTION_SIGN] = {49},
    ['*'] = {21},
    ['/'] = {53},
    ['\n'] = {119},
    ['\t'] = {121},
    ['A'] = {44},
    [A_OGONEK_UPPER] = {98, 44},
    ['B'] = {34},
    ['C'] = {36},
    [C_KRESKA_UPPER] = {14, 36},
    ['D'] = {38},
    ['E'] = {70},
    [E_OGONEK_UPPER] = {98, 70},
    ['F'] = {68},
    ['G'] = {42},
    ['H'] = {40},
    ['I'] = {65},
    ['J'] = {32},
    ['K'] = {66},
    ['L'] = {30},
    [L_KRESKA_UPPER] = {11},
    ['M'] = {56},
    ['N'] = {54},
    [N_KRESKA_UPPER] = {14, 54},
    ['O'] = {46},
    [O_KRESKA_UPPER] = {14, 46},
    ['P'] = {69},
    ['Q'] = {52},
    ['R'] = {28},
    ['S'] = {67},
    [S_KRESKA_UPPER] = {14, 67},
    ['T'] = {50},
    ['U'] = {48},
    ['V'] = {62},
    ['W'] = {64},
    ['X'] = {58},
    ['Y'] = {60},
    ['Z'] = {71},
    [Z_KRESKA_UPPER] = {14, 71},
    [Z_KROPKA_UPPER] = {23}};

#define KC_ESCAPE 0x29
#define KC_BACKSPACE 0x2a
#define KC_CAPS_LOCK 0x39
#define KC_RIGHT 0x4F
#define KC_LEFT 0x50
#define KC_DOWN 0x51
#define KC_UP 0x52

#define TW_WRITING 0x8B
#define TW_CORRECTING 0x8C
#define TW_FORWARDS 0x8D
#define TW_BACKWARDS 0x8E
#define TW_SPACE 0x71

static const uint8_t special_keycode2erika[128] = {
    [KC_ESCAPE] = 0,    // Escape
    [KC_CAPS_LOCK] = 0, // Caps lock
    [0x3a] = 0x84,      // F1 -> Line height 1.0
    [0x3b] = 0x85,      // F2 -> Line height 1.5
    [0x3c] = 0x86,      // F3 -> Line height 2.0
    [0x3d] = 0x87,      // F4 -> 10 chars/inch
    [0x3e] = 0x88,      // F5 -> 12 chars/inch
    [0x3f] = 0x89,      // F6 -> 15 chars/inch
    [0x40] = 0,         // F7
    [0x41] = 0,         // F8
    [0x42] = 0,         // F9
    [0x43] = 0,         // F10
    [0x44] = 0,         // F11
    [0x45] = 0,         // F12
    [0x46] = 0,         // Print Screen
    [0x47] = 0,         // Scroll Lock
    [0x48] = 0,         // Pause
    [0x49] = 0,         // Insert
    [0x4a] = 0,         // Home
    [0x4b] = 0,         // Page Up
    [0x4c] = 0,         // Delete
    [0x4d] = 0,         // End
    [0x4e] = 0,         // Page Down
    [KC_RIGHT] = 0x71,  // Right
    [KC_LEFT] = 0x72,   // Left
    [KC_DOWN] = 0x75,   // Down
    [KC_UP] = 0x76,     // Up
    [0x53] = 0,         // Num Lock
};

#endif