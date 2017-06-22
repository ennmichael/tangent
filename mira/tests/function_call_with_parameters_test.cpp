#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function_name = "f";

  Mira::Function_table function_table;
  
  function_table.add_function({
  function_name, 
  {"a"},
  [](const auto& parameter_function_table) -> Mira::Number 
  {
    const auto a = parameter_function_table.thunk_for_function("a", {});
    BOOST_CHECK(a != boost::none);
    return a->execute() * a->execute();
  }});

  function_table.add_function({
    "2",
    {},
    [](const auto&) -> Mira::Number
    {
      return 2;
    }
  });

  // TODO write a double execute checking test
  
  const auto function_thunk = function_table.thunk_for_function(
    function_name,
    {}
  );
  BOOST_CHECK(function_thunk != boost::none);
  BOOST_CHECK_EQUAL(function_thunk->execute(), 4);
}

