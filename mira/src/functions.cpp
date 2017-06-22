#include "functions.hpp"
#include "exceptions.hpp"
#include "utils.hpp"
#include <utility>
#include <algorithm>

namespace Tangent {
namespace Mira {

Number Function::execute(const Parameter_values& values) const
{
  const Functions_visible_inside_body visible_functions(
    closure, 
    parameter_function_table(parameter_names, values)
  );
  return body(visible_functions);
}

Function_table parameter_function_table(
  const Parameter_names& names,
  const Parameter_values& values)
{
  if (names.size() != values.size())
    throw User_errors::Incorrect_number_of_parameter_values();
  
  Function_table result;

  Utils::adjacent_for_each(
    names.cbegin(),
    names.cend(),
    values.cbegin(),
    values.cend(),
    [&result](const auto& name, const auto& value)
    {
      result.add_function({
        name,
        value.parameter_names,
        value.body
      });
    });

  return result;
}

std::shared_ptr<const Function> Function_table::get_function(
  const Function_name& name) const
{
  if (functions_.count(name))
    return functions_.at(name);
  return nullptr;
}

void Function_table::add_function(
  const Function_name& name,
  const std::shared_ptr<const Function>& function)
{
  functions_[name] = function;
}

Functions_visible_inside_body::Functions_visible_inside_body(
  Outer_function_table outer,
  Inner_function_table inner)
  : outer_(std::move(outer))
  , inner_(std::move(inner))
{
}

<Function> Functions_visible_inside_body::get_function(
  const Function_name& name) const
{
  const auto get_required_function_from_table =
  [&](const auto& table)
  {
    return table.get_function(name);
  };
  
  if (const auto outer_function = get_required_function_from_table(outer_))
    return *outer_function;
  return get_required_function_from_table(inner_);
}

}
}

