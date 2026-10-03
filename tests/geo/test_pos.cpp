#define CATCH_CONFIG_MAIN
#include "../../include/geo/pos.hpp"
#include <algorithm>
#include <array>
#include <catch2/catch_test_macros.hpp>
#include <iterator>

using namespace aoc::geo;
constexpr auto tag{"[pos]"};

TEST_CASE("pos::cross(const pos<U>&)", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& other, const int expected) {
    const int result{sut.cross(other)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {0, 0}, 0));
  REQUIRE(test({1, 0}, {0, 1}, 1));
  REQUIRE(test({0, 1}, {1, 0}, -1));
  REQUIRE(test({1, 0}, {1, 0}, 0));
  REQUIRE(test({0, 0}, {1, 1}, 0));
  REQUIRE(test({1, 1}, {0, 0}, 0));
  REQUIRE(test({2, 3}, {4, 5}, -2));
}

TEST_CASE("pos::cross_pos()", tag) {
  constexpr pos sut{0, 0};
  constexpr std::array result{sut.cross_pos()};

  REQUIRE(result.size() == 4);
  REQUIRE(std::ranges::find(result, pos{1, 0}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, 0}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{0, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{0, -1}) != std::end(result));
}

TEST_CASE("pos::diag_pos()", tag) {
  constexpr pos sut{0, 0};
  constexpr std::array result{sut.diag_pos()};

  REQUIRE(result.size() == 4);
  REQUIRE(std::ranges::find(result, pos{1, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{1, -1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, -1}) != std::end(result));
}

TEST_CASE("pos::adj_pos()", tag) {
  constexpr pos sut{0, 0};
  constexpr std::array result{sut.adj_pos()};

  REQUIRE(result.size() == 8);
  REQUIRE(std::ranges::find(result, pos{1, 0}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, 0}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{0, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{0, -1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{1, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{1, -1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, 1}) != std::end(result));
  REQUIRE(std::ranges::find(result, pos{-1, -1}) != std::end(result));
}

TEST_CASE("pos::euclidean(const pos<U>&)", tag) {
  auto test = [](const pos<float>& sut, const pos<float>& other, const float expected) {
    const float result{sut.euclidean(other)};
    return result == expected;
  };

  REQUIRE(test({0.0f, 0.0f}, {0.0f, 0.0f}, 0.0f));
  REQUIRE(test({0.0f, 0.0f}, {3.0f, 4.0f}, 5.0f));
  REQUIRE(test({-1.0f, -1.0f}, {2.0f, 3.0f}, 5.0f));
  REQUIRE(test({1.5f, 2.5f}, {4.5f, 6.5f}, 5.0f));
}

TEST_CASE("pos::manhattan(const pos<U>&)", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& other, const int expected) {
    const int result{sut.manhattan(other)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {0, 0}, 0));
  REQUIRE(test({0, 0}, {1, 1}, 2));
  REQUIRE(test({-1, 1}, {1, -1}, 4));
  REQUIRE(test({-1, 1}, {-1, 1}, 0));
  REQUIRE(test({-3, 5}, {-7, 9}, 8));
}

TEST_CASE("pos::neighbours(Rng&&)", tag) {
  auto test = [](const pos<int>& sut, const std::vector<pos<int>>& dirs, const std::vector<pos<int>>& expected) {
    const auto n{sut.neighbours(dirs)};
    const std::vector result(std::ranges::begin(n), std::ranges::end(n));
    return result == expected;
  };

  REQUIRE(test(pos{0, 0}, std::vector<pos<int>>{{1, 0}, {1, 0}}, std::vector<pos<int>>{{1, 0}, {1, 0}}));
  REQUIRE(test(pos{0, 0}, std::vector<pos<int>>{{-1, 0}, {1, 0}}, std::vector<pos<int>>{{-1, 0}, {1, 0}}));
  REQUIRE(test(pos{1, 1}, std::vector<pos<int>>{{1, 0}, {1, 0}}, std::vector<pos<int>>{{2, 1}, {2, 1}}));
  REQUIRE(test(pos{1, 1}, std::vector<pos<int>>{{1, 0}, {0, 1}, {1, 1}}, std::vector<pos<int>>{{2, 1}, {1, 2}, {2, 2}}));
}

TEST_CASE("pos::quadrant", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& other, const int expected) {
    const int result{sut.quadrant(other)};
    return result == expected;
  };

  REQUIRE(test(pos{0, 0}, pos{0, 0}, 0));
  REQUIRE(test(pos{0, 0}, pos{1, 0}, 0));
  REQUIRE(test(pos{0, 0}, pos{0, 1}, 0));
  REQUIRE(test(pos{0, 0}, pos{-1, 0}, 0));
  REQUIRE(test(pos{0, 0}, pos{0, -1}, 0));
  REQUIRE(test(pos{0, 0}, pos{1, 1}, 1));
  REQUIRE(test(pos{0, 0}, pos{-1, 1}, 2));
  REQUIRE(test(pos{0, 0}, pos{-1, -1}, 3));
  REQUIRE(test(pos{0, 0}, pos{1, -1}, 4));
  REQUIRE(test(pos{5, 5}, pos{0, 0}, 3));
  REQUIRE(test(pos{5, 5}, pos{10, 10}, 1));
  REQUIRE(test(pos{5, 5}, pos{0, 10}, 2));
  REQUIRE(test(pos{5, 5}, pos{10, 0}, 4));
}

TEST_CASE("pos::rot90()", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& expected) {
    const pos result{sut.rot90()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {0, 0}));
  REQUIRE(test({1, 3}, {3, -1}));
  REQUIRE(test({5, -9}, {-9, -5}));
  REQUIRE(test({-5, 9}, {9, 5}));
  REQUIRE(test({-5, -9}, {-9, 5}));
}

TEST_CASE("pos::rot180()", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& expected) {
    const pos result{sut.rot180()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {0, 0}));
  REQUIRE(test({1, 3}, {-1, -3}));
  REQUIRE(test({5, -9}, {-5, 9}));
  REQUIRE(test({-5, 9}, {5, -9}));
  REQUIRE(test({-5, -9}, {5, 9}));
}

TEST_CASE("pos::rot270()", tag) {
  auto test = [](const pos<int>& sut, const pos<int>& expected) {
    const pos result{sut.rot270()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {0, 0}));
  REQUIRE(test({1, 3}, {-3, 1}));
  REQUIRE(test({5, -9}, {9, 5}));
  REQUIRE(test({-5, 9}, {-9, -5}));
  REQUIRE(test({-5, -9}, {9, -5}));
}

TEST_CASE("pos::constants", tag) {
  REQUIRE(pos{0, 0} == origin<int>);
  REQUIRE(pos{1, 0} == unit_x<int>);
  REQUIRE(pos{0, 1} == unit_y<int>);
  REQUIRE(std::array<pos<int>, 4>{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}} == cross_dir<>);
  REQUIRE(std::array<pos<int>, 4>{{{1, 1}, {1, -1}, {-1, 1}, {-1, -1}}} == diag_dir<>);
  REQUIRE(std::array<pos<int>, 8>{{{1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}}} == adj_dir<>);
}

TEST_CASE("pos::operator+(const pos<T>&, const pos<U>&)", tag) {
  REQUIRE(pos<>{0, 0} + pos<>{1, 1} == pos<>{1, 1});
  REQUIRE(pos<int>{-1, -1} + pos<int>{1, 1} == pos<int>{0, 0});
  REQUIRE(pos<int>{-3, 9} + pos<int>{8, -4} == pos<int>{5, 5});
}

TEST_CASE("pos::operator-(const pos<T>&, const pos<U>&)", tag) {
  REQUIRE(pos<int>{0, 0} - pos<int>{1, 1} == pos<int>{-1, -1});
  REQUIRE(pos<int>{-1, -1} - pos<int>{1, 1} == pos<int>{-2, -2});
  REQUIRE(pos<int>{-3, 9} - pos<int>{8, -4} == pos<int>{-11, 13});
}

TEST_CASE("pos::operator*(const pos<T>&, const pos<U>&)", tag) {
  REQUIRE(pos<int>{0, 0} * pos<int>{0, 0} == 0);
  REQUIRE(pos<int>{0, 0} * pos<int>{1, 1} == 0);
  REQUIRE(pos<int>{1, 0} * pos<int>{1, 0} == 1);
  REQUIRE(pos<int>{0, 1} * pos<int>{0, 1} == 1);
  REQUIRE(pos<int>{1, 0} * pos<int>{0, 1} == 0);
  REQUIRE(pos<int>{2, 3} * pos<int>{4, 5} == 23);
  REQUIRE(pos<int>{1, 2} * pos<int>{-1, -2} == -5);
}

TEST_CASE("pos::operator*(const pos<T>&, U)", tag) {
  REQUIRE(pos<int>{1, 1} * 3 == pos<int>{3, 3});
  REQUIRE(pos<int>{-5, 4} * -3 == pos<int>{15, -12});
}

TEST_CASE("pos::operator/(const pos<T>&, U)", tag) {
  REQUIRE(pos<int>{3, 3} / 1 == pos<int>{3, 3});
  REQUIRE(pos<int>{-10, 5} / 5 == pos<int>{-2, 1});
}

TEST_CASE("pos::operator%(const pos<T>&, const pos<U>&)", tag) {
  REQUIRE(pos<int>{10, 10} % pos<int>{10, 10} == pos<int>{0, 0});
  REQUIRE(pos<int>{10, 10} % pos<int>{3, 5} == pos<int>{1, 0});
  REQUIRE(pos<int>{3, 5} % pos<int>{3, 5} == pos<int>{0, 0});
  REQUIRE(pos<int>{-1, -1} % pos<int>{10, 15} == pos<int>{9, 14});
}

TEST_CASE("pos::operator%(const pos<T>&, U)", tag) {
  REQUIRE(pos<int>{10, 10} % 10 == pos<int>{0, 0});
  REQUIRE(pos<int>{10, 10} % 11 == pos<int>{10, 10});
  REQUIRE(pos<int>{10, 10} % 15 == pos<int>{10, 10});
}

TEST_CASE("pos::operator-(const pos<T>&)", tag) {
  REQUIRE(-pos<int>{0, 0} == pos<int>{0, 0});
  REQUIRE(-pos<int>{1, -1} == pos<int>{-1, 1});
}
