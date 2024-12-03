#include "Arduino.h"
#include "config.h"
#include "macros.h"
#include <minIni.h>
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

void init_ini()
{
  msgln("here1");
  minIni ini("test.ini");
  minIni ini2("plain.ini");
  msgln("here2");
  String s;
  msgln("here2.5");
  /* string reading */
  s = ini.gets( "first", "string" , "aap" );
  msgln("here3");
  assert_my(s, "noot");
  msgln("here4");
  s = ini.gets( "second", "string" , "aap" );
  assert_my(s, "mies");
  s = ini.gets( "first", "dummy" , "aap" );
  assert_my(s, "aap");
  /* ----- */
  s = ini2.gets( "", "string" , "aap" );
  assert_my(s, "noot");
  /* ----- */
  Serial.println("1. String reading tests passed");

  /* value reading */
  long n;
  n = ini.getl("first", "val", -1 );
  assert_my(n, 1);
  n = ini.getl("second", "val", -1);
  assert_my(n, 2);
  n = ini.getl("first", "dummy", -1);
  assert_my(n, -1);
  /* ----- */
  n = ini2.getl("", "val", -1);
  assert_my(n, 1);
  /* ----- */
  Serial.println("2. Value reading tests passed");


  /* string writing */
  bool b;
  b = ini.put("first", "alt", "flagged as \"correct\"");
  assert_my(b);
  s = ini.gets("first", "alt", "aap");
  assert_my(s, "flagged as \"correct\"");

  b = ini.put("second", "alt", "correct");
  assert_my(b);
  s = ini.gets("second", "alt", "aap");
  assert_my(s, "correct");

  b = ini.put("third", "alt", "correct");
  assert_my(b);
  s = ini.gets("third", "alt", "aap" );
  assert_my(s, "correct");
  /* ----- */
  b = ini2.put("", "alt", "correct");
  assert(b);
  s = ini2.gets("", "alt", "aap" );
  assert_my(s, "correct");
  /* ----- */
  Serial.println("3. String writing tests passed");

  /* section/key enumeration */
  Serial.println("4. section/key enumeration; file contents follows");
  String section;
  for (int is = 0; section = ini.getsection(is), section.length() > 0; is++) {
    Serial.print("    [");
    Serial.print(section.c_str());
    Serial.println("]");
    for (int ik = 0; s = ini.getkey(section, ik), s.length() > 0; ik++) {
      Serial.print("\t");
      Serial.println(s.c_str());
    }
  }

  /* string deletion */
  b = ini.del("first", "alt");
  assert_my(b);
  b = ini.del("second", "alt");
  assert_my(b);
  b = ini.del("third");
  assert_my(b);
  /* ----- */
  b = ini2.del("", "alt");
  assert_my(b);
  /* ----- */
  Serial.println("5. string deletion passed ");
  
  while(true){;}
}

void load_config(int *_result)
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