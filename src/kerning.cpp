#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>

using namespace std;
static constexpr size_t FONT_SIZE{767};
uint8_t font[FONT_SIZE];
uint8_t imageFile[32 * 24 * 8];

void dumpChar(char c) {
  for (int i = 0; i < 8; ++i) {
    cout << (int)font[i] << " ";
    for (int j = 0; j < 8; ++j) {
      cout << ((font[(c - ' ') * 8 + i] << j) & 0x80 ? "⬛" : "⬜");
    }
    cout << endl;
  }
}

void print(char c, int col) {
  for (int i = 0; i < 8; ++i)
    imageFile[i * 32 + col] = font[(c - ' ') * 8 + i];
}

void print(string s) {
  for (size_t i = 0; i < s.length(); ++i)
    print(s[i], i);
}

void dumpImageFile(size_t width) {
  for (int row = 0; row < 8; ++row) {
    for (size_t col = 0; col < width; ++col) {
      for (int bit = 0; bit < 8; ++bit) {
        cout << ((imageFile[row * 32 + col] << bit) & 0x80 ? "⬛" : "⬜");
      }
    }
    cout << endl;
  }
}

int main() {
  cout << "Hej world!\n";
  ifstream fontfile("data/font.dat", ios::in | ios::binary | ios::ate);
  if (fontfile.is_open()) {
    auto size = fontfile.tellg();
    assert(size == FONT_SIZE);
    fontfile.seekg(0, ios::beg);
    fontfile.read((char *)font, sizeof(font));
    fontfile.close();
  } else {
    cout << "Failed to open file" << endl;
    return -1;
  }
  string s = "kerning";
  print(s);
  dumpImageFile(s.length());
}
