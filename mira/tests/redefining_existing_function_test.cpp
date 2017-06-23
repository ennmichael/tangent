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

  const auto add_double_definition = [&]()
  {
    tbl.add_function(function_name, Mira::Function(
      {}, [](auto) -> Mira::Number 
      {
        return 1;
      }));
    tbl.add_function(function_name, Mira::Function(
      {}, [](auto) -> Mira::Number 
      {
        return 2;
      }));
  };

  BOOST_CHECK_THROW(
    add_double_definition(), 
    Mira::User_errors::Redefining_existing_function);
}

