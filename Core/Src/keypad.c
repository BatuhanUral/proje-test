/*
 * char pressed_key = '\0';
 * pressed_key = Read_Keypad();
 * if (pressed_key != '\0') {}
 */

/*MAINDE KULLANIM

	KLAVYE MOD 1       					KLAVYE MOD 2
ÇAĞIRILMA '' ŞEKLİNDE		HARFLER '' , SAYILAR NORMAL 12, 22
	 __     __ 		  				  __       __
	|1 2 3 A  |       				 |12 22 32 X |
	|4 5 6 B  |	      				 |42 52 62 Y |
	|7 8 9 C  |        				 |72 82 92 Z |
	|* 0 # D  |        				 |S 02 H D   |
	|__     __|        				 |__       __|

 */




#include "keypad.h"
#include "stm32f4xx_hal.h"
#include "macro.h"

static uint8_t mod = 1;
static uint32_t lastModDebounceTime = 0;
static uint8_t modButtonPressed = 0;
#define DEBOUNCE_DELAY_MS 100
#define MOD_DEBOUNCE_DELAY_MS 200

char Read_Keypad(void) {

	// Tüm satırları LOW yap
	GPIO_WRITE(R1, OFF);
	GPIO_WRITE(R2, OFF);
	GPIO_WRITE(R3, OFF);
	GPIO_WRITE(R4, OFF);

	char key = '\0';
	uint32_t currentTime = HAL_GetTick();
	uint8_t keyPressedCount = 0;

	// R1 SATIRI AKTİF
	GPIO_WRITE(R1, ON);
	if (READ_INPUT(C1) == ON) key = (mod == 1) ? '1' : 12, keyPressedCount++;
	if (READ_INPUT(C2) == ON) key = (mod == 1) ? '2' : 22, keyPressedCount++;
	if (READ_INPUT(C3) == ON) key = (mod == 1) ? '3' : 32, keyPressedCount++;
	if (READ_INPUT(C4) == ON) key = (mod == 1) ? 'A' : 'X', keyPressedCount++;
	GPIO_WRITE(R1, OFF);

	// R2 SATIRI AKTİF
	GPIO_WRITE(R2, ON);
	if (READ_INPUT(C1) == ON) key = (mod == 1) ? '4' : 42, keyPressedCount++;
	if (READ_INPUT(C2) == ON) key = (mod == 1) ? '5' : 52, keyPressedCount++;
	if (READ_INPUT(C3) == ON) key = (mod == 1) ? '6' : 62, keyPressedCount++;
	if (READ_INPUT(C4) == ON) key = (mod == 1) ? 'B' : 'Y', keyPressedCount++;
	GPIO_WRITE(R2, OFF);

	// R3 SATIRI AKTİF
	GPIO_WRITE(R3, ON);
	if (READ_INPUT(C1) == ON) key = (mod == 1) ? '7' : 72, keyPressedCount++;
	if (READ_INPUT(C2) == ON) key = (mod == 1) ? '8' : 82, keyPressedCount++;
	if (READ_INPUT(C3) == ON) key = (mod == 1) ? '9' : 92, keyPressedCount++;
	if (READ_INPUT(C4) == ON) key = (mod == 1) ? 'C' : 'Z', keyPressedCount++;
	GPIO_WRITE(R3, OFF);

	// R4 SATIRI AKTİF
	GPIO_WRITE(R4, ON);
	if (READ_INPUT(C1) == ON) key = (mod == 1) ? '*' : 'S', keyPressedCount++;
	if (READ_INPUT(C2) == ON) key = (mod == 1) ? '0' : 20, keyPressedCount++;
	if (READ_INPUT(C3) == ON) key = (mod == 1) ? '#' : 'T', keyPressedCount++;

	if (READ_INPUT(C4) == ON) {
		if (!modButtonPressed && (currentTime - lastModDebounceTime) >= MOD_DEBOUNCE_DELAY_MS) {
			mod = (mod % 2) + 1;
			modButtonPressed = 1;
			lastModDebounceTime = currentTime;
		}
		GPIO_WRITE(R4, OFF);
		return '\0';
	} else {
		modButtonPressed = 0;
	}
	GPIO_WRITE(R4, OFF);


	// Eğer birden fazla tuşa basılmışsa '\0' döndürme condition'ı
	if (keyPressedCount > 1) {
		return '\0';
	}

	return key;
}
