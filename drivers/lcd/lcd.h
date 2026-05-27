#ifndef LCD_H
#define LCD_H

#include <stdint.h>

/**
 * @brief Inițializează comunicarea cu LCD-ul via I2C și îl configurează în modul 4-bit.
 */
void LCD_Init(void);

/**
 * @brief Șterge întregul conținut de pe ecran și mută cursorul la început.
 */
void LCD_Clear(void);

/**
 * @brief Mută cursorul la o poziție specificată.
 * @param row Rândul (0 pentru prima linie, 1 pentru a doua).
 * @param col Coloana (0-15 pentru un ecran 16x2).
 */
void LCD_SetCursor(uint8_t row, uint8_t col);

/**
 * @brief Afișează un șir de caractere (string) la poziția curentă a cursorului.
 * @param text Șirul de caractere (null-terminated).
 */
void LCD_Print(const char *text);

/**
 * @brief Afișează un număr întreg pozitiv pe ecran.
 * @param number Numărul ce trebuie afișat (0 - 65535).
 */
void LCD_PrintNumber(uint16_t number);

#endif // LCD_H