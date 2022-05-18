#ifndef KEYMAP_H
#define KEYMAP_H


#define WIN_ESC          0x0000

//max number of keys: 65536

#define KEY_LEFT         0x0001
#define KEY_RIGHT        0x0002
#define KEY_UP           0x0003
#define KEY_DOWN         0x0004
#define KEY_MINUS        0x0005
#define KEY_EQUALS       0x0006
#define KEY_SPACE        0x0007
#define KEY_ESC          0x0008

#define KEY_g            0x0100
#define KEY_f            0x0101
#define KEY_t            0x0102
#define KEY_r            0x0103
#define KEY_w            0x0104
#define KEY_s            0x0105
#define KEY_a            0x0106
#define KEY_d            0x0107

#define KEY_KP_5         0x0200
#define KEY_KP_2         0x0201
#define KEY_KP_8         0x0202
#define KEY_KP_4         0x0203
#define KEY_KP_6         0x0204

#define KEY_5            0x0205

#define MOUSE_MIDDLE     0x0300
#define MOUSE_LEFT       0x0301
#define MOUSE_RIGHT      0x0302
#define MOUSE_X_POS      0x0303
#define MOUSE_X_NEG      0x0304
#define MOUSE_Y_POS      0x0305
#define MOUSE_Y_NEG      0x0306
#define MOUSE_WHEEL_UP   0x0307
#define MOUSE_WHEEL_DOWN 0x0308


//for kMaxInputKeys = 2048, max number is 0x007FF


#endif // KEYMAP_H
