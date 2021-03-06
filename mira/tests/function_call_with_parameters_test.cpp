#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function_name = "f";

  Mira::Function_table function_table;
  
  function_table.add_function(
    function_name, 
    Mira::Function({"n"},
    [](const auto& visible_functions) -> Mira::Number 
    {
      const auto n = visible_functions.function_named("n");
      return n.result(visible_functions.outer_table) * 
             n.result(visible_functions.outer_table);
    }
  ));

  function_table.add_function(
    "2",
    Mira::Function({},
    [](const auto&) -> Mira::Number
    {
      return 2;
    }));
  
  auto function = function_table.function_named(function_name);
  const auto two = function_table.function_named("2");

  function = function.curried({two});
  BOOST_CHECK_EQUAL(function.result(function_table), 4);
  BOOST_CHECK_EQUAL(
    function.result(function_table),
    function.result(function_table)
  );
}

