#include "functions.hpp"
#include "exceptions.hpp"
#include "utils.hpp"
#include <utility>
#include <algorithm>

namespace Tangent {
namespace Mira {

boost::optional<Thunk> Function_table::thunk_for_function(
  const Function_name& name, 
  const Parameter_values& values) const
{ 
  if (const auto function = find_function_by_name(name)) {
    (void)values; // TODO
    return Thunk(Functions_visible_inside_body({}, {}), function->body);
  }
  
  return boost::none;
}

void Function_table::add_function(const Function& function)
{
  functions_.push_back(function);
}

boost::optional<Function> Function_table::find_function_by_name(
  const Function_name& name) const
{
  const auto function_name_comparer = [&name](const Function& function)
  {
    return function.name == name;
  };
  
  return Utils::optionally_find_if(
    functions_.cbegin(), 
    functions_.cend(), 
    function_name_comparer);
}

Functions_visible_inside_body::Functions_visible_inside_body(
  Outer_function_table outer,
  Inner_function_table inner)
  : outer_(std::move(outer))
  , inner_(std::move(inner))
{
}

boost::optional<Thunk> Functions_visible_inside_body::thunk_for_function(
  const Function_name& name,
  const Parameter_values& parameter_values) const
{
  const auto find_required_thunk_from_table = 
  [&](const auto& table)
  {
    return table.thunk_for_function(name, parameter_values);
  };
  
  if (const auto outer_thunk = find_required_thunk_from_table(outer_)) {
    return *outer_thunk;
  }
  return find_required_thunk_from_table(inner_);
}

Thunk::Thunk(
  const Function& function,
  const Parameter_values& parameter_values)
  : visible_functions_(std::move(visible_functions))
  , body_to_execute_(std::move(body_to_execute))
{
}

Number Thunk::execute() const 
{
  return body_to_execute_(visible_functions_);
}

Function_table parameter_function_table(
  const Parameter_names& names,
  const Parameter_values& values)
{
  if (names.size() != values.size())
    throw User_errors::Incorrect_number_of_parameter_values();

  // adjacent_for_each
}

}
}

