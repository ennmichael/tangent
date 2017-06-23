#pragma once

#include "program_text.hpp"
#include "number.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
#include <memory>
#include "boost/optional.hpp"

namespace Tangent {
namespace Mira {

struct Function;
struct Functions_visible_inside_body;
class Function_table;

using Function_name = Program_text;
using Function_body = Number(*)(const Functions_visible_inside_body&);
// Function_body should take two parameters instead of one?
// Or just ditch encapsulation on Names_visble_inside_function
using Parameter_names = std::vector<Program_text>;
using Parameter_values = std::vector<Function>;
using Outer_function_table = Function_table;
using Inner_function_table = Function_table;

class Function {
public:
  Function(Parameter_names, Function_body);
  
  Number result(const Function_table&) const;
  Function curried(const Parameter_values&) const;
  
private:
  void assert_proper_parameters() const;
  Function_table parameter_function_table() const;

  Parameter_names parameter_names_;
  Parameter_values curried_parameter_values_;
  Function_body body_;
};

class Function_table {
public:
  boost::optional<Function> function_named(const Function_name&) const;
  void add_function(
    const Function_name&, 
    const Function&);
 
private: 
  std::unordered_map<Function_name, Function> functions_;
};

class Functions_visible_inside_body {
public: 
  Functions_visible_inside_body(Outer_function_table, Inner_function_table);
  
  boost::optional<Function> function_named(const Function_name&) const;
  Outer_function_table outer() const;

private:
  Outer_function_table outer_;
  Inner_function_table inner_;
};

}
}

