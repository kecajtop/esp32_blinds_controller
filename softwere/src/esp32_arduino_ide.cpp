#include <Wire.h>
#include <screen_elements.h>
#include <variables.h>
#include <SPI.h>
/*TFT_eSPI file to change drom folder*/
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <XPT2046_Touchscreen.h>
SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);


/***********HTML**************/
#include <WiFi.h>
#include <HTTPClient.h>
#include <setup.h>

// String tempQuery1 = "?deviceWorkingState=";
// String tempValue1 = "3";
String tempQuery1 = "";
String tempValue1 = "";
unsigned int serverTime;
int serverTimeH;
int serverTimeM;
int serverTimeS;

void setup() {
  psetup();
  nav();
  screen_1();
  i2c_scanner();
  //led_test();
}
void loop() {
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
void led_test() {
  pinMode(16, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(17, OUTPUT);
  delay(1000);
  digitalWrite(16, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(17, HIGH);

  delay(100);
  digitalWrite(16, LOW);
  delay(100);
  digitalWrite(16, HIGH);
  delay(100);
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100);
  digitalWrite(17, LOW);
  delay(100);
  digitalWrite(17, HIGH);

  Serial.println(analogRead(34));

  tft.fillRect(150, 150, 100, 100, 0x0000);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x000F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x03E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x03EF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7800);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x780F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7BE0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xD69A);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x7BEF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x001F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x07E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x07FF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xF800);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xF81F);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFFE0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFFFF);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFDA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xB7E0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFE19);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x9A60);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFEA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFE19);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x9A60);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xFEA0);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0xC618);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x867D);
  delay(500);
  tft.fillRect(150, 150, 100, 100, 0x915C);
  delay(500);
}