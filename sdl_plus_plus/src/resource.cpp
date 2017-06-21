#include "resource.h"
#include "SDL2/SDL_image.h"

namespace Sdl {
const char* Sdl_exception::what() const noexcept { return SDL_GetError(); }

Sdl_system_control::Sdl_system_control(Uint32 flags) {
  internal::error_checking::check_function(SDL_Init(flags));
}

Sdl_system_control::~Sdl_system_control() { SDL_Quit(); }

namespace internal {
namespace error_checking {
void check_function(int function_result) {
  if (function_result != 0)
    throw Sdl_exception{};
}
}
}
}
