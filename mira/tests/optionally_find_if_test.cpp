#include "../include/utils.hpp"
#define BOOST_TEST_MODULE mira_tests
#include "boost/test/unit_test.hpp"
#include <vector>

bool is_odd(int n)
{
  return n % 2 != 0;
}

bool is_larger_than_10(int n)
{
  return n > 10;
}

BOOST_AUTO_TEST_CASE(optionally_find_if_test)
{
  namespace Utils = Tangent::Mira::Utils;

  std::vector<int> vec {0, 2, 3, 4, 5, 6};
  
  const auto result = Utils::optionally_find_if(
    vec.cbegin(), 
    vec.cend(),
    is_odd);
  BOOST_CHECK_EQUAL(*result, 3);

  const auto doesnt_exist = Utils::optionally_find_if(
    vec.cbegin(),
    vec.cend(),
    is_larger_than_10);
  BOOST_CHECK(doesnt_exist == boost::none);
}

