[![CICD](https://github.com/e4ac/aocpp/actions/workflows/cicd.yml/badge.svg)](https://github.com/e4ac/aocpp/actions/workflows/cicd.yml)
[![License: GPLv3](https://img.shields.io/badge/license-GPLv3-blue)](https://opensource.org/license/gpl-3-0)

# AoCPP
C++ header only library for solving [Advent of Code](https://adventofcode.com/).

## Usage
Add below to `CMakeLists.txt`:
```cmake
include(FetchContent)
fetchcontent_declare(aocpp GIT_REPOSITORY https://github.com/e4ac/aocpp GIT_TAG main)
fetchcontent_makeavailable(aocpp)
```

## Testing
Build and test with [`cmake`](https://cmake.org/).
```shell
cmake -B bin
cmake --build bin --parallel 8
ctest --test-dir bin --parallel 8
```
