#ifndef AOCPP_AREA_HPP
#define AOCPP_AREA_HPP
#include "pos.hpp"
#include <algorithm>
#include <cstddef>
#include <ranges>
#include <type_traits>
#include <utility>

namespace aoc::geo {

/// Represents a 2D area.
template <typename T = std::size_t> requires std::is_arithmetic_v<T>
class area {
public:
  constexpr area(const pos<T>& corner1, const pos<T>& corner2) {
    top_left_ = pos{std::min(corner1.x, corner2.x), std::max(corner1.y, corner2.y)};
    bottom_right_ = pos{std::max(corner1.x, corner2.x), std::min(corner1.y, corner2.y)};
  }

  /// Returns the top-left position.
  [[nodiscard]] constexpr pos<T> top_left() const noexcept {
    return top_left_;
  }

  /// Returns the top-right position.
  [[nodiscard]] constexpr pos<T> top_right() const noexcept {
    return pos<T>{bottom_right_.x, top_left_.y};
  }

  /// Returns the bottom-left position.
  [[nodiscard]] constexpr pos<T> bottom_left() const noexcept {
    return pos<T>{top_left_.x, bottom_right_.y};
  }

  /// Returns the bottom-right position.
  [[nodiscard]] constexpr pos<T> bottom_right() const noexcept {
    return bottom_right_;
  }

  /// Returns the maximum X position.
  [[nodiscard]] constexpr T max_x() const noexcept {
    return bottom_right_.x;
  }

  /// Returns the minimum X position.
  [[nodiscard]] constexpr T min_x() const noexcept {
    return top_left_.x;
  }

  /// Returns the maximum Y position.
  [[nodiscard]] constexpr T max_y() const noexcept {
    return top_left_.y;
  }

  /// Returns the minimum Y position.
  [[nodiscard]] constexpr T min_y() const noexcept {
    return bottom_right_.y;
  }

  /// Returns the area width.
  [[nodiscard]] constexpr T width() const noexcept {
    return bottom_right_.x - top_left_.x + 1;
  }

  /// Returns the area height.
  [[nodiscard]] constexpr T height() const noexcept {
    return top_left_.y - bottom_right_.y + 1;
  }

  /// Returns the area size.
  [[nodiscard]] constexpr T size() const {
    return width() * height();
  }

  /// Returns whether the area contains an X value.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool has_x(U x) const noexcept {
    return x >= top_left_.x && x <= bottom_right_.x;
  }

  /// Returns whether the area contains an X value.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool has_y(U y) const noexcept {
    return y >= bottom_right_.y && y <= top_left_.y;
  }

  /// Returns whether the area contains a position.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool has(const pos<U>& p) const noexcept {
    return has_x(p.x) && has_y(p.y);
  }

  /// Returns whether a position is on the X boundary.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool on_x(const pos<U>& p) const noexcept {
    return has_y(p.y) && (p.x == top_left_.x || p.x == bottom_right_.x);
  }

  /// Returns whether a position is on the Y boundary.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool on_y(const pos<U>& p) const noexcept {
    return has_x(p.x) && (p.y == bottom_right_.y || p.y == top_left_.y);
  }

  /// Returns whether a position is on a boundary.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool on_bound(const pos<U>& p) const noexcept {
    return on_x(p) || on_y(p);
  }

  /// Returns whether a position is on a corner.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr bool on_corner(const pos<U>& p) const noexcept {
    return on_x(p) && on_y(p);
  }

  /// Returns a position wrapped into this area.
  template <typename U> requires std::is_arithmetic_v<U>
  [[nodiscard]] constexpr pos<U> wrap(const pos<U>& p) const noexcept {
    return p % pos{width(), height()};
  }

  /// Returns a collection of positions wrapped into this area.
  template <std::ranges::range Rng>
  [[nodiscard]] auto wrap(Rng&& rng) const {
    return std::views::transform(std::forward<Rng>(rng), [self = *this](const auto& p) { return self.wrap(p); });
  }

  /// Returns a collection of positions filtered by this area.
  template <std::ranges::range Rng>
  [[nodiscard]] auto filter(Rng&& rng) const {
    return std::views::filter(std::forward<Rng>(rng), [self = *this](const auto& p) { return self.has(p); });
  }

  [[nodiscard]] bool operator==(const area& other) const noexcept { return size() == other.size(); }
  [[nodiscard]] bool operator!=(const area& other) const noexcept { return size() != other.size(); }
  [[nodiscard]] bool operator<(const area& other) const noexcept { return size() < other.size(); }
  [[nodiscard]] bool operator<=(const area& other) const noexcept { return size() <= other.size(); }
  [[nodiscard]] bool operator>(const area& other) const noexcept { return size() > other.size(); }
  [[nodiscard]] bool operator>=(const area& other) const noexcept { return size() >= other.size(); }

private:
  /// The top left corner.
  pos<T> top_left_;

  /// The bottom right corner.
  pos<T> bottom_right_;
}; // class area

} // namespace aoc
#endif // AOCPP_AREA_HPP
