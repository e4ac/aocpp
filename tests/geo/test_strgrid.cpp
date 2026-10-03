#define CATCH_CONFIG_MAIN
#include "../../include/geo/area.hpp"
#include "../../include/geo/strgrid.hpp"
#include <catch2/catch_test_macros.hpp>
#include <optional>
#include <vector>

using namespace aoc::geo;
constexpr auto tag{"[strgrid]"};

TEST_CASE("strgrid::rows()", tag) {
  auto test = [](const std::vector<std::string>& data, const std::size_t expected) {
    const strgrid sut{data};
    return sut.rows() == expected;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def"}, 2));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 3));
  REQUIRE(test(std::vector<std::string>{}, 0));
}

TEST_CASE("strgrid::cols()", tag) {
  auto test = [](const std::vector<std::string>& data, const std::size_t expected) {
    const strgrid sut{data};
    return sut.cols() == expected;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def"}, 3));
  REQUIRE(test(std::vector<std::string>{"ab", "cd", "ef"}, 2));
  REQUIRE(test(std::vector<std::string>{}, 0));
  REQUIRE(test(std::vector<std::string>{""}, 0));
}

TEST_CASE("strgrid::bounds()", tag) {
  auto test = [](const std::vector<std::string>& data, const area<>& expected) {
    const strgrid sut{data};
    return sut.bounds() == expected;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, area{origin<>, pos<>{2, 2}}));
  REQUIRE(test(std::vector<std::string>{"ab", "cd", "ef"}, area{origin<>, pos<>{1, 2}}));
}

TEST_CASE("strgrid::find(char)", tag) {
  auto test = [](const std::vector<std::string>& data, const char ch, const std::optional<pos<>>& opt) {
    const strgrid sut{data};
    return sut.find(ch) == opt;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 'a', pos<>{0, 0}));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 'e', pos<>{1, 1}));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 'h', pos<>{1, 2}));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 'z', std::nullopt));
}

TEST_CASE("strgrid::find_all(char)", tag) {
  auto test = [](const std::vector<std::string>& data, const char ch, const std::vector<pos<>>& result) {
    const strgrid sut{data};
    return sut.find_all(ch) == result;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "bac", "cba"}, 'a', std::vector{pos<>{0, 0}, pos<>{1, 1}, pos<>{2, 2}}));
  REQUIRE(test(std::vector<std::string>{"abc", "bac", "cba"}, 'b', std::vector{pos<>{1, 0}, pos<>{0, 1}, pos<>{1, 2}}));
  REQUIRE(test(std::vector<std::string>{"abc", "bac", "cba"}, 'z', std::vector<pos<>>{}));
}

TEST_CASE("strgrid::operator[](pos)", tag) {
  auto test = [](const std::vector<std::string>& data, const pos<int>& p, const char expected) {
    const strgrid sut{data};
    return sut[p] == expected;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, pos{0, 0}, 'a'));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, pos{1, 1}, 'e'));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, pos{2, 1}, 'f'));
}

TEST_CASE("strgrid::operator[](std::size_t)", tag) {
  auto test = [](const std::vector<std::string>& data, const std::size_t i, const std::string& expected) {
    const strgrid sut{data};
    return sut[i] == expected;
  };

  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 0, "abc"));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 1, "def"));
  REQUIRE(test(std::vector<std::string>{"abc", "def", "ghi"}, 2, "ghi"));
}
