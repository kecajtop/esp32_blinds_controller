#include "Arduino.h"
#include "config.h"
#include "macros.h"
#include <minIni.h>
#include <string>
#include <SD.h>

extern config_t settings;
extern const char* ssid;
extern const char* password;
extern const char* test_file_name;

int sd_config_status = 0;

static void assert_my(bool cond)
{
  if(!cond){
    Serial.println("Error");
    while(true){;}
  }else{
    Serial.println("OK");
  }
}

static void assert_my(String s1, String s2)
{
  Serial.print("<");
  Serial.print(s1.c_str());
  Serial.print("> <");
  Serial.print(s2.c_str());
  Serial.print(">  ");
  
  assert_my(s1 == s2);
}

static void assert_my(int d1, int d2)
{
  Serial.print("(");
  Serial.print(d1);
  Serial.print(") (");
  Serial.print(d2);
  Serial.print(")  ");
  
  assert_my(d1 == d2);
}

void init_ini(int *_result)
{
  msgln("Loading Settings from SD CARD ... ");
  minIni ini("/settings.ini");

  printf_k("[I] WIFI\r\n");
  settings.wifi.ssid = ini.gets( "WIFI", "SSID" , STR(WIFI_SSID) );
  printf_k("\t SSID = %s\r\n",settings.wifi.ssid.c_str());
  settings.wifi.password = ini.gets( "WIFI", "PASS" , STR(WIFI_PASSWORD) );
  printf_k("\t PASS = %s\r\n",settings.wifi.password.c_str());
  settings.wifi.enable = (ini.gets( "WIFI", "ENABLE" , STR(WIFI_ENABLE) )).toInt();
  printf_k("\t ENABLE_WIFI = %d\r\n",settings.wifi.enable);
  settings.ota.enable= (ini.gets( "OTA", "ENABLE" , STR(OTA_ENABLE) )).toInt();
  printf_k("\t OTA = %d\r\n",settings.ota.enable);

  ssid = settings.wifi.ssid.c_str();
  password = settings.wifi.password.c_str();
  *_result = 1;
  
  msgln("Done");
}

/*void load_config(int *_result)
{

	char value_string[VALUE_MAX_LENGTH];
	msgln("Loading config from SD CARD ... ");

  if (SD_findKey(F("auto_load"), value_string))
	{
		settings.ota    = SD_findInt(F("ota"));
		Serial.print(F("\t ota = "));
    print_kln(settings.ota);
	}
	else
	{
		settings.ota = 0;
		Serial.print(F("\t ota = not found, default = "));
		print_kln(settings.ota);
	}

	if (SD_findKey(F("enable_wifi"), value_string))
	{
		settings.enable_wifi    = SD_findInt(F("enable_wifi"));
		Serial.print(F("\t enable_wifi = "));
    print_kln(settings.enable_wifi);
	}
	else
	{
    #ifdef WIFI_ENABLE
      settings.enable_wifi = atoi(STR(WIFI_ENABLE));
    #endif
    #ifndef WIFI_ENABLE
		  settings.enable_wifi = 0;
    #endif 
		Serial.print(F("\t enable_wifi = not found, default = "));
		print_kln(settings.enable_wifi);
	}
	
  if (SD_findKey(F("ssid_wifi"), value_string))
	{
    settings.ssid_wifi    = SD_findString(F("ssid_wifi"));
		Serial.print(F("\t ssid_wifi = "));
    print_kln(settings.ssid_wifi);
    ssid = settings.ssid_wifi.c_str();
	}
	else
	{
    #ifdef WIFI_SSID
      settings.ssid_wifi = STR(WIFI_SSID);
    #endif
    #ifndef WIFI_SSID
		  settings.ssid_wifi = "Test";
    #endif  
		Serial.print(F("\t ssid_wifi = not found, default = "));
		print_kln(settings.ssid_wifi);
    ssid = settings.ssid_wifi.c_str();
	}

  if (SD_findKey(F("password_wifi"), value_string))
	{
    settings.password_wifi    = SD_findString(F("password_wifi"));
		print_k(F("\t password_wifi = "));
    print_kln(settings.password_wifi);
    password = settings.password_wifi.c_str();
	}
	else
	{
    #ifdef WIFI_PASSWORD
      settings.password_wifi = STR(WIFI_PASSWORD);
    #endif
    #ifndef WIFI_PASSWORD
		  settings.password_wifi = "Test";
    #endif
		print_k(F("\t password_wifi = not found, default = "));
		print_kln(settings.password_wifi);
    password = settings.password_wifi.c_str();

	}
	msgln("Done");
	*_result = sd_config_status;
}
*/

bool SD_available(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return value_length > 0;
}

int SD_findInt(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2Int(value_string, value_length);
}

float SD_findFloat(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2Float(value_string, value_length);
}

String SD_findString(const __FlashStringHelper * key) {
  char value_string[VALUE_MAX_LENGTH];
  int value_length = SD_findKey(key, value_string);
  return HELPER_ascii2String(value_string, value_length);
}

int SD_findKey(const __FlashStringHelper * key, char * value) {
  File configFile = SD.open(CONFIG_FILE_NAME);

  if (!configFile) {  
    err(F("SD Card: Issue encountered while attempting to open the file "));
    print_kln(CONFIG_FILE_NAME);
    sd_config_status = 0xFF;
    return 0;
  }
  else
  {
    sd_config_status = 1;
  }

  char key_string[KEY_MAX_LENGTH];
  char SD_buffer[KEY_MAX_LENGTH + VALUE_MAX_LENGTH + 1]; // 1 is = character
  int key_length = 0;
  int value_length = 0;

  // Flash string to string
  PGM_P keyPoiter;
  keyPoiter = reinterpret_cast<PGM_P>(key);
  byte ch;
  do {
    ch = pgm_read_byte(keyPoiter++);
    if (ch != 0)
      key_string[key_length++] = ch;
  } while (ch != 0);

  // check line by line
  while (configFile.available()) {
    int buffer_length = configFile.readBytesUntil('\n', SD_buffer, 100);
    if (SD_buffer[buffer_length - 1] == '\r')
      buffer_length--; // trim the \r

    if (buffer_length > (key_length + 1)) { // 1 is = character
      if (memcmp(SD_buffer, key_string, key_length) == 0) { // equal
        if (SD_buffer[key_length] == '=') {
          value_length = buffer_length - key_length - 1;
          memcpy(value, SD_buffer + key_length + 1, value_length);
          break;
        }
      }
    }
  }

  configFile.close();  // close the file
  return value_length;
}

int HELPER_ascii2Int(char *ascii, int length) {
  int sign = 1;
  int number = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c >= '0' && c <= '9')
        number = number * 10 + (c - '0');
    }
  }

  return number * sign;
}

float HELPER_ascii2Float(char *ascii, int length) {
  int sign = 1;
  int decimalPlace = 0;
  float number  = 0;
  float decimal = 0;

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    if (i == 0 && c == '-')
      sign = -1;
    else {
      if (c == '.')
        decimalPlace = 1;
      else if (c >= '0' && c <= '9') {
        if (!decimalPlace)
          number = number * 10 + (c - '0');
        else {
          decimal += ((float)(c - '0') / pow(10.0, decimalPlace));
          decimalPlace++;
        }
      }
    }
  }

  return (number + decimal) * sign;
}

String HELPER_ascii2String(char *ascii, int length) {
  String str;
  str.reserve(length);
  str = "";

  for (int i = 0; i < length; i++) {
    char c = *(ascii + i);
    str += String(c);
  }

  return str;
}