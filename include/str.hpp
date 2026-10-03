#ifndef AOCPP_STR_HPP
#define AOCPP_STR_HPP
#include <ranges>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace aoc::str {

/// Splits a string.
inline std::vector<std::string_view> split(const std::string_view str, const std::string_view delim = ",", const bool skip_empty = true) {
  std::vector<std::string_view> result;
  for (auto&& chunk : std::views::split(str, delim)) {
    if (std::string_view token{chunk}; !skip_empty || !token.empty())
      result.push_back(token);
  }
  return result;
}

/// Multiplies a string.
inline std::string mul(const std::string_view str, const std::size_t n) {
  if (n == 0)
    return std::string{};
  if (n == 1)
    return std::string{str};

  std::string result;
  result.reserve(str.size() * n);
  for (std::size_t i = 0; i < n; ++i)
    result.append(str);
  return result;
}

/// Converts a range of strings to `double`.
template <std::ranges::range Rng> requires std::convertible_to<std::ranges::range_value_t<Rng>, std::string>
auto rng_to_double(Rng&& rng) {
  return std::views::transform(std::forward<Rng>(rng), [](const std::string& str) { return std::stod(str); });
}

/// Converts a range of strings to `int`.
template <std::ranges::range Rng> requires std::convertible_to<std::ranges::range_value_t<Rng>, std::string>
auto rng_to_int(Rng&& rng) {
  return std::views::transform(std::forward<Rng>(rng), [](const std::string& str) { return std::stoi(str); });
}

/// Converts a range of strings to `std::size_t`.
template <std::ranges::range Rng> requires std::convertible_to<std::ranges::range_value_t<Rng>, std::string>
auto rng_to_size_t(Rng&& rng) {
  return std::views::transform(std::forward<Rng>(rng), [](const std::string& str) { return std::stoull(str); });
}

/// Trims the string from the left.
constexpr std::string_view trim_left(const std::string_view str, const std::string_view whitespace = " \t\n\v\f\r") {
  const std::size_t start{str.find_first_not_of(whitespace)};
  return start == std::string_view::npos ? std::string_view{} : str.substr(start);
}

/// Trims the string from the right.
constexpr std::string_view trim_right(const std::string_view str, const std::string_view whitespace = " \t\n\v\f\r") {
  const std::size_t end{str.find_last_not_of(whitespace)};
  return end == std::string_view::npos ? std::string_view{} : str.substr(0, end + 1);
}

/// Trims the string.
constexpr std::string_view trim(const std::string_view str, const std::string_view whitespace = " \t\n\v\f\r") {
  const std::size_t start{str.find_first_not_of(whitespace)};
  if (start == std::string_view::npos)
    return {};

  const std::size_t end{str.find_last_not_of(whitespace)};
  return str.substr(start, end - start + 1);
}

} // namespace aoc::str
#endif // AOCPP_STR_HPP
