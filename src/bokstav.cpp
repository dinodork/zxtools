#include "mdspan.hpp"
#include "zx_graphics/zx_colors.hpp"
#include "zx_graphics/zx_graphics.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <span>
#include <string>
#include <vector>

using namespace std;
using namespace zx_graphics;

using Bitmap_mem = uint8_t[32 * 24 * 8];
using Attr_mem = uint8_t[24][32];
using Character = uint8_t[8];

Byte gradient[] = {
    0,          //
    0,          //
    0b10101010, //
    0,          //
    0,          //
    0b01010101, //
    0,          //
    0b01010101, //
    //
    0b10101010, //
    0b01010101, //
    0b10101010, //
    0b11111111, //
    0b10101010, //
    0b11111111, //
    0b10101010, //
    0b11111111, //
};

Character char_a = {
    0b00000000, //
    0b00000000, //
    0b00111000, //
    0b00000100, //
    0b00111100, //
    0b01000100, //
    0b00111100, //
    0b00000000,
};

uint8_t font[767];

constexpr uint16_t get_byte_address(size_t x_byte, size_t y_pixel) {
  uint16_t byte_offset = x_byte;
  byte_offset |= (y_pixel & 0x07) << 8;
  byte_offset |= (y_pixel & 0X38) << 2;
  byte_offset |= (y_pixel & 0xC0) << 5;
  return byte_offset;
}

void plot(BitmapMem &mdmem, size_t x, size_t y) {
  mdmem(x >> 3, y) |= 0x80 >> (x & 7);
}

void draw(BitmapMem &mdmem, size_t x_start, size_t y_start, size_t x_end,
          size_t y_end) {
  if (x_end == x_start)
    for (auto y = y_start; y < y_end; ++y)
      plot(mdmem, x_start, y);
  if (y_end == y_start)
    for (auto x = x_start; x < x_end; ++x)
      plot(mdmem, x, y_start);
}

void writeLetterBig(BitmapMem &mdmem, span<uint8_t, 8> character, size_t col,
                    size_t row, Attr_mem &attr_mem) {

  for (size_t i = 0; i < sizeof(character); ++i) {
    for (auto j = 0; j < 8; ++j) {
      auto icol = col + j;
      auto irow = row + i;
      auto mask = 0x80 >> j;
      uint16_t pixel_row = character[i] << j;
      if (pixel_row & 0x80) {
        attr_mem[irow][icol] = BRIGHT | PAPER_MAGENTA | (int)Ink::CYAN;
        if (i == 0 || !(character[i - 1] & mask)) { // nothing above
          auto x = icol * 8, y = irow * 8 - 1;
          draw(mdmem, x, y, x + 8, y);
        }
        if (!(pixel_row & 0x40)) { // nothing to the right
          auto x = (icol + 1) * 8, y = irow * 8;
          draw(mdmem, x, y, x, y + 8);
        }
        if (i == sizeof(character) ||
            !(character[i + 1] & mask)) { // nothing below
          auto x = icol * 8, y = (irow + 1) * 8;
          draw(mdmem, x, y, x + 8, y);
        }
        if (!(pixel_row & 0x100)) { // nothing_to_the_left
          auto x = icol * 8 - 1, y = irow * 8;
          draw(mdmem, x, y, x, y + 8);
        }
      }
    }
  }
}

int main() {

  auto filename = "build/data/font.dat";
  ifstream fontfile(filename, ios::in | ios::binary | ios::ate);
  if (fontfile.is_open()) {
    //    size = fontfile.tellg();
    //    assert(size == 767);
    fontfile.seekg(0, ios::beg);
    fontfile.read((char *)font, sizeof(font));
    fontfile.close();
  } else {
    cout << "Failed to open '" << filename << "'" << endl;
    return -1;
  }

  ofstream myfile;
  myfile.open("bokstav.scr");

  Bitmap_mem bitmap_mem;
  Attr_mem attr_mem;

  auto bitmap_mem_mdspan = BitmapMem(bitmap_mem);

  for (auto &b : bitmap_mem)
    b = 0x00;

  for (auto &row : attr_mem)
    for (auto &col : row)
      col = BRIGHT | PAPER_BLACK | INK_WHITE;

  string s = "Hello";
  int col = 0;
  for (auto c : s) {
    auto character = span<uint8_t, 8>(font + (c - 32) * 8, 8);
    writeLetterBig(bitmap_mem_mdspan, character, col, 10, attr_mem);
    col += 6;
  }

  // Write to file
  for (auto b : bitmap_mem)
    myfile << b;

  for (auto &row : attr_mem)
    for (auto &col : row)
      myfile << col;

  myfile.close();
}
