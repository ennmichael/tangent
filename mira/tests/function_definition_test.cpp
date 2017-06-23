#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"

BOOST_AUTO_TEST_CASE(function_defintion_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function_name = "f1";

  Mira::Function_table tbl;
  tbl.add_function(
    function_name, 
    Mira::Function(
      {},
      [](auto _) -> Mira::Number {
        return 1;
      }
  ));

  auto function = tbl.function_named(function_name);
  BOOST_CHECK_EQUAL(function.result(tbl), 1);
}

