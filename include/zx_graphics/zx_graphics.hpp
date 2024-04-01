#pragma once

#include <iostream>

namespace zx_graphics {

struct ZXSpectrumLayout {
  template <class Extents> class mapping;
};

using ZXSpectrumScreen = Kokkos::extents<std::uint16_t, 32, 192>;

template <class Extents> class ZXSpectrumLayout::mapping {
public:
  using extents_type = Extents;
  using index_type = typename extents_type::index_type;
  using size_type = typename extents_type::size_type;
  using rank_type = typename extents_type::rank_type;
  using layout_type = ZXSpectrumLayout;

  // The framework forces the mapping to be constructible from the extents
  // type, but we really don't have a need for that.
  mapping(ZXSpectrumScreen) {}

  /*
    How to translate the screen memory address:

    Byte         15|14|13|12|11|10| 9| 8| 7| 6| 5| 4| 3| 2| 1| 0
                 --+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--
    Co-ordinate   0| 0| 0|Y7|Y6|Y2|Y1|Y0|Y5|Y4|Y3|X4|X3|X2|X1|X0
  */
  constexpr index_type operator()(index_type x_byte,
                                  index_type y_pixel) const noexcept {
    uint16_t byte_offset = x_byte;
    byte_offset |= (y_pixel & 0x07) << 8;
    byte_offset |= (y_pixel & 0X38) << 2;
    byte_offset |= (y_pixel & 0xC0) << 5;
    return byte_offset;
  }
};

using BitmapMem =
    Kokkos::mdspan<std::uint8_t, ZXSpectrumScreen, ZXSpectrumLayout>;

} // namespace zx_graphics
