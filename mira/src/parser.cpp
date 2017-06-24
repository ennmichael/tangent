#include "parser.hpp"
#include "utils.hpp"
#include <utility>

namespace Tangent {
namespace Mira {

void Filters_to_apply::add_filter(Filter f)
{
  filters_.push_back(f);
}

Program_text Filters_to_apply::apply_to(Program_text text) const
{
  for (const auto filter : filters_)
    text = filter(text);
  return text;
}

Program_text whitespace_filter(const Program_text& text)
{
  return Utils::string_replace(text, "\\s+", " ");
}

Program_text parentheses_filter(const Program_text& text)
{
  auto result = text;
  const auto replace_character = 
  [&](auto original, auto replaced)
  {
    result = Utils::string_replace(result, original, replaced);
  };

  replace_character("\\{", "(");
  replace_character("\\[", "(");
  replace_character("\\}", ")");
  replace_character("\\]", ")");

  return result;
}

Tokenizer::Tokenizer(const Filtered_program_text& text)
  : current_token_(
      text.cbegin(), Utils::first_space(text.cbegin(), text.cend()))
  , remaining_text_(
      Utils::first_space(text.cbegin(), text.cend())+1, text.cend())
{
}

Program_text Tokenizer::current_token() const
{
  return current_token_;
}

Tokenizer Tokenizer::advanced() const
{
  return Tokenizer(remaining_text_);
}

bool Tokenizer::done() const
{
  return remaining_text_ == "";
}

}
}

