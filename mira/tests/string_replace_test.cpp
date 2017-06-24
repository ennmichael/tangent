#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/utils.hpp"
#include <string>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Utils = Tangent::Mira::Utils;
  
  const auto test_replacement = [](
    const std::string& given, 
    const std::string& replace_pattern, 
    const std::string& new_pattern,
    const std::string& expected)
  {
    const auto result = Utils::string_replace(
      given, 
      replace_pattern, 
      new_pattern);
    BOOST_CHECK_EQUAL(result, expected);
  };

  test_replacement("abracadabra", "ab", "ba", "baracadbara");
  test_replacement("a b  c     d\te", "\\s+", " ", "a b c d e");
}

