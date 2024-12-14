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
//#include "setup.h"
//#include "screen_elements.h"
//#include "screens.h"
#include "i2c_expander.h"
//#include "variables.h"
//#include "touch_element.h"
#include "user_app.h"
#include "boot.h"
#include <XPT2046_Touchscreen.h>

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

SPIClass touchscreenSPI = SPIClass(VSPI);
XPT2046_Touchscreen touchscreen(XPT2046_CS, XPT2046_IRQ);

motor my_motor[8];

const char* ssid; //= "";
const char* password; //= "";

const char* test_file_name = "test";

char list[512];

int stauts = 0;

config_t settings;

char data_block[128]; 

pattern_struct_t pattern;

void setup() {
  // put your setup code here, to run once:
  
    Serial.begin(115200);
    print_k("");
    build_date();
    reset_info();

    Init_boot_command (BOOT_MODE);
    
    //init_tft();
    Add_boot_command ("TFT", init_tft);
    Add_boot_command ("TOUCHSCREEN", init_touchscreen);
    Add_boot_command ("APP_INFO", app_info);
    Add_boot_command ("SD CARD", sd_init);
    Add_boot_command ("LOAD CONFIG", load_config);
    Add_boot_command ("SD CARD FW.", sd_new_fw);
    Add_boot_command ("WIFI", wifi_config);
    Add_boot_command ("JSON FW,", ota_fw_upgrade);
    Add_boot_command ("I2C SETUP", i2c_init);
    set_boot_tite("ESP32 BOOT STATUS");

    Exec_boot_command();

    init_ini();
    delay(5000);
    display_info();


    
    infoln("User Setup");
    tft.setRotation(3);
    user_setup();
    for (int i=0;i<8;i++)
    {
      my_motor[i].begin(i);
    }

    infoln("Ready!");
}

void loop() 
{
  user_loop();
  my_motor[0].motor_close(1);
}

