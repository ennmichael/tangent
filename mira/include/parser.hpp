#pragma once

#include "program_text.hpp"
#include "functions.hpp"
#include "boost/optional.hpp"
#include <functional>

namespace Tangent {
namespace Mira {
namespace Program_text_interpreter {

using Function_definition = std::function<void(Function_table&)>;

class Tokenizer {
public:
  explicit Tokenizer(Program_text text);
  
  Program_text next_token();
  bool done() const;
};

}
}
}

