#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/utils.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Utils = Tangent::Mira::Utils;
  
  std::vector<int> vec1 {1, 2, 3};
  std::vector<int> vec2 {1, 2, 3};

  std::vector<int> result;

  Utils::adjacent_for_each(
    vec1.cbegin(), 
    vec1.cend(),
    vec2.begin(),
    vec2.end(),
    [&result](auto first, auto& second){
      second *= 10;
      result.push_back(first+second);
    });

  std::vector<int> vec1_expected {1, 2, 3};
  std::vector<int> vec2_expected {10, 20, 30};
  std::vector<int> result_expected {11, 22, 33};

  BOOST_CHECK_EQUAL(vec1, vec1_expected);
  BOOST_CHECK_EQUAL(vec2, vec2_expected);
  BOOST_CHECK_EQUAL(result, result_expected);
}

