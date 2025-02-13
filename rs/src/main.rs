use std::{
    collections::{HashMap, HashSet},
    env,
    io::ErrorKind,
    time::Duration,
};

use time::OffsetDateTime;

#[derive(Clone, Copy, Debug, PartialEq, Eq)]
enum AltStatus {
    Up,
    JustDown(OffsetDateTime),
    Down(OffsetDateTime),
}

impl AltStatus {
    fn down(self) -> bool {
        self != Self::Up
    }
}

fn main() {
    let valid_chars = "1234567890!\":?%+_()=ż`qwertzuiopóasdfghjklłyxcvbnm.,- $~|*śńćęąźŻ\n\tQWERTYUIOPASDFGHJKLZXCVBNMŁ".chars().collect::<HashSet<_>>();
    let char_to_typewriter = HashMap::<_, u8>::from([
        ('1', 47),
        ('2', 45),
        ('3', 43),
        ('4', 41),
        ('5', 39),
        ('6', 37),
        ('7', 35),
        ('8', 33),
        ('9', 31),
        ('0', 29),
        ('!', 61),
        ('"', 63),
        (':', 2),
        ('?', 55),
        ('%', 51),
        ('+', 27),
        ('_', 1),
        ('(', 59),
        (')', 57),
        ('=', 26),
        ('`', 14),
        ('q', 87),
        ('w', 95),
        ('e', 82),
        ('r', 80),
        ('t', 78),
        ('z', 96),
        ('u', 75),
        ('i', 86),
        ('o', 76),
        ('p', 89),
        ('a', 81),
        ('s', 90),
        ('d', 85),
        ('f', 94),
        ('g', 79),
        ('h', 91),
        ('j', 92),
        ('k', 83),
        ('l', 88),
        ('y', 97),
        ('x', 73),
        ('c', 84),
        ('v', 74),
        ('n', 77),
        ('m', 93),
        ('.', 100),
        (',', 99),
        ('-', 22),
        (' ', 113),
        ('$', 187),
        ('~', 253),
        ('|', 19),
        ('*', 187),
        ('\u{017c}', 24),
        ('\u{00f3}', 101),
        ('\u{0142}', 18),
        ('b', 72),
        ('\u{015b}', 102),
        ('\u{0144}', 103),
        ('\u{0107}', 104),
        ('\u{0119}', 20),
        ('\u{0105}', 15),
        ('\u{017a}', 105),
        ('\u{017b}', 23),
        ('\n', 119),
        ('\t', 121),
        ('Q', 52),
        ('W', 64),
        ('E', 70),
        ('R', 28),
        ('T', 50),
        ('Y', 60),
        ('U', 48),
        ('I', 65),
        ('O', 46),
        ('P', 69),
        ('A', 44),
        ('S', 67),
        ('D', 38),
        ('F', 68),
        ('G', 42),
        ('H', 40),
        ('J', 32),
        ('K', 66),
        ('L', 30),
        ('Z', 71),
        ('X', 58),
        ('C', 36),
        ('V', 62),
        ('B', 34),
        ('N', 54),
        ('M', 56),
        ('\u{0141}', 11),
    ]);

    let Some(path) = env::args().nth(1) else {
        eprintln!("Usage: typewriter <path>");
        return;
    };

    let mut port = serialport::new(&path, 1200)
        .timeout(Duration::from_secs(30))
        .open()
        .expect("Failed to open serial port");

    let _ = port.set_flow_control(serialport::FlowControl::Software);

    println!("Connected to typewriter");
    let msg = "W Szczebrzeszynie chrząszcz brzmi w trzcinie. Zażółć gęślą jaźń"
        .chars()
        .filter_map(|c| char_to_typewriter.get(&c))
        .copied()
        .collect::<Vec<_>>();
    println!("{msg:?}");
    port.write_all(&msg)
        .expect("Failed to send code to typewriter");
}
