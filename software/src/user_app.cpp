#include "Arduino.h"
#include "screens.h"
#include "variables.h"
#include "setup.h"
#include "i2c_expander.h"
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>
#include "touch_element.h" 
#include "user_app.h"

extern int x, y, z;
extern int lock_key_1;      //zmienna dotyku przyciskow
extern int screen_changer;  //zmienna kolejnych ekranów w menu
extern int screen_sum;      //zmienna kolejnych ekranów w menu - suma max
extern int button_1[];
extern int sizeOfArray_rollers;
extern int sizeOfArray_object_areas;

extern byte cn_rollers;  //columns
extern String rollers[11][9];

extern TFT_eSPI tft;  // Invoke library, pins defined in User_Setup.h

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

extern SPIClass touchscreenSPI;
extern XPT2046_Touchscreen touchscreen;

void user_setup(void)
{
    psetup();
    nav();
    screen_1();
}

void user_loop(void)
{
x = 0;
  y = 0;
  z = 0;
  while (touchscreen.tirqTouched() && touchscreen.touched()) {
    if (lock_key_1) {  //f wywoluje sie tylko raz. Nie ma migotania
      lock_key_1 = 0;
      String touch_function_result = touch_function();
      if (touch_function_result == "button_1") {
        screen_changer--;
        if (screen_changer == 0) screen_changer = screen_sum;
        else if (screen_changer > screen_sum) screen_changer = 1;
        //tutaj ide w dol z ekranami

      } else if (touch_function_result == "button_2") {
        screen_changer++;
        if (screen_changer > screen_sum) screen_changer = 1;
        else if (screen_changer > screen_sum) screen_changer = 1;
        //tutaj ide w gore z ekranami

      } else if (touch_function_result == "button_3") {
        screen_changer = 10;
        //funkcje przycisku 3
      } else if (touch_function_result == "button_4") {
        screen_changer = 11;
        //funkcje przycisku 4
      } else if (touch_function_result == "button_5") {
        screen_changer = 12;
        //funkcje przycisku 5
      } else if (touch_function_result == "button_6") {
        screen_changer = 13;
        //funkcje przycisku 6
      } else if (touch_function_result == "button_7") {
        screen_changer = 14;
        //funkcje przycisku 6
      } else if (touch_function_result == "button_8") {
        screen_changer = 15;
        //funkcje przycisku 6
      }
    }
    delay(200);
  }
  if (lock_key_1 == 0) {
    tft.fillScreen(TFT_WHITE);  //moment czyszczenia ekranu
    switch (screen_changer) {
      case 1:
        nav();
        screen_1();
        break;
      case 2:
        nav();
        screen_2();
        break;
      case 3:
        nav();
        screen_3();
        break;
      case 10:
        screen_level_2();
        break;
      case 11:
        screen_level_2();
        break;
      case 12:
        screen_level_2();
        break;
      case 13:
        screen_level_2();
        break;
      case 14:
        screen_level_2();
        break;
      case 15:
        screen_level_2();
        break;
    }
    lock_key_1 = 1;
  }
}