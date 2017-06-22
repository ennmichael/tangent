#pragma once

#include "boost/optional.hpp"
#include <algorithm>
#include <iterator>

namespace Tangent {
namespace Mira {
namespace Utils {

template <class Iter, class Comp>
boost::optional<typename std::iterator_traits<Iter>::value_type>
optionally_find_if(Iter from, Iter to, const Comp& comp)
{
  const auto i = std::find_if(from, to, comp);
  if (i == to)
    return boost::none;
  return *i;
}

template <class Iter1, class Iter2, class Callback>
void adjacent_for_each(
  Iter1 from1, Iter1 to1,
  Iter2 from2, Iter2 to2,
  const Callback& callback)
{ // TODO test this function
  const auto size = std::min(
    std::distance(from1, to1), 
    std::distance(from2, to2));

  for (std::size_t _ = 0; _ < size; ++_, ++from1, ++from2)
    callback(*from1, *from2);
}

}
}
}

