#include "window.h"

Window::Window(): screen_width(DEFAULT_WINDOW_WIDTH),
                  screen_height(DEFAULT_WINDOW_HEIGHT),
                  screen_x_position(DEFAULT_WINDOW_X_POSITION),
                  screen_y_position(DEFAULT_WINDOW_Y_POSITION),
                  window_name(DEFAULT_WINDOW_NAME) {}

Window::~Window () {

  SDL_DestroyWindow(window);
  SDL_GL_DeleteContext(gl_context);
  SDL_Quit ();
}

void Window::setWindowSize(const int& width, const int& height) {
  screen_width = width;
  screen_height = height;
}

void Window::setWindowPosition(const int& x_position, const int& y_position) {
  screen_x_position = x_position;
  screen_y_position = y_position;
}

void Window::setWindowName(const std::string& name) {
  window_name = name;
}

SDL_Window* Window::getWindow() {
  return window;
}

void Window::Init () {

  SDL_Init (SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow (window_name.c_str(),
                             screen_x_position,
                             screen_y_position,
                             screen_width, 
                             screen_height,
                             SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

  gl_context = SDL_GL_CreateContext(window);

  //v_sync
  SDL_GL_SetSwapInterval(0);

  if (window != NULL)
      std::cout<<"SDL window initialized."<<"\n\n";
  else
      std::cout<<"SDL window failed to initialize."<<std::endl;
}