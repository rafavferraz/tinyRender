#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>

#include "/code/Math/LinearAlgebra/linear_algebra.h"
#include "/code/Math/Containers/mat4.h"

#define DEFAULT_WINDOW_WIDTH      400
#define DEFAULT_WINDOW_HEIGHT     400
#define DEFAULT_WINDOW_X_POSITION 600
#define DEFAULT_WINDOW_Y_POSITION 600
#define DEFAULT_WINDOW_NAME       "TinyRender"


class Window {
 public:

  Window();
  ~Window();

  void Init();

  void setWindowSize(const int& width, const int& height);
  void setWindowName(const std::string& name);
  void setWindowPosition(const int& x_position, const int& y_position);
  SDL_Window* getWindow();

 private:
  int screen_width;
  int screen_height;
  int screen_x_position;
  int screen_y_position;
  std::string window_name;

  SDL_GLContext gl_context;
  SDL_Window*   window;
};


#endif // WINDOW_H
