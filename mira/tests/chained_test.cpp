#define BOOST_TEST_MODULE utils_tests
#include "boost/test/unit_test.hpp"

#include "../include/utils.hpp"

BOOST_AUTO_TEST_CASE(function_defintion_test)
{
  namespace Utils = Tangent::Mira::Utils;
  const std::vector<int> v1 {1, 2, 3, 4};
  const std::vector<int> v2 {5, 6, 7};
  const auto result = Utils::chained(v1, v2);
  const std::vector<int> expected {1, 2, 3, 4, 5, 6, 7};
  BOOST_CHECK(result == expected);
}

