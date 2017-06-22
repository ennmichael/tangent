#pragma once

#include "program_text.hpp"
#include "number.hpp"
#include <vector>
#include <functional>
#include <unordered_map>
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

struct Function { // TODO name shouldn't be part of this
  Program_text name;
  Parameter_names parameter_names;
  Function_body body;
};

class Function_table {
public:
  boost::optional<Thunk> thunk_for_function(
    const Function_name&,
    const Parameter_values&) const;
  void add_function(const Function&);

private:
  boost::optional<Function> find_function_by_name(const Function_name&) const;

  std::vector<Function> functions_;
};

class Functions_visible_inside_body {
public:
  Functions_visible_inside_body(Outer_function_table, Inner_function_table);
  
  boost::optional<Thunk> thunk_for_function(
    const Function_name&,
    const Parameter_values&) const;

private:
  Outer_function_table outer_;
  Inner_function_table inner_;
};

class Thunk {
public:
  Thunk(const Function&, const Outer_function_table&, const Parameter_values&);
  
  Number execute() const;

private:
  Functions_visible_inside_body visible_functions_;
  Function_body body_to_execute_;
};

Function_table parameter_function_table(
  const Parameter_names&,
  const Parameter_values&);
}
}

