#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function1_name = "shadowed";
  constexpr auto function2_name = "f2";
  constexpr auto function3_name = "shadowed";

  Mira::Function_table outer;
  outer.add_function(function1_name, Mira::Function(
    {}, [](auto) -> Mira::Number 
    {
      return 1;
    }));
  outer.add_function(function2_name, Mira::Function(
    {}, [](auto) -> Mira::Number 
    {
      return 2;
    }));

  Mira::Function_table inner;
  inner.add_function(function3_name, Mira::Function(
    {}, [](auto) -> Mira::Number 
    {
      return 3;
    }));

  Mira::Functions_visible_inside_body visible_functions{outer, inner};
  const auto f1 = visible_functions.function_named(function1_name);
  const auto f2 = visible_functions.function_named(function2_name);
  const auto f3 = visible_functions.function_named(function3_name);
  
  BOOST_CHECK_EQUAL(f1.result(visible_functions.outer_table), 3);
  BOOST_CHECK_EQUAL(f2.result(visible_functions.outer_table), 2);
  BOOST_CHECK_EQUAL(f3.result(visible_functions.outer_table), 3);
}

