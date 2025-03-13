#ifndef config_h
#define config_h

#include "Arduino.h"
#include "ESP32OTAPull.h"

#if __has_include("update_settings.h") // optionally override with values in settings.h
#include "update_settings.h"
#else
#define JSON_URL   "https://raw.githubusercontent.com/kecajtop/esp32_blinds_controller/refs/heads/main/json/firmware_pcb_rev01.json" // this is where you'll post your JSON filter file
#define _FW_VERSION_ESP32    "0.0.3" // The current version of this program
#define _SD_FW_NAME_ESP32 "/firmwareESP32.bin"
#define _SD_FW_NAME_ESP32_BAK "/firmwareESP32.bak"
#define _PCB_VERSION "REV1"
#define CONFIG_FILE_NAME "/config.txt"
#endif

#define KEY_MAX_LENGTH    30 // change it if key is longer
#define VALUE_MAX_LENGTH  30 // change it if value is longer

struct wifi_t
{
  uint8_t enable;
  String ssid;
  String password;
};

struct ota_t
{
  uint8_t enable;
};

struct cover_t
{
  String name;
  uint32_t map_number;
  String name_up;
  String name_down;
  uint32_t close_time;
  uint32_t open_time;
  uint8_t invert;
};

struct config_t
{
  wifi_t wifi;
  ota_t ota;
  String name;
  cover_t cover[16];
};

void init_ini(int *_result);

String HELPER_ascii2String(char *ascii, int length);
float HELPER_ascii2Float(char *ascii, int length);
int HELPER_ascii2Int(char *ascii, int length);
int SD_findKey(const __FlashStringHelper * key, char * value);
String SD_findString(const __FlashStringHelper * key);
float SD_findFloat(const __FlashStringHelper * key);
int SD_findInt(const __FlashStringHelper * key);
bool SD_available(const __FlashStringHelper * key);
void load_config(int *_result);

#endif