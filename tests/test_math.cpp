#define CATCH_CONFIG_MAIN
#include "../include/math.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc::math;
constexpr auto tag{"[math]"};

TEST_CASE("math::pos_mod(T, U)", tag) {
  REQUIRE(pos_mod(5, 3) == 2);
  REQUIRE(pos_mod(10, 7) == 3);
  REQUIRE(pos_mod(-1, 3) == 2);
  REQUIRE(pos_mod(-10, 7) == 4);
  REQUIRE(pos_mod(-5, -3) == -2);
  REQUIRE(pos_mod(-10, -7) == -3);
}

TEST_CASE("math::num_digits(T)", tag) {
  REQUIRE(num_digits(123) == 3);
  REQUIRE(num_digits(-123) == 3);
  REQUIRE(num_digits(1000000) == 7);
  REQUIRE(num_digits(1000000.123) == 7);
}

TEST_CASE("math::llpow(long long, long long)", tag) {
  REQUIRE(llpow(2, 1) == 2);
  REQUIRE(llpow(2, 2) == 4);
  REQUIRE(llpow(10, 2) == 100);
  REQUIRE(llpow(10, 5) == 100000);
  REQUIRE(llpow(-10, 5) == -100000);
  REQUIRE(llpow(-10, 6) == 1000000);
}
