#define CATCH_CONFIG_MAIN
#include "../include/str.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace aoc;
constexpr auto tag{"[str]"};

TEST_CASE("str::split(std::string_view, std::string_view, bool)", tag) {
  auto test = [](const std::string& sut, const std::string& delim, const bool skip_empty, const std::vector<std::string_view>& expected) {
    const std::vector result{str::split(sut, delim, skip_empty)};
    return result == expected;
  };

  REQUIRE(test("a,b,c", ",", true, std::vector<std::string_view>{"a", "b", "c"}));
  REQUIRE(test("a,,b,,c", ",", true, std::vector<std::string_view>{"a", "b", "c"}));
  REQUIRE(test("a,,b,,c", ",", false, std::vector<std::string_view>{"a", "", "b", "", "c"}));
  REQUIRE(test("abc--def----ghi", "--", true, std::vector<std::string_view>{"abc", "def", "ghi"}));
  REQUIRE(test("abc--def--ghi", ",", true, std::vector<std::string_view>{"abc--def--ghi"}));
}

TEST_CASE("str::mul(std::string_view, int)", tag) {
  REQUIRE(str::mul("ab", 3) == "ababab");
  REQUIRE(str::mul("abc", 5) == "abcabcabcabcabc");
  REQUIRE(str::mul("123", 1) == "123");
  REQUIRE(str::mul("abc", 0).empty());
}

TEST_CASE("str::rng_to_int(std::string_view)", tag) {
  const std::vector<std::string> input{"-1", "0", "1", "2", "3", "9999"};
  const auto result = str::rng_to_int(input);
  REQUIRE(std::vector<int>(result.begin(), result.end()) == std::vector<int>{-1, 0, 1, 2, 3, 9999});
}

TEST_CASE("str::rng_to_double(std::string_view)", tag) {
  const std::vector<std::string> input{"-1.4", "0.99", "1.984"};
  const auto result = str::rng_to_double(input);
  REQUIRE(std::vector<double>(result.begin(), result.end()) == std::vector<double>{-1.4, 0.99, 1.984});
}

TEST_CASE("str::rng_to_size_t(std::string_view)", tag) {
  const std::vector<std::string> input{"0", "1", "2", "3", "9999"};
  const auto result = str::rng_to_size_t(input);
  REQUIRE(std::vector<std::size_t>(result.begin(), result.end()) == std::vector<std::size_t>{0, 1, 2, 3, 9999});
}

TEST_CASE("str::trim_left(std::string_view)", tag) {
  REQUIRE(str::trim_left("   abc") == "abc");
  REQUIRE(str::trim_left("   abc   ") == "abc   ");
  REQUIRE(str::trim_left("abc   ") == "abc   ");
  REQUIRE(str::trim_left("abc") == "abc");
  REQUIRE(str::trim_left("   ").empty());
  REQUIRE(str::trim_left("").empty());
  REQUIRE(str::trim_left("aabbcc", "ac") == "bbcc");
}

TEST_CASE("str::trim_right(std::string_view)", tag) {
  REQUIRE(str::trim_right("   abc") == "   abc");
  REQUIRE(str::trim_right("   abc   ") == "   abc");
  REQUIRE(str::trim_right("abc   ") == "abc");
  REQUIRE(str::trim_right("abc") == "abc");
  REQUIRE(str::trim_right("   ").empty());
  REQUIRE(str::trim_right("").empty());
  REQUIRE(str::trim_right("aabbcc", "ac") == "aabb");
}

TEST_CASE("str::trim(std::string_view)", tag) {
  REQUIRE(str::trim("   abc") == "abc");
  REQUIRE(str::trim("   abc   ") == "abc");
  REQUIRE(str::trim("abc   ") == "abc");
  REQUIRE(str::trim("abc") == "abc");
  REQUIRE(str::trim("   ").empty());
  REQUIRE(str::trim("").empty());
  REQUIRE(str::trim("aabbcc", "ac") == "bb");
}
