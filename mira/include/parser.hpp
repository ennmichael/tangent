#pragma once

#include "program_text.hpp"
#include "functions.hpp"
#include <functional>
#include <sstream>
#include <string>

namespace Tangent {
namespace Mira {

using Filter = Program_text (*)(const Program_text&);
using Filtered_program_text = Program_text;

class Filters_to_apply {
public:
  void add_filter(Filter);
  Program_text apply_to(Program_text) const;

private:
  std::vector<Filter> filters_;
};

Program_text whitespace_filter(const Program_text&);
Program_text parentheses_filter(const Program_text&);

// TODO dot-syntax filter?

class Tokenizer {
public:
  explicit Tokenizer(const Filtered_program_text&);
  
  Program_text current_token() const;
  Tokenizer advanced() const;
  bool done() const;

private:
  using Program_text_stringstream = std::basic_stringstream<
    Program_text::value_type>;
  
  Program_text current_token_;
  Program_text remaining_text_;
};

}
}

