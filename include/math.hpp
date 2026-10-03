#ifndef AOCPP_MATH_HPP
#define AOCPP_MATH_HPP
#include <cmath>
#include <type_traits>

namespace aoc::math {

/// Performs a MOD operation that can handle negative values.
template <typename T, typename U> requires std::is_integral_v<T> && std::is_integral_v<U>
[[nodiscard]] constexpr T pos_mod(T lhs, U rhs) noexcept {
  return (lhs % rhs + rhs) % rhs;
}

/// Finds the number of digits in a number.
template <typename T> requires std::is_arithmetic_v<T>
[[nodiscard]] int num_digits(T n) {
  return n == 0 ? 1 : static_cast<int>(std::log10(std::abs(n)) + 1);
}

/// Performs pow on long long.
[[nodiscard]] constexpr long long llpow(long long base, long long exp) noexcept {
  if (exp < 0)
    return 0;

  long long result = 1;
  while (exp > 0) {
    if (exp % 2 == 1)
      result *= base;

    base *= base;
    exp /= 2;
  }
  return result;
}

} // namespace aoc::math
#endif // AOCPP_MATH_HPP
