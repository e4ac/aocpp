#define CATCH_CONFIG_MAIN
#include "../../include/geo/dirpos.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc::geo;
constexpr auto tag{"[dirpos]"};

TEST_CASE("dirpos::next(T)", tag) {
  auto test = [](const dirpos<int>& sut, const dirpos<int>& expected) {
    const dirpos result{sut.next()};
    return result == expected;
  };

  REQUIRE(test(dirpos<int>{{0, 0}, {1, 0}}, dirpos<int>{{1, 0}, {1, 0}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {2, 0}}, dirpos<int>{{2, 0}, {2, 0}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-4, 1}}, dirpos<int>{{-4, 1}, {-4, 1}}));
}

TEST_CASE("dirpos::rot90()", tag) {
  auto test = [](const dirpos<int>& sut, const dirpos<int>& expected) {
    const dirpos result{sut.rot90()};
    return result.p == expected.p && result.d == expected.d;
  };

  REQUIRE(test(dirpos<int>{{0, 0}, {1, 3}}, dirpos<int>{{0, 0}, {3, -1}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {5, -9}}, dirpos<int>{{0, 0}, {-9, -5}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, 9}}, dirpos<int>{{0, 0}, {9, 5}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, -9}}, dirpos<int>{{0, 0}, {-9, 5}}));
}

TEST_CASE("dirpos::rot180()", tag) {
  auto test = [](const dirpos<int>& sut, const dirpos<int>& expected) {
    const dirpos result{sut.rot180()};
    return result.p == expected.p && result.d == expected.d;
  };

  REQUIRE(test(dirpos<int>{{0, 0}, {1, 3}}, dirpos<int>{{0, 0}, {-1, -3}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {5, -9}}, dirpos<int>{{0, 0}, {-5, 9}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, 9}}, dirpos<int>{{0, 0}, {5, -9}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, -9}}, dirpos<int>{{0, 0}, {5, 9}}));
}

TEST_CASE("dirpos::rot270()", tag) {
  auto test = [](const dirpos<int>& sut, const dirpos<int>& expected) {
    const dirpos result{sut.rot270()};
    return result.p == expected.p && result.d == expected.d;
  };

  REQUIRE(test(dirpos<int>{{0, 0}, {1, 3}}, dirpos<int>{{0, 0}, {-3, 1}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {5, -9}}, dirpos<int>{{0, 0}, {9, 5}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, 9}}, dirpos<int>{{0, 0}, {-9, -5}}));
  REQUIRE(test(dirpos<int>{{0, 0}, {-5, -9}}, dirpos<int>{{0, 0}, {9, -5}}));
}

TEST_CASE("dirpos::operator==(dirpos)", tag) {
  REQUIRE(dirpos<int>{{0, 0}, {1, 0}} == dirpos<int>{{0, 0}, {1, 0}});
  REQUIRE(dirpos<int>{{0, 1}, {1, 0}} != dirpos<int>{{0, 0}, {1, 0}});
  REQUIRE(dirpos<int>{{0, 0}, {1, 0}} != dirpos<int>{{0, 0}, {2, 0}});
}
