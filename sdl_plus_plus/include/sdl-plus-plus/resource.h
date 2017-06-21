#pragma once

#include "SDL2/SDL.h"
#include <memory>
#include <stdexcept>

namespace Sdl {
class Sdl_exception : public std::exception {
public:
  const char* what() const noexcept override;
};

class Sdl_system_control {
public:
  Sdl_system_control(Uint32 = SDL_INIT_EVERYTHING);
  ~Sdl_system_control();

  Sdl_system_control(const Sdl_system_control&) = delete;
  Sdl_system_control(Sdl_system_control&&) = delete;
  Sdl_system_control& operator=(const Sdl_system_control&) = delete;
  Sdl_system_control& operator=(Sdl_system_control&&) = delete;
};

namespace internal {
namespace error_checking {
template <class T> void check_pointer(const T& ptr) {
  if (ptr == nullptr)
    throw Sdl_exception();
}

void check_function(int);
}
}
}
