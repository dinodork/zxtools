#pragma once

#include <cstdint>

using Byte = std::uint8_t;

enum class Ink {
  BLACK = 0,
  BLUE = 1,
  RED = 1 << 1,
  MAGENTA = RED | BLUE,
  GREEN = 1 << 2,
  CYAN = GREEN | BLUE,
  YELLOW = GREEN | RED,
  WHITE = GREEN | RED | BLUE,
};

const Byte INK_BLACK = 0;
const Byte INK_BLUE = 1;
const Byte INK_RED = 1 << 1;
const Byte INK_MAGENTA = INK_RED | INK_BLUE;
const Byte INK_GREEN = 1 << 2;
const Byte INK_CYAN = INK_GREEN | INK_BLUE;
const Byte INK_YELLOW = INK_GREEN | INK_RED;
const Byte INK_WHITE = INK_GREEN | INK_RED | INK_BLUE;

const Byte PAPER_BLACK = 0;
const Byte PAPER_BLUE = 1 << 3;
const Byte PAPER_RED = 1 << 4;
const Byte PAPER_MAGENTA = PAPER_RED | PAPER_BLUE;
const Byte PAPER_GREEN = 1 << 5;
const Byte PAPER_CYAN = PAPER_GREEN | PAPER_BLUE;
const Byte PAPER_YELLOW = PAPER_GREEN | PAPER_RED;
const Byte PAPER_WHITE = PAPER_GREEN | PAPER_RED | PAPER_BLUE;

const Byte BRIGHT = 1 << 6;
const Byte FLASH = 1 << 7;
