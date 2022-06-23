#pragma once


struct State {

  bool mouse_button_left_press = false;
  bool mouse_button_left_release = true;

  bool mouse_button_middle_press = false;
  bool mouse_button_middle_release = true;

  bool mouse_scroll_up = false;
  bool mouse_scroll_down = false;

  double mouse_scroll_up_offset = 0.0;
  double mouse_scroll_down_offset = 0.0;

  double cursor_x_position = 0.0;
  double cursor_y_position = 0.0;

  double cursor_x_offset = 0.0;
  double cursor_y_offset = 0.0;

  void clear() {

    mouse_button_left_press = false;
    mouse_button_middle_press = false;

    cursor_x_offset = 0.0;
    cursor_y_offset = 0.0;

    mouse_scroll_up = false;
    mouse_scroll_down = false;

    mouse_scroll_up_offset = 0.0;
    mouse_scroll_down_offset = 0.0;
  }

} state;