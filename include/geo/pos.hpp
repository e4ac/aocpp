#ifndef AOCPP_POS_HPP
#define AOCPP_POS_HPP
#include "../math.hpp"
#include <array>
#include <cmath>
#include <cstddef>
#include <ostream>
#include <ranges>
#include <type_traits>
#include <utility>

namespace aoc::geo {

/// Represents a 2D position.
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
struct pos {
  /// The X position.
  T x;

  /// The Y position.
  T y;

  constexpr explicit pos(T xy = 0) noexcept : x{xy}, y{xy} {}
  constexpr pos(T x, T y) noexcept : x{x}, y{y} {}
  constexpr auto operator<=>(const pos&) const = default;

  /// Returns the cross-product of two positions.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr T cross(const pos<U>& other) const noexcept {
    return x * other.y - y * other.x;
  }

  /// Returns the cross-pattern neighbours (+ shape).
  [[nodiscard]] constexpr std::array<pos, 4> cross_pos(T dist = 1) const noexcept {
    return {{pos{x + dist, y}, pos{x - dist, y}, pos{x, y + dist}, pos{x, y - dist}}};
  }

  /// Returns the diagonal-pattern neighbours (X shape).
  [[nodiscard]] constexpr std::array<pos, 4> diag_pos(T dist = 1) const noexcept {
    return {{pos{x + dist, y + dist}, pos{x - dist, y - dist}, pos{x - dist, y + dist}, pos{x + dist, y - dist}}};
  }

  /// Returns the adjacent-pattern neighbours (* shape).
  [[nodiscard]] constexpr std::array<pos, 8> adj_pos(T dist = 1) const noexcept {
    return {{
      pos{x + dist, y}, pos{x - dist, y}, pos{x, y + dist}, pos{x, y - dist},
      pos{x + dist, y + dist}, pos{x - dist, y - dist}, pos{x - dist, y + dist}, pos{x + dist, y - dist}
    }};
  }

  /// Returns the Euclidean distance between two positions.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] T euclidean(const pos<U>& other) const {
    return std::hypot(x - other.x, y - other.y);
  }

  /// Returns the manhattan distance between two positions.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] T manhattan(const pos<U>& other) const {
    return std::abs(x - other.x) + std::abs(y - other.y);
  }

  /// Returns a range of neighbours specified by the range of directions.
  template <std::ranges::range Rng>
  [[nodiscard]] auto neighbours(Rng&& rng) const {
    return std::views::transform(std::forward<Rng>(rng), [self = *this](const auto& p) { return self + p; });
  }

  /// Returns the quadrant of another position relative to this position. 0 means on the same axis.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr int quadrant(const pos<U>& other) const {
    const auto dx = other.x - x;
    const auto dy = other.y - y;
    if (dx == 0 || dy == 0)
      return 0;
    if (dx > 0)
      return dy > 0 ? 1 : 4;
    return dy > 0 ? 2 : 3;
  }

  /// Returns the position after rotating clockwise 90 degrees.
  [[nodiscard]] constexpr pos rot90() const noexcept {
    return pos{y, -x};
  }

  /// Returns the position after rotating clockwise 180 degrees.
  [[nodiscard]] constexpr pos rot180() const noexcept {
    return pos{-x, -y};
  }

  /// Returns the position after rotating clockwise 270 degrees.
  [[nodiscard]] constexpr pos rot270() const noexcept {
    return pos{-y, x};
  }
}; // struct pos

/// The origin point (0, 0).
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
constexpr pos<T> origin{0, 0};

/// The unit X position (1, 0).
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
constexpr pos<T> unit_x{1, 0};

/// The unit Y position (0, 1).
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
constexpr pos<T> unit_y{0, 1};

/// The cross-directions (+ shape).
template <typename T = int> requires std::is_arithmetic_v<T>
constexpr std::array<pos<T>, 4> cross_dir{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}};

/// The diagonal-positions (X shape).
template <typename T = int> requires std::is_arithmetic_v<T>
constexpr std::array<pos<T>, 4> diag_dir{{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

/// The adjacent-positions (* shape).
template <typename T = int> requires std::is_arithmetic_v<T>
constexpr std::array<pos<T>, 8> adj_dir{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}};

template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr pos<T> operator+(const pos<T>& lhs, const pos<U>& rhs) noexcept {
  return pos<T>{lhs.x + rhs.x, lhs.y + rhs.y};
}

template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr pos<T> operator-(const pos<T>& lhs, const pos<U>& rhs) noexcept {
  return pos<T>{lhs.x - rhs.x, lhs.y - rhs.y};
}

template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr T operator*(const pos<T>& lhs, const pos<U>& rhs) noexcept {
  return lhs.x * rhs.x + lhs.y * rhs.y;
}

template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr pos<T> operator*(const pos<T>& lhs, U rhs) noexcept {
  return pos<T>{lhs.x * rhs, lhs.y * rhs};
}

template <typename T, typename U> requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
[[nodiscard]] constexpr pos<T> operator/(const pos<T>& lhs, U rhs) noexcept {
  return pos<T>{lhs.x / rhs, lhs.y / rhs};
}

template <typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
[[nodiscard]] constexpr pos<T> operator%(const pos<T>& lhs, const pos<U>& rhs) noexcept {
  return pos<T>{math::pos_mod(lhs.x, rhs.x), math::pos_mod(lhs.y, rhs.y)};
}

template <typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
[[nodiscard]] constexpr pos<T> operator%(const pos<T>& lhs, U rhs) noexcept {
  return pos<T>{math::pos_mod(lhs.x, rhs), math::pos_mod(lhs.y, rhs)};
}

template <typename T> requires std::is_arithmetic_v<T>
[[nodiscard]] constexpr pos<T> operator-(const pos<T>& opr) noexcept {
  return pos<T>{-opr.x, -opr.y};
}

template <typename T> requires std::is_arithmetic_v<T>
std::ostream& operator<<(std::ostream& os, const pos<T>& opr) {
  return os << '(' << opr.x << ", " << opr.y << ')';
}

} // namespace aoc::geo
#endif // AOCPP_POS_HPP
