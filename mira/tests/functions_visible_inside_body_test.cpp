#define BOOST_TEST_MODULE functions_tests
#include "boost/test/unit_test.hpp"

#include "../include/functions.hpp"
#include <iostream>

BOOST_AUTO_TEST_CASE(functions_visible_inside_body_test)
{
  namespace Mira = Tangent::Mira;
  
  constexpr auto function1_name = "f1";
  constexpr auto function2_name = "f2";
  constexpr auto function3_name = "f3";

  Mira::Function_table outer;
  outer.add_function({function1_name, {}, [](auto) -> Mira::Number {
    return 1;
  }});
  outer.add_function({function2_name, {}, [](auto) -> Mira::Number {
    return 2;
  }});

  Mira::Function_table inner;
  inner.add_function({function3_name, {}, [](auto) -> Mira::Number {
    return 3;
  }});

  Mira::Functions_visible_inside_body visible_functions(outer, inner);
  const auto f1_thunk 
    = visible_functions.thunk_for_function(function1_name, {});
  const auto f2_thunk
    = visible_functions.thunk_for_function(function2_name, {});
  const auto f3_thunk
    = visible_functions.thunk_for_function(function3_name, {});
  
  BOOST_CHECK(f1_thunk != boost::none);
  BOOST_CHECK(f2_thunk != boost::none);
  BOOST_CHECK(f3_thunk != boost::none);

  BOOST_CHECK_EQUAL(f1_thunk->execute(), 1);
  BOOST_CHECK_EQUAL(f2_thunk->execute(), 2);
  BOOST_CHECK_EQUAL(f3_thunk->execute(), 3);
}

