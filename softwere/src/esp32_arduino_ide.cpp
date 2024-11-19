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

