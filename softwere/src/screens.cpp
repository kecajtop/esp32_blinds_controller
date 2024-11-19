void nav() {
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);

  byte x1 = 136 + (12 * screen_changer);
  tft.drawCircle(148, 15, 4, button_colour);
  tft.drawCircle(160, 15, 4, button_colour);
  tft.drawCircle(172, 15, 4, button_colour);
  tft.fillCircle(x1, 15, 4, button_colour);

  tft.fillRoundRect(button_2[0], button_2[1], button_2[2], button_2[3], button_2[4], button_colour);
  tft.drawCentreString(button_label_2, button_2[0] + (button_2[2] / 2), button_2[1] + (button_2[3] / 2) - fontHeigh / 2, 1);
}
void screen_1() {
  tft.drawCentreString("Obszary budynku:", 160, 60 - fontHeigh, 1);
  //wypisuje na ekranie kafelki z obszarami budynku
  for (byte i = 0; i < sizeOfArray_object_areas; i++) {  //tu mam ile mam miec przyciskow - obszarów
    String pomocnicza1 = object_areas[i][1];
    //********************************tutaj mam rozbicie nazwy na przycisku na dwa wiersze
    String text_row_1 = "";
    String text_row_2 = "";
    if (pomocnicza1.length() >= 10) {
      for (byte j = 0; j < 11; j++) {
        text_row_1 = text_row_1 + pomocnicza1[j];  //iteracja po ciagu znaków
      }
      for (byte j = 11; j < pomocnicza1.length(); j++) {
        text_row_2 = text_row_2 + pomocnicza1[j];  //iteracja po ciagu znaków
      }
    } else {
      text_row_1 = pomocnicza1;
      text_row_2 = "";
    }
    /**********************************************/
    //********************************tutaj mam ukladanie kafelkow w petli for
    tft.fillRoundRect(buttons_positions[i][0], buttons_positions[i][1], buttons_positions[i][2], buttons_positions[i][3], buttons_positions[i][4], button_colour);  //0
    tft.drawCentreString(text_row_1, buttons_positions[i][0] + (buttons_positions[i][2] / 2), buttons_positions[i][1] + (buttons_positions[i][3] / 2) - (fontHeigh + fontHeigh / 2), 1);
    tft.drawCentreString(text_row_2, buttons_positions[i][0] + (buttons_positions[i][2] / 2), buttons_positions[i][1] + (buttons_positions[i][3] / 2), 1);
  }
}
void screen_2() {
  tft.drawCentreString("Dane z serwera:", 160, 60 - fontHeigh, 1);
  getRequest();

  cb_y1 = 70;
  String stringToWrite="";
  if(wifiConnectionStatus)stringToWrite = "Status polaczenia: polaczono";
  else stringToWrite = "Status polaczenia: nie polaczono";
  tft.drawString(stringToWrite, 10, cb_y1 + 2);

  cb_y1 = cb_y1 + cb_row_space;
  stringToWrite = "Czas z serwera: "+ String(serverTimeH) + ':' + String(serverTimeM) + ':' + String(serverTimeS);
  tft.drawString(stringToWrite, 10, cb_y1 + 2);
}
void screen_3() {
  tft.drawCentreString("Ustawienia:", 160, 60 - fontHeigh, 1);
  cb_y1 = 70;
  String stringToWrite = "";

  stringToWrite = "Tryb pracy przycisku: " + deviceData[5];
  tft.drawString(stringToWrite, 10, cb_y1 + 2);

  cb_y1 = cb_y1 + cb_row_space;
  stringToWrite = "Czasy dzialania rolet ";
  tft.drawString(stringToWrite, 10, cb_y1 + 2);

  cb_y1 = cb_y1 + cb_row_space;
  stringToWrite = "Siec: " + deviceData[0];
  tft.drawString(stringToWrite, 10, cb_y1 + 2);

  cb_y1 = cb_y1 + cb_row_space;
  stringToWrite = "ID: " + deviceData[4];
  tft.drawString(stringToWrite, 10, cb_y1 + 2);

  cb_y1 = cb_y1 + cb_row_space;
  stringToWrite = "Ekspandery :"+String(countOfI2cDevices);
  tft.drawString(stringToWrite, 10, cb_y1 + 2);
}
void standard_back_button() {
  tft.fillRoundRect(button_1[0], button_1[1], button_1[2], button_1[3], button_1[4], button_colour);
  tft.drawCentreString(button_label_1, button_1[0] + (button_1[2] / 2), button_1[1] + (button_1[3] / 2) - fontHeigh / 2, 1);
}

void screen_level_2() {
  standard_back_button();
  int screen_changer_position = screen_changer - 10;
  //zabezpieczenie;
  if (screen_changer_position < 0) screen_changer_position = 0;
  else if (screen_changer_position > 5) screen_changer_position = 5;

  tft.drawCentreString(object_areas[screen_changer_position][1], 160, 60 - fontHeigh, 1);

  cb_y1 = 70;  //zeruje zmienna
  for (int i = 0; i < sizeOfArray_rollers; i++) {
    //wyswietlam wnetrza kafelkow
    if (rollers[i][2] == object_areas[screen_changer_position][0]) {
      //zaznacznie check boxow
      tft.drawRect(10, cb_y1, frame1, frame1, button_colour);  //check box
      if (rollers[i][5] == "checked") tft.fillRect(10, cb_y1, frame1, frame1, button_insert_colour);
      tft.drawString(rollers[i][1], 35, cb_y1 + 2);
      //zaznaczania loading bar
      tft.drawRect(150, cb_y1, 50, frame1, button_colour);                                   //loading bar
      if (rollers[i][6] == "0") tft.fillRect(150, cb_y1, 50, frame1, button_insert_colour);  //1 to otwarta wiec pusty
      rollers[i][8] = cb_y1;                                                                 //zapisuje pozycje bara do otwarcia na ekranie
      cb_y1 = cb_y1 + cb_row_space;
    }
  }

  //przycisk góra/dół

  tft.fillRoundRect(button_up[0], button_up[1], button_up[2], button_up[3], button_up[4], button_colour);
  tft.drawCentreString(button_label_3, button_up[0] + (button_up[2] / 2), button_up[1] + (button_up[3] / 2) - fontHeigh / 2, 1);

  tft.fillRoundRect(button_down[0], button_down[1], button_down[2], button_down[3], button_down[4], button_colour);
  tft.drawCentreString(button_label_4, button_down[0] + (button_down[2] / 2), button_down[1] + (button_down[3] / 2) - fontHeigh / 2, 1);
}

//fonts
// tft.setFreeFont(&FreeMono9pt7b);
// tft.setCursor(1, 60, 1);
// tft.println("Wybierz obszar budynku: test tekstu");
// tft.setFreeFont(&FreeMonoOblique9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&FreeSans9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&FreeSerif9pt7b);
// tft.println("Wybierz obszar\n budynku:");
// tft.setFreeFont(&TomThumb);
// tft.println("Wybierz obszar\n budynku:");
