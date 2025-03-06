#ifndef KEYPAD_H
#define KEYPAD_H

#include "stm32f4xx_hal.h"


// TUŞ MOD CHAR--> STR DEĞİŞİMİ
#define E ((char)12)
#define F ((char)22)
#define G ((char)32)
#define I ((char)42)
#define J ((char)52)
#define K ((char)62)
#define M ((char)72)
#define N ((char)82)
#define O ((char)92)
#define T ((char)02)


// Fonksiyon Prototipi
char Read_Keypad(void);

#endif  // KEYPAD_H

