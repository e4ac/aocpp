#ifndef AOCPP_STRGRID_HPP
#define AOCPP_STRGRID_HPP
#include <concepts>
#include <optional>
#include <ranges>
#include <string>
#include <vector>

namespace aoc::geo {

/// Represents a string grid.
class strgrid {
public:
  template <std::ranges::range Rng> requires std::convertible_to<std::ranges::range_value_t<Rng>, std::string>
  explicit strgrid(Rng&& rng) : grid_(std::ranges::begin(rng), std::ranges::end(rng)) {}

  /// Gets the row count.
  [[nodiscard]] std::size_t rows() const noexcept { return grid_.size(); }

  /// Gets the column count.
  [[nodiscard]] std::size_t cols() const noexcept { return grid_.empty() ? 0 : grid_[0].size(); }

  /// Gets the grid area/boundary.
  [[nodiscard]] area<> bounds() const noexcept { return area{origin<>, pos{cols() - 1, rows() - 1}}; }

  /// Finds the position of a character.
  [[nodiscard]] std::optional<pos<>> find(const char ch) const {
    for (std::size_t y{0}; y < grid_.size(); y++) {
      if (const auto x = grid_[y].find(ch); x != std::string::npos)
        return pos{x, y};
    }
    return std::nullopt;
  }

  /// Finds all the positions of a character.
  [[nodiscard]] std::vector<pos<>> find_all(const char ch) const {
    std::vector<pos<>> result;
    for (std::size_t y{0}; y < grid_.size(); y++) {
      for (std::size_t x{0}; x < grid_[y].size(); x++) {
        if (grid_[y][x] == ch)
          result.emplace_back(x, y);
      }
    }
    return result;
  }

  template <typename T> requires std::is_arithmetic_v<T>
  [[nodiscard]] const char& operator[](const pos<T>& p) const noexcept { return grid_[p.y][p.x]; }
  [[nodiscard]] const std::string& operator[](const std::size_t i) const noexcept { return grid_[i]; }

private:
  /// Grid data.
  std::vector<std::string> grid_;
}; // class strgrid

} // namespace aoc::geo
#endif // AOCPP_STRGRID_HPP
