#define CATCH_CONFIG_MAIN
#include "../include/input.hpp"
#include <catch2/catch_test_macros.hpp>
#include <fstream>

using namespace aoc::io;
constexpr auto tag{"[input]"};

TEST_CASE("input::read_lines(std::string)", tag) {
  const std::string filename{"read_lines.txt"};
  {
    std::ofstream file{filename};
    file << "line1\nline2\n\nline4\nline5\n\n\nline8\n";
  }

  const std::vector results{read_lines(filename)};
  REQUIRE(results.size() == 5);
  REQUIRE(results[0] == "line1");
  REQUIRE(results[1] == "line2");
  REQUIRE(results[2] == "line4");
  REQUIRE(results[3] == "line5");
  REQUIRE(results[4] == "line8");
}
