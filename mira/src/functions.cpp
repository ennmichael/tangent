#include "functions.hpp"
#include "exceptions.hpp"
#include "utils.hpp"
#include <utility>
#include <algorithm>

namespace Tangent {
namespace Mira {

Function::Function(
  Parameter_names parameter_names,
  Function_body body)
  : parameter_names_(std::move(parameter_names))
  , body_(body)
{
}

Number Function::result(const Function_table& function_table) const
{
  assert_proper_parameters();
  const Functions_visible_inside_body visible_functions(
    function_table, 
    parameter_function_table()
  );
  return body_(visible_functions);
}

Function Function::curried(const Parameter_values& values_to_curry) const
{
  auto result = *this;
  result.curried_parameter_values_ = Utils::chained(
    curried_parameter_values_, values_to_curry
  );
  return result;
}

void Function::assert_proper_parameters() const
{
  if (parameter_names_.size() != curried_parameter_values_.size())
    throw User_errors::Incorrect_number_of_parameter_values();
}

Function_table Function::parameter_function_table() const
{
  Function_table result;

  Utils::adjacent_for_each(
    parameter_names_.cbegin(),
    parameter_names_.cend(),
    curried_parameter_values_.cbegin(),
    curried_parameter_values_.cend(),
    [&result](const auto& name, const auto& value)
    {
      result.add_function(name, value);
    });

  return result; 
}

boost::optional<Function> Function_table::function_named(
  const Function_name& name) const
{
  if (functions_.count(name))
    return functions_.at(name);
  return boost::none;
}

void Function_table::add_function(
  const Function_name& name,
  const Function& function)
{
  if (functions_.find(name) != functions_.end())
    throw User_errors::Redefining_existing_function();
  functions_.insert(std::make_pair(name, function));
}

Functions_visible_inside_body::Functions_visible_inside_body(
  Outer_function_table outer,
  Inner_function_table inner)
  : outer_(std::move(outer))
  , inner_(std::move(inner))
{
}

boost::optional<Function> Functions_visible_inside_body::function_named(
  const Function_name& name) const
{
  const auto get_required_function_from_table =
  [&](const auto& table)
  {
    return table.function_named(name);
  };
  
  if (const auto inner_function = get_required_function_from_table(inner_))
    return *inner_function;
  return get_required_function_from_table(outer_);
}

Outer_function_table Functions_visible_inside_body::outer() const
{
  return outer_;
}

}
}

