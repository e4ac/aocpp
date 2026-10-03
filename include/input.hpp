#ifndef AOCPP_INPUT_HPP
#define AOCPP_INPUT_HPP
#include <fstream>
#include <ranges>
#include <string>
#include <vector>

namespace aoc::io {

/// Reads non-empty lines from a file.
inline std::vector<std::string> read_lines(const std::string& filename) {
  std::vector<std::string> lines;
  std::ifstream file{filename};
  std::string line;
  while (std::getline(file, line)) {
    if (!line.empty())
      lines.push_back(std::move(line));
  }
  return lines;
}

} // namespace aoc::io
#endif // AOCPP_INPUT_HPP
