#ifndef AOCPP_DIRPOS_HPP
#define AOCPP_DIRPOS_HPP
#include "pos.hpp"
#include <cstddef>
#include <type_traits>

namespace aoc::geo {

/// Represents a 2D position with a direction.
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
struct dirpos {
  /// The 2D position.
  pos<T> p;

  /// The direction.
  pos<T> d;

  constexpr explicit dirpos(pos<T> p, pos<T> d = unit_x<T>) noexcept : p{p}, d{d} {}

  /// Returns the next position.
  [[nodiscard]] constexpr dirpos next() const noexcept {
    return dirpos{p + d, d};
  }

  /// Returns the position after rotating the direction clockwise 90 degrees.
  [[nodiscard]] constexpr dirpos rot90() const noexcept {
    return dirpos{p, d.rot90()};
  }

  /// Returns the position after rotating the direction clockwise 180 degrees.
  [[nodiscard]] constexpr dirpos rot180() const noexcept {
    return dirpos{p, d.rot180()};
  }

  /// Returns the position after rotating the direction clockwise 270 degrees.
  [[nodiscard]] constexpr dirpos rot270() const noexcept {
    return dirpos{p, d.rot270()};
  }

  [[nodiscard]] bool operator==(const dirpos& other) const noexcept { return p == other.p && d == other.d; }
  [[nodiscard]] bool operator!=(const dirpos& other) const noexcept { return !operator==(other); }
};  // struct dirpos

} // namespace aoc::geo
#endif // AOCPP_DIRPOS_HPP
