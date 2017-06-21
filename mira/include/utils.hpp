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

}
}
}

