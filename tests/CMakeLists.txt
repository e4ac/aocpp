include(FetchContent)
fetchcontent_declare(catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2.git GIT_TAG devel)
fetchcontent_makeavailable(catch2)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(CTest)
include(Catch)
add_executable(
  tests
  test_str.cpp
  geo/test_area.cpp
  geo/test_dirpos.cpp
  geo/test_pos.cpp
  geo/test_strgrid.cpp
  test_input.cpp
  test_math.cpp
)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
catch_discover_tests(tests)
