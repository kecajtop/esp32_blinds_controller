#include "Arduino.h"
#include "Wire.h"
#include <EEPROM.h>
#include <rom/rtc.h>
#include <SPI.h>
#include <SD.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "network.h"
#include "config.h"
#include "info.h"
#include "sd_card.h"
#include "macros.h"
#include "simple_tft.h"
#include "fw_upgrade.h"
#include <setup.h>
#include <XPT2046_Touchscreen.h>

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip

#define I2C_CLKRATE_400K            400000      // Speed of I2C bus 100KHz

#define SDApin 27
#define SCLpin 22

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

int x, y, z;

// Replace with your network credentials

const char* ssid; //= "";
const char* password; //= "";

const char* test_file_name = "test";

char list[512];

int stauts = 0;

config_t settings;

static uint32_t prev_ms = 0;

//I2C UART0 TX 1
//I2C UART0 RX 3

#define INT 19

#define USE_LV_LOG 1

char data_block[128]; 

pattern_struct_t pattern;

void setup() {
  // put your setup code here, to run once:
  
    Serial.begin(115200);
    infoln("Start");

    lv_init();
    
    prev_ms = millis();

    lv_log_register_print_cb(log_print);

    init_tft();

    touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    touchscreen.begin(touchscreenSPI);
    // Set the Touchscreen rotation in landscape mode
    // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 1: touchscreen.setRotation(1);
    touchscreen.setRotation(3);

    clear_display();
    
    set_selftest_tite("INFO");
    
    app_info();
    
    lib_info();

    clear_display();

    set_selftest_tite("SELFTEST"); 

    build_date();
    
    reset_info();

    stauts = sd_init();

    display_selftest_pass_fail("SD CARD",stauts);
    
    if (stauts)
    {
      stauts = sd_new_fw();
      if (stauts)
      {
        display_selftest_pass_fail("SD CARD FW.",stauts);
        sd_fw_upgrade();
      }
    }

    stauts = load_config();

    display_selftest_pass_fail("CONFIG TXT",stauts);

    if (settings.enable_wifi)
    {
      print_kln("[M] Enabling WiFi");
      if (initWiFi("Test"))
      {
        display_selftest_pass_fail("WIFI",ST_CONNECTED);
        
      }
      else
      {
        display_selftest_pass_fail("WIFI",ST_DISCONNECTED);
      }
    }
    else
    {
      display_selftest_pass_fail("WIFI",ST_DISABLED);
    }
    
    //Wire.begin(SDApin,  SCLpin);

    //Wire.setClock(I2C_CLKRATE_400K);

    //init_ams();

    psetup();
    
    nav();
    
    screen_1();
    
    i2c_scanner();

    delay(2000);

    infoln("config done");

    tft.setRotation(3);

    infoln("Ready!");
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
