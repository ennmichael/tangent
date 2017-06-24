#define BOOST_TEST_MODULE parser_tests
#include "boost/test/unit_test.hpp"

#include "../include/parser.hpp"

BOOST_AUTO_TEST_CASE(filters_test)
{
  namespace Mira = Tangent::Mira;
  
  const Mira::Program_text text = 
    "{myFun  1 1 [add 25\t(multiply 10 10)]}";
  
  const auto with_whitespace_filtered = Mira::whitespace_filter(text);
  BOOST_CHECK_EQUAL(
    with_whitespace_filtered,
    "{myFun 1 1 [add 25 (multiply 10 10)]}"
  );

  const auto with_parens_filtered = Mira::parentheses_filter(text);
  BOOST_CHECK_EQUAL(
    with_parens_filtered,
    "(myFun  1 1 (add 25\t(multiply 10 10)))"
  );

  Mira::Filters_to_apply filters;
  filters.add_filter(Mira::whitespace_filter);
  filters.add_filter(Mira::parentheses_filter);

  const auto with_all_filtered = filters.apply_to(text);
  BOOST_CHECK_EQUAL(
    with_all_filtered,
    "(myFun 1 1 (add 25 (multiply 10 10)))"
  );
}

