#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"
#include "../include/exceptions.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function_name = "f";

  Mira::Function_table tbl;
  
  tbl.add_function(
    function_name, 
    Mira::Function(
    {},
    [](const auto& visible_functions) -> Mira::Number 
    {
      const auto n = visible_functions.function_named("n");
      return n.result(visible_functions.outer_table) * 
             n.result(visible_functions.outer_table);
    }
  ));
  
  const auto function = tbl.function_named(function_name);
  using Expected_throw_type = Mira::User_errors::Function_doesnt_exist; 
  BOOST_CHECK_THROW(
    function.result(tbl), 
    Expected_throw_type
  );

  tbl.add_function(
    "n",
    Mira::Function(
    {},
    [](const auto&) -> Mira::Number
    {
      return 3;
    }
  ));
  
  BOOST_CHECK_EQUAL(function.result(tbl), 9);
}

