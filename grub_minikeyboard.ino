#include "DigiKeyboard.h"

#define SW1 0
#define SW2 2

#define KEY_ARROW_UP 82
#define KEY_ARROW_DOWN 81

bool prev_sw1 = false;
bool prev_sw2 = false;
bool unable_flg = false;

void setup() {
  // don't need to set anything up to use DigiKeyboard
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
}

void loop() {
  bool sw1_pressed = digitalRead(SW1)==0;
  bool sw2_pressed = digitalRead(SW2)==0;

  if (sw1_pressed && sw2_pressed) {
    if (!unable_flg) {
      sendKey(KEY_ENTER);
    }
    prev_sw1 = sw1_pressed;
    prev_sw2 = sw2_pressed;
    unable_flg = true;
    return;
  }

  if (!unable_flg && prev_sw1 && !sw1_pressed) {
    sendKey(KEY_ARROW_UP);
    unable_flg = true;
  }
  if (!unable_flg && prev_sw2 && !sw2_pressed) {
    sendKey(KEY_ARROW_DOWN);
    unable_flg = true;
  }

  if (!sw1_pressed && !sw2_pressed) {
    unable_flg = false;
  }

  prev_sw1 = sw1_pressed;
  prev_sw2 = sw2_pressed;
}

void sendKey(int key_num) {
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.delay(5);
  DigiKeyboard.sendKeyStroke(key_num);
  DigiKeyboard.delay(5);
}
