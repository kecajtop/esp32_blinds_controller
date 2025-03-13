#include "Arduino.h"
#include "screen_elements.h"

//nav
// uint32_t button_name_1 = 'button_1';
String button_label_1 = "WSTECZ";
int button_1[]{
  1,    //x  0
  1,    //y  1
  104,  //wide  2
  40,   //height  3
  15,   // round  4
};

// uint32_t button_name_2 = 'button_2';
String button_label_2 = "NASTEPNY";
int button_2[]{
  215,  //x
  1,    //y
  104,  //wide
  40,   //height
  15,   // round
};
String button_label_3 = "GORA";
int button_up[]{
  244,  //x
  71,   //y
  70,   //wide
  60,   //height
  5,    // round
};
String button_label_4 = "DOL";
int button_down[]{
  244,  //x
  133,  //y
  70,   //wide
  60,   //height
  5,    // round
};


//Panele:
int buttons_positions[6][5]{ //max 6 elements
                             /*{x0, y0, wide, heigh, round}*/
                             { 1, 71, 150, 50, 15 },
                             { 169, 71, 150, 50, 15 },
                             { 1, 131, 150, 50, 15 },
                             { 169, 131, 150, 50, 15 },
                             { 1, 191, 150, 50, 15 },
                             { 169, 191, 150, 50, 15 }
};
String buttons_names[6]{
  { "button_3" },
  { "button_4" },
  { "button_5" },
  { "button_6" },
  { "button_7" },
  { "button_8" }
};

//check-box
uint8_t cb_y1 = 70;                 //pozycja checkboxa na lcd w osi y
uint8_t frame1 = 20;                //rozmiar check boxa
uint8_t cb_row_space = frame1 + 5;  //odleglosc pomiedzy wierszami
