#ifndef INPUT_H
#define INPUT_H

#include "SDL2/SDL.h"

#include "keymap.h"
#include "camera.h"

#define kMaxInputKeys 2048

enum class LoopState;

struct InputData {

  InputData(): key_flag{false}, keys{false}  {}  //check if it really initializes

  bool key_flag[kMaxInputKeys];
  bool keys[kMaxInputKeys];
};


class Input {

 public:

  void ReadInput();
  bool ProcessInput(Camera<float>* camera);

 private:

  void ReadMouseButton();
  void ReadMouseMotion();
  void ReadKeyboard();

  SDL_Event event;
  InputData input;
};


#endif // INPUT_H
