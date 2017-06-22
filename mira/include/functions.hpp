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
struct Thunk;
class Function_table;

using Function_name = Program_text;
using Function_body = Number(*)(const Functions_visible_inside_body&);
using Parameter_names = std::vector<Program_text>;
using Parameter_values = std::vector<Function>;
using Outer_function_table = Function_table;
using Inner_function_table = Function_table;

class Function_table {
public:
  std::shared_ptr<const Function> get_function(const Function_name&) const;
  void add_function(
    const Function_name&, 
    const std::shared_ptr<const Function>&);
 
private: 
  std::unordered_map<Function_name, std::shared_ptr<Function>> functions_;
};

struct Function {
  Parameter_names parameter_names;
  Function_body body;
  Function_table closure;

  Number execute(const Parameter_values&) const;
};

Function_table parameter_function_table(
  const Parameter_names&,
  const Parameter_values&);

class Functions_visible_inside_body {
public:
  Functions_visible_inside_body(Outer_function_table, Inner_function_table);
  
  std::shared_ptr<const Function> get_function(const Function_name&) const;

private:
  Outer_function_table outer_;
  Inner_function_table inner_;
};

}
}

