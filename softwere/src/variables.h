#include <Arduino.h>

int x, y, z;
int lock_key_1 = 1;      //zmienna dotyku przyciskow
int screen_changer = 1;  //zmienna kolejnych ekranów w menu
int screen_sum = 3;      //zmienna kolejnych ekranów w menu - suma max

byte fontHeigh = 10;  //dodałem wiecej aby zrobic padding pom tekstem
uint32_t button_colour = '0x7BEF';
uint32_t button_insert_colour = '0x867D';
uint32_t empty_colour = 'TFT_WHITE';


byte cn_object_areas = 2;//columns
String object_areas[6][2]{  //area/name of area/
  { "AREA_1", "PARTER POM. MIESZKALNE"},
  { "AREA_2", "PARTER POM. TECHNICZNE"},
  { "AREA_3", "PIETRO POM. MIESZKALNE"},
  { "AREA_4", "PIETRO POM. TECHNICZNE"},
  { "AREA_5", "TEST 1"},
  { "AREA_6", "TEST 2"}
};
int sizeOfArray_object_areas = (sizeof(object_areas) / sizeof(object_areas[0][0])) / cn_object_areas;  //liczba wierszy

//tablica obiektów typu roleta
byte cn_rollers = 9;  //columns
String rollers[11][9]{  //id/ name/ area/ start time ms/ stop time ms/ if checkbox checked/ open/close stage(1 open 0 close)/ poziom otwarcia 0 otwarty,100, zamkniety/pozycja na ekranie
  { "1", "Roleta 1", "AREA_1", "0", "9000", "0" , "1", "0", "0"},
  { "2", "Roleta 2", "AREA_2", "0", "16000", "0" , "0", "100", "0"},
  { "3", "Roleta 3", "AREA_1", "0", "10000", "0" , "0", "100", "0"},
  { "4", "Roleta 4", "AREA_1", "0", "6000", "0" , "0", "100", "0"},
  { "5", "Roleta 5", "AREA_1", "0", "5000", "0" , "1", "0", "0"},
  { "6", "Roleta 6", "AREA_1", "0", "2000", "0" , "0", "100", "0"},
  { "7", "Roleta 7", "AREA_3", "0", "12000", "0" , "0", "100", "0"},
  { "8", "Roleta 8", "AREA_3", "0", "12000", "0" , "0", "100", "0"},
  { "9", "Roleta 9", "AREA_4", "0", "12000", "0" , "1", "0", "0"},
  { "10", "Roleta 10", "AREA_4", "0", "12000", "0" , "0", "100", "0"},
  { "11", "Roleta 11", "AREA_5", "0", "12000", "0" , "1", "0", "0"}
};
int sizeOfArray_rollers = (sizeof(rollers) / sizeof(rollers[0][0])) / cn_rollers;  //liczba wierszy

int wifiConnectionStatus =0;
String deviceData[]{
  "UPC7AA1BAF",  //ssid
  "Ra5xvvsxcpdj", //ssid_pass
  "https://pivvwsrxfv.cfolks.pl",//host name
  "/connectEspDbIdDevice.php",//php file name
  "did000001", //device_id
  "button",  //bell button or just button
};

unsigned long start_millis_time=0;  //start odliczania czasu do dzaialnia przekaznika

int countOfI2cDevices = 0;
