#pragma once

#include "parser.hpp"
#include "functions.hpp"

namespace Tangent {
namespace Mira {

struct Function_declaration {
  Program_text function_name;
  Function function;
};

class Interpreter {
public:
  void interpret_line(const Program_text&);

private:
  Function_table function_table_;
};

}
}

