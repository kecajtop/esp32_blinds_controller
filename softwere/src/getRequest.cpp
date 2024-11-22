#include "Arduino.h"
#include <HTTPClient.h>
#include <variables.h>
#include <getRequest.h>

extern String tempQuery1;
extern String tempValue1;
extern unsigned int serverTime;
extern int serverTimeH;
extern int serverTimeM;
extern int serverTimeS;

extern String deviceData[];

void getRequest() {
  HTTPClient http;
  String HOST_NAME = String(deviceData[2]);   // REPLACE WITH YOUR PC's IP ADDRESS
  String PHP_FILE_NAME = String(deviceData[3]);  //REPLACE WITH YOUR PHP FILE NAME
  String server = "";

  //server = HOST_NAME + PHP_FILE_NAME + tempQuery0 + tempValue0 + "&" + tempQuery1 + tempValue1;
  server = HOST_NAME + PHP_FILE_NAME + tempQuery1 + tempValue1;
  http.begin(server);
  int httpCode = http.GET();

  if (httpCode > 0) {
    if (httpCode == HTTP_CODE_OK) {
      String payload = http.getString();

      Serial.println(payload);
      byte firstSign =0;
      byte lastSign=0;
      String getText = "";
      // //tryb pracy
      // firstSign = payload.indexOf("?serverWorkingState=") + 20;
      // lastSign = firstSign + 1;
      // getText = "";
      // for (byte i = firstSign; i < lastSign; i++) {
      //   getText = getText + payload[i];
      // }
      // workingState = getText.toInt();

      /***************************************/
      // Serial.println(workingState);
      // tempValue1=workingState;
      /***************************************/


      //godzina
      firstSign = payload.indexOf("?serverTime=") + 12;
      lastSign = firstSign + 5;
      getText = "";
      for (byte i = firstSign; i < lastSign; i++) {
        getText = getText + payload[i];
      }
      serverTime = getText.toInt();
      serverTimeH = serverTime/3600;
      serverTimeM = (serverTime-(serverTimeH*3600))/60;
      serverTimeS = (serverTime-(serverTimeH*3600)-(serverTimeM*60));

    } else {
      Serial.printf("HTTP GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("HTTP GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
  http.end();
}