#include "Arduino.h"
#include "macros.h"
#include <Wifi.h>
#include <TFT_eSPI.h>
#include "variables.h"
#include <XPT2046_Touchscreen.h>
#include "setup.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

extern SPIClass touchscreenSPI;
extern XPT2046_Touchscreen touchscreen;

extern int wifiConnectionStatus;

extern String deviceData[];

void psetup() {
  Serial.begin(115200);

  /***********HTML**************/
  String ssid_read_1 = deviceData[0];
  String pass_read_1 = deviceData[1];
  int str_1_len = ssid_read_1.length() + 1;
  int str_2_len = pass_read_1.length() + 1;
  char ssid_eeprom_read[str_1_len];
  char pass_eeprom_read[str_2_len];
  ssid_read_1.toCharArray(ssid_eeprom_read, str_1_len);
  pass_read_1.toCharArray(pass_eeprom_read, str_2_len);

  const char* ssid_client = ssid_eeprom_read;
  const char* password_client = pass_eeprom_read;
  uint16_t i = 0;
  uint16_t n = 0;
  WiFi.begin(ssid_client, password_client);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    print_k('.');
    i++;
    n++;
    delay(100);
    if (n>50)
    {
        n = 0;
        print_kln();
    }
    if (i>100)
    {
      print_kln();
      msgln("WiFi Connection Failed");
      break;
    }
  }
  wifiConnectionStatus=1;  //polaczono
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
  /***********HTML**************/


  /***********LCD+TFT**************/
  // Start the SPI for the touchscreen and init the touchscreen
  touchscreenSPI.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
  touchscreen.begin(touchscreenSPI);
  // Set the Touchscreen rotation in landscape mode
  // Note: in some displays, the touchscreen might be upside down, so you might need to set the rotation to 3: touchscreen.setRotation(3);
  touchscreen.setRotation(3);
  // Start the tft display
  tft.init();
  // Set the TFT display rotation in landscape mode
  tft.setRotation(3);
  tft.invertDisplay(true);  //odwrocenie kolorow

  // Clear the screen before writing to it
  tft.fillScreen(TFT_WHITE);
  // tft.setTextColor(TFT_WHITE, TFT_BLACK, 1);
  tft.setTextColor(TFT_BLACK, TFT_BLACK);
  tft.setFreeFont(&FreeSans9pt7b);

  int centerX = SCREEN_WIDTH / 2;
  int centerY = SCREEN_HEIGHT / 2;
}