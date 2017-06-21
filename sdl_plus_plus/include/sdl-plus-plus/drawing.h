#pragma once

#include "SDL2/SDL.h"
#include "boost/functional/hash.hpp"
#include "boost/operators.hpp"
#include "boost/optional.hpp"
#include "resource.h"
#include <cmath>
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace Sdl {
using Color = SDL_Color;
using Colour = Color;
using Rectangle = SDL_Rect;

struct Point;
using Point_vector = std::vector<Point>;

struct Point
  : private boost::equality_comparable<
      Point,
      boost::addable<
        Point, boost::subtractable<
                 Point, boost::multipliable<Point, boost::dividable<Point>>>>> {
  static Point origin() noexcept;

  Point() = default;
  Point(int, int) noexcept;

  int x;
  int y;

  bool operator==(Point) const noexcept;
  Point& operator+=(Point) noexcept;
  Point& operator-=(Point) noexcept;
  Point& operator*=(Point) noexcept;
  Point& operator/=(Point) noexcept;
};

std::ostream& operator<<(std::ostream&, Point);

struct Size
  : private boost::equality_comparable<
      Size,
      boost::addable<
        Size, boost::subtractable<
                Size, boost::multipliable<Size, boost::dividable<Size>>>>> {
  Size() = default;
  Size(int, int) noexcept;

  int width;
  int height;

  bool operator==(Size) const noexcept;
  Size& operator+=(Size) noexcept;
  Size& operator-=(Size) noexcept;
  Size& operator*=(Size) noexcept;
  Size& operator/=(Size) noexcept;
};

std::ostream& operator<<(std::ostream&, Size);

double distance_between_points(Point, Point) noexcept;

namespace internal {
int difference(int, int) noexcept;
double pythagorean_theoreme(double, double) noexcept;
}

struct Message_box {
  enum class Type : Uint32 {
    Basic = 0,
    Error = SDL_MESSAGEBOX_ERROR,
    Warning = SDL_MESSAGEBOX_WARNING,
    Info = SDL_MESSAGEBOX_INFORMATION
  };

  std::string title;
  std::string content;
  Type type = Type::Basic;
};

void show_message_box(const Message_box&);

namespace Premade_colors {
constexpr Color red(Uint8 amount = 255, Uint8 alpha = 255) noexcept {
  return {amount, 0, 0, alpha};
}

constexpr Color green(Uint8 amount = 255, Uint8 alpha = 255) noexcept {
  return {0, amount, 0, alpha};
}

constexpr Color blue(Uint8 amount = 255, Uint8 alpha = 255) noexcept {
  return {0, 0, amount, alpha};
}

constexpr Color yellow(Uint8 amount = 255, Uint8 alpha = 255) noexcept {
  return {amount, amount, 0, alpha};
}

constexpr Color black(Uint8 alpha = 255) noexcept { return {0, 0, 0, alpha}; }

constexpr Color white(Uint8 alpha = 255) noexcept {
  return {255, 255, 255, alpha};
}
}

namespace Premade_colours = Premade_colors;

struct Rectangle_points {
  Point upper_left;
  Point lower_right;
};

Size rectangle_size(Rectangle_points) noexcept;
Rectangle make_rectangle(Rectangle_points) noexcept;
Rectangle make_rectangle(Point, Size) noexcept;

namespace internal {
template <class T> struct Strong_typedef {
  explicit Strong_typedef(const T& value) : value(value) {}

  T value;
};
}

struct Angle_rad : private internal::Strong_typedef<double> {
  static Angle_rad pi() noexcept;

  using Strong_typedef::Strong_typedef;
  using Strong_typedef::value;
};

struct Angle_degrees : private internal::Strong_typedef<double> {
  using Strong_typedef::Strong_typedef;
  using Strong_typedef::value;
};

struct Line {
  Line() = default;
  Line(Point, Angle_rad, int) noexcept;
  Line(Point, Point) noexcept;

  Point from = Point();
  Point to = Point();
};

std::ostream& operator<<(std::ostream&, Line);

using Filename = std::string;

class Texture {
public:
  static Texture create_from_raw_surface(SDL_Renderer&, SDL_Surface&);

  Size size() const;
  void draw_to_raw_renderer(SDL_Renderer&, Point);

private:
  explicit Texture(SDL_Renderer&, SDL_Surface&);

  Rectangle create_source_rectangle() const noexcept;
  Rectangle create_destination_rectangle(Point) const noexcept;

  struct Deleter {
    void operator()(SDL_Texture*) noexcept;
  };

  std::unique_ptr<SDL_Texture, Deleter> texture_ptr_;
};

class Surface {
public:
  static Surface load_from_file(const Filename&);

  Texture get_texture_from_raw_renderer(SDL_Renderer&);

private:
  explicit Surface(const Filename&);

  struct Deleter {
    void operator()(SDL_Surface*) noexcept;
  };

  std::unique_ptr<SDL_Surface, Deleter> surface_ptr_;
};

enum class Color_filling : bool { filled, none };

class Renderer {
public:
  explicit Renderer(SDL_Window&);

  Texture load_texture(const Filename&);
  void set_blend_mode(SDL_BlendMode);
  void render_present();
  void render_clear(Color);

  void draw_texture(Texture&, Point);
  void draw_line(Line, Color);
  void draw_rectangle(Rectangle, Color, Color_filling);

private:
  void set_draw_color(Color);
  void draw_filled_rectangle(Rectangle);
  void draw_empty_rectangle(Rectangle);
  Color get_draw_color() const;

  struct Deleter {
    void operator()(SDL_Renderer*) noexcept;
  };
  std::unique_ptr<SDL_Renderer, Deleter> renderer_ptr_;
};

class Image_cache {
public:
  void load_image(const Filename&, Renderer&);
  bool image_loaded(const Filename&) const noexcept;
  Texture& get_image_texture(const Filename&) noexcept;
  const Texture& get_image_texture(const Filename&) const noexcept;

private:
  std::unordered_map<Filename, Texture> textures_;
};

struct Window_properties {
  static Window_properties default_values();
  static Window_properties default_values_with_title(std::string);

  Size size;
  Point position;
  std::string title;
};

class Draw_commands {
public:
  void add_image_draw_command(Texture&, Point);
  void add_line_draw_command(Line, Color);
  void add_rectangle_draw_command(Rectangle, Color, Color_filling);

  void execute(Renderer&);

private:
  class Draw_command {
  public:
    Draw_command() = default;
    Draw_command(const Draw_command&) = delete;
    Draw_command(Draw_command&&) = delete;
    Draw_command& operator=(const Draw_command&) = delete;
    Draw_command& operator=(Draw_command&&) = delete;

    virtual void execute(Renderer&) const = 0;
    virtual ~Draw_command() = default;
  };

  class Image_draw_command;
  class Line_draw_command;
  class Rectangle_draw_command;

  std::vector<std::unique_ptr<Draw_command>> draw_commands_;
};

class Window {
public:
  explicit Window(const Window_properties&, Uint32 = 0);

  void draw_image(const Filename&, Point);
  void draw_line(Line, Color);
  void draw_rectangle(Rectangle, Color, Color_filling);

  void redraw(Color);

private:
  struct Deleter {
    void operator()(SDL_Window*) noexcept;
  };

  using Unique_window = std::unique_ptr<SDL_Window, Deleter>;

  void cache_image(const Filename&);
  void execute_draw_commands();
  static Unique_window create_checked_window(const Window_properties&, Uint32);
  static Unique_window create_unchecked_window(const Window_properties&,
                                               Uint32);

  Image_cache image_cache_;
  Unique_window window_ptr_;
  Renderer renderer_;
  Draw_commands draw_commands_;
};
}

namespace std {
template <> class hash<Sdl::Point> {
public:
  std::size_t operator()(Sdl::Point point) const noexcept {
    std::size_t seed = 0;
    boost::hash_combine(seed, point.x);
    boost::hash_combine(seed, point.y);
    return seed;
  }
};
}

namespace std {
template <> class hash<Sdl::Size> {
public:
  std::size_t operator()(Sdl::Size size) const noexcept {
    std::size_t seed = 0;
    boost::hash_combine(seed, size.width);
    boost::hash_combine(seed, size.height);
    return seed;
  }
};
}

