#define CATCH_CONFIG_MAIN
#include "../../include/geo/area.hpp"
#include "../../include/geo/pos.hpp"
#include <catch2/catch_test_macros.hpp>
#include <ranges>
#include <vector>

using namespace aoc::geo;
constexpr auto tag{"[area]"};

TEST_CASE("area::ctor(const pos<T>&, const pos<T>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& top_left, const pos<int>& bottom_right) {
    const area result{corner1, corner2};
    return top_left == result.top_left() && bottom_right == result.bottom_right();
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 5}, {5, 0}));
  REQUIRE(test({-3, -4}, {-5, 7}, {-5, 7}, {-3, -4}));
  REQUIRE(test({-3, 7}, {-5, -4}, {-5, 7}, {-3, -4}));
}

TEST_CASE("area::top_right()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& expected) {
    const pos result{area{corner1, corner2}.top_right()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {5, 5}));
  REQUIRE(test({-3, -4}, {-5, 7}, {-3, 7}));
  REQUIRE(test({-3, 7}, {-5, -4}, {-3, 7}));
}

TEST_CASE("area::bottom_left()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& expected) {
    const pos result{area{corner1, corner2}.bottom_left()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}));
  REQUIRE(test({-3, -4}, {-5, 7}, {-5, -4}));
  REQUIRE(test({-3, 7}, {-5, -4}, {-5, -4}));
}

TEST_CASE("area::max_x()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.max_x()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 5));
  REQUIRE(test({-3, -4}, {-5, 7}, -3));
  REQUIRE(test({3, 7}, {-5, -4}, 3));
}

TEST_CASE("area::min_x()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.min_x()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 0));
  REQUIRE(test({-3, -4}, {-5, 7}, -5));
  REQUIRE(test({3, -7}, {5, -4}, 3));
}

TEST_CASE("area::max_y()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.max_y()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 5));
  REQUIRE(test({-3, -4}, {-5, 7}, 7));
  REQUIRE(test({3, -7}, {5, -4}, -4));
}

TEST_CASE("area::min_y()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.min_y()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 0));
  REQUIRE(test({-3, -4}, {-5, 7}, -4));
  REQUIRE(test({3, -7}, {5, -4}, -7));
}

TEST_CASE("area::width()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.width()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 6));
  REQUIRE(test({0, 0}, {5, 10}, 6));
  REQUIRE(test({0, 0}, {10, 5}, 11));
}

TEST_CASE("area::height()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.height()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 6));
  REQUIRE(test({0, 0}, {5, 10}, 11));
  REQUIRE(test({0, 0}, {10, 5}, 6));
}

TEST_CASE("area::size()", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int expected) {
    const int result{area{corner1, corner2}.size()};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 36));
  REQUIRE(test({0, 0}, {5, 10}, 66));
  REQUIRE(test({0, 0}, {10, 5}, 66));
}

TEST_CASE("area::has_x(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int x, const bool expected) {
    const bool result{area{corner1, corner2}.has_x(x)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 0, true));
  REQUIRE(test({0, 0}, {5, 5}, 3, true));
  REQUIRE(test({0, 0}, {5, 5}, 5, true));
  REQUIRE(test({0, 0}, {10, 5}, 9, true));
  REQUIRE(test({0, 0}, {5, 5}, -1, false));
  REQUIRE(test({0, 0}, {5, 5}, 6, false));
}

TEST_CASE("area::has_y(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const int y, const bool expected) {
    const bool result{area{corner1, corner2}.has_y(y)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, 0, true));
  REQUIRE(test({0, 0}, {5, 5}, 3, true));
  REQUIRE(test({0, 0}, {5, 5}, 5, true));
  REQUIRE(test({0, 0}, {5, 10}, 9, true));
  REQUIRE(test({0, 0}, {5, 5}, -1, false));
  REQUIRE(test({0, 0}, {5, 5}, 6, false));
}

TEST_CASE("area::has(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const bool expected) {
    const bool result{area{corner1, corner2}.has(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {3, 4}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 5}, true));
  REQUIRE(test({0, 0}, {5, 10}, {5, 6}, true));
  REQUIRE(test({0, 0}, {5, 5}, {-1, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {6, 6}, false));
  REQUIRE(test({0, 0}, {5, 5}, {0, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 0}, false));
  REQUIRE(test({0, 0}, {5, 5}, {6, 0}, false));
  REQUIRE(test({0, 0}, {5, 5}, {0, 6}, false));
  REQUIRE(test({0, 0}, {5, 10}, {6, 6}, false));
}

TEST_CASE("area::on_x(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const bool expected) {
    const bool result{area{corner1, corner2}.on_x(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {0, 1}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 1}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 0}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {5, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, 1}, false));
}

TEST_CASE("area::on_y(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const bool expected) {
    const bool result{area{corner1, corner2}.on_y(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {0, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {5, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {5, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {1, 1}, false));
}

TEST_CASE("area::on_bound(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const bool expected) {
    const bool result{area{corner1, corner2}.on_bound(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {0, 1}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 4}, true));
  REQUIRE(test({0, 0}, {5, 5}, {4, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 0}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {2, 3}, false));
}

TEST_CASE("area::on_corner(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const bool expected) {
    const bool result{area{corner1, corner2}.on_corner(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {5, 5}, {0, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {0, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 0}, true));
  REQUIRE(test({0, 0}, {5, 5}, {5, 5}, true));
  REQUIRE(test({0, 0}, {5, 5}, {1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {-1, 5}, false));
  REQUIRE(test({0, 0}, {5, 5}, {5, 1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {5, -1}, false));
  REQUIRE(test({0, 0}, {5, 5}, {2, 3}, false));
}

TEST_CASE("area::wrap(const pos<U>&)", tag) {
  auto test = [](const pos<int>& corner1, const pos<int>& corner2, const pos<int>& p, const pos<int>& expected) {
    const pos result{area{corner1, corner2}.wrap(p)};
    return result == expected;
  };

  REQUIRE(test({0, 0}, {6, 6}, {0, 0}, {0, 0}));
  REQUIRE(test({0, 0}, {6, 6}, {1, 1}, {1, 1}));
  REQUIRE(test({0, 0}, {6, 6}, {2, 2}, {2, 2}));
  REQUIRE(test({0, 0}, {6, 6}, {3, 3}, {3, 3}));
  REQUIRE(test({0, 0}, {6, 6}, {6, 6}, {6, 6}));
  REQUIRE(test({0, 0}, {6, 6}, {3, 7}, {3, 0}));
  REQUIRE(test({0, 0}, {6, 6}, {7, 3}, {0, 3}));
  REQUIRE(test({0, 0}, {6, 7}, {8, 10}, {1, 2}));
  REQUIRE(test({0, 0}, {6, 6}, {2, -3}, {2, 4}));
  REQUIRE(test({0, 0}, {6, 6}, {-3, 2}, {4, 2}));
  REQUIRE(test({0, 0}, {6, 7}, {-3, -8}, {4, 0}));
  REQUIRE(test({0, 0}, {6, 6}, {-1, -1}, {6, 6}));
  REQUIRE(test({0, 0}, {6, 6}, {-1, -2}, {6, 5}));
}

TEST_CASE("area::wrap(Rng&&)", tag) {
  constexpr area sut{pos{0, 0}, pos{6, 6}};
  const std::vector<pos<int>> inputs{ {0, 0}, {1, 1}, {3, 7}, {7, 3}, {8, 10}, {2, -3}, {-3, 2} };
  const std::vector<pos<int>> expected{ {0, 0}, {1, 1}, {3, 0}, {0, 3}, {1, 3}, {2, 4}, {4, 2} };
  auto wrapped{sut.wrap(inputs)};
  const std::vector results(std::ranges::begin(wrapped), std::ranges::end(wrapped));

  REQUIRE(expected == results);
}

TEST_CASE("area::filter(Rng&&)", tag) {
  constexpr area sut{pos{0, 0}, pos{5, 5}};
  const std::vector<pos<int>> inputs{ {0, 0}, {1, 3}, {5, 5}, {-1, -1}, {0, -1}, {-1, 0}, {5, 6}, {6, 5} };
  const std::vector<pos<int>> expected{ {0, 0}, {1, 3}, {5, 5} };
  auto filtered{sut.filter(inputs)};
  const std::vector results(std::ranges::begin(filtered), std::ranges::end(filtered));

  REQUIRE(expected == results);
}

TEST_CASE("area::operator==(const area&)", tag) {
  REQUIRE(area{pos{0, 0}, pos{5, 5}} == area{pos{0, 0}, pos{5, 5}});
  REQUIRE(area{pos{0, 0}, pos{5, 5}} == area{pos{5, 5}, pos{0, 0}});
  REQUIRE(area{pos{0, 0}, pos{5, 5}} == area{pos{0, 5}, pos{5, 0}});
  REQUIRE(area{pos{0, 0}, pos{5, 5}} == area{pos{5, 0}, pos{0, 5}});
  REQUIRE(area{pos{0, 0}, pos{5, 5}} == area{pos{5, 5}, pos{10, 10}});
  REQUIRE(area{pos{0, 0}, pos{5, 10}} == area{pos{5, 10}, pos{10, 20}});
  REQUIRE(area{pos{0, 0}, pos{5, 6}} != area{pos{0, 5}, pos{5, 0}});
  REQUIRE(area{pos{0, 0}, pos{5, 10}} != area{pos{5, 10}, pos{10, 21}});
}

TEST_CASE("area::operator<(const area&)", tag) {
  REQUIRE(area{pos{0, 0}, pos{5, 5}} <= area{pos{0, 0}, pos{5, 5}});
  REQUIRE(area{pos{0, 0}, pos{5, 5}} >= area{pos{0, 0}, pos{5, 5}});
  REQUIRE(area{pos{0, 0}, pos{5, 10}} >= area{pos{5, 10}, pos{10, 20}});
  REQUIRE(area{pos{0, 0}, pos{5, 10}} <= area{pos{5, 10}, pos{10, 20}});
  REQUIRE(area{pos{0, 0}, pos{5, 6}} > area{pos{0, 0}, pos{5, 5}});
  REQUIRE(area{pos{0, 0}, pos{5, 6}} < area{pos{0, 0}, pos{5, 7}});
}
