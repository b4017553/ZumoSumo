#include "ZumoLCD.h"
// sets up custom Zumo Display class
ZumoLCD::ZumoLCD(uint8_t pins[]): LiquidCrystal(pins[0], pins[1], pins[2], pins[3], pins[4], pins[5]){};