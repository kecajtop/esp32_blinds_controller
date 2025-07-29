#ifndef sd_card_h
#define sd_card_h

#define SDSCK 18//14
#define SDMOSI 23//15
#define SDMISO 19//2
#define SDCS 5//13

#include "Arduino.h"

void sd_init(int *_result);
int get_sd_init(void);
void printDirectory(File dir, int numTabs);

#endif