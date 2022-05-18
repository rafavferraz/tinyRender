#include "input.h"


//hash table time!!
bool Input::ProcessInput (Camera<float> *camera) {

  bool run_flag = true;

  //one shot type
  if(input.keys[KEY_ESC] || input.keys[WIN_ESC])
    run_flag = false;

  if(input.keys[KEY_a])
    camera->MoveLeft ();
  if(input.keys[KEY_d])
    camera->MoveRight ();
  if(input.keys[KEY_w])
    camera->MoveUp ();
  if(input.keys[KEY_s])
    camera->MoveDown ();
  if(input.keys[KEY_MINUS])
    camera->MoveBackward ();
  if(input.keys[KEY_EQUALS])
    camera->MoveForward ();
  if(input.keys[KEY_5])
    camera->MoveToOrigin ();


  //on-off type
  if(input.keys[KEY_SPACE]) {
    if(!input.key_flag[KEY_SPACE]) {
      //if was off, turn on
// loop_state = LoopState::PAUSE;
      input.key_flag[KEY_SPACE]=true;
      input.keys[KEY_SPACE] = false;
    }
    else {
      //if was on, turn off
// loop_state = LoopState::RUN;
      input.key_flag[KEY_SPACE]=false;
      input.keys[KEY_SPACE] = false;
    }
  }

  return run_flag;
}

void Input::ReadInput () {

  while (SDL_PollEvent(&event)) {

    switch (event.type) {

      case SDL_QUIT:
          input.keys[WIN_ESC]=true; break;

      case SDL_MOUSEMOTION:
          ReadMouseMotion (); break;

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
          ReadMouseButton (); break;

      case SDL_KEYDOWN:
      case SDL_KEYUP:
          ReadKeyboard (); break;

      default:
          break;
    }
  }
}

void Input::ReadMouseButton () {

  switch (event.type) {

    case SDL_MOUSEBUTTONDOWN:
      switch (event.button.button)  {

        case SDL_BUTTON_LEFT:
          input.keys[MOUSE_LEFT]=true;break;

        case SDL_BUTTON_MIDDLE:
          input.keys[MOUSE_MIDDLE]=true;break;

        default:
            break;
      }
      break;

    case SDL_MOUSEBUTTONUP:
      switch (event.button.button)  {

        case SDL_BUTTON_LEFT:
          input.keys[MOUSE_LEFT]=false;break;

        case SDL_BUTTON_MIDDLE:
          input.keys[MOUSE_MIDDLE]=false;break;

        default:
            break;
      }
      break;

    default:
        break;
  }
}

void Input::ReadMouseMotion () {

  if (event.motion.xrel > 0)
    input.keys[MOUSE_X_POS]=true;
  else if (event.motion.xrel < 0)
    input.keys[MOUSE_X_NEG]=true;
  else if (event.motion.yrel > 0)
    input.keys[MOUSE_Y_POS]=true;
  else if (event.motion.yrel < 0)
    input.keys[MOUSE_Y_NEG]=true;
}

//hash table time!!
void Input::ReadKeyboard () {

  switch (event.type) {

    case SDL_KEYUP:
      switch (event.key.keysym.sym) {
        case SDLK_a:
          input.keys[KEY_a]=false; break;
        case SDLK_d:
          input.keys[KEY_d]=false; break;
        case SDLK_w:
          input.keys[KEY_w]=false; break;
        case SDLK_s:
          input.keys[KEY_s]=false; break;
        case SDLK_MINUS:
          input.keys[KEY_MINUS]=false; break;
        case SDLK_EQUALS:
          input.keys[KEY_EQUALS]=false; break;
        case SDLK_t:
          input.keys[KEY_t]=false; break;
        case SDLK_r:
          input.keys[KEY_r]=false; break;
        case SDLK_KP_5:
          input.keys[KEY_KP_5]=false; break;
        case SDLK_KP_8:
          input.keys[KEY_KP_8]=false; break;
        case SDLK_KP_2:
          input.keys[KEY_KP_2]=false; break;
        case SDLK_KP_4:
          input.keys[KEY_KP_4]=false;break;
        case SDLK_KP_6:
          input.keys[KEY_KP_6]=false; break;
        case SDLK_5:
          input.keys[KEY_5]=false; break;
        case SDLK_SPACE:
          input.keys[KEY_SPACE] = false; break;
        default: break;
      }
      break;

    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
        case SDLK_ESCAPE:
          input.keys[KEY_ESC]=true;break;
        case SDLK_g:
          input.keys[KEY_g]=true;break;
        case SDLK_f:
          input.keys[KEY_f]=true;break;
        case SDLK_t:
          input.keys[KEY_t]=true;break;
        case SDLK_r:
          input.keys[KEY_r]=true;break;
        case SDLK_SPACE:
          input.keys[KEY_SPACE] = true; break;

        //Camera
        case SDLK_a:
          input.keys[KEY_a]=true; break;
        case SDLK_d:
          input.keys[KEY_d]=true; break;
        case SDLK_w:
          input.keys[KEY_w]=true; break;
        case SDLK_s:
          input.keys[KEY_s]=true; break;
        case SDLK_MINUS:
          input.keys[KEY_MINUS]=true; break;
        case SDLK_EQUALS:
          input.keys[KEY_EQUALS]=true; break;
        case SDLK_KP_5:
          input.keys[KEY_KP_5]=true; break;
        case SDLK_KP_8:
          input.keys[KEY_KP_8]=true; break;
        case SDLK_KP_2:
          input.keys[KEY_KP_2]=true; break;
        case SDLK_KP_4:
          input.keys[KEY_KP_4]=true;break;
        case SDLK_KP_6:
          input.keys[KEY_KP_6]=true; break;
        case SDLK_5:
          input.keys[KEY_5]=true; break;
        default: break;
      }
      break;

    default: break;
  }
}
