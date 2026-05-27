#ifndef I2C_H
#define I2C_H

#include <stdint.h>

/**
 * @brief Inițializează magistrala I2C (Master) la 100kHz.
 */
void I2C_Init(void);

/**
 * @brief Trimite condiția de START pe magistrală.
 */
void I2C_Start(void);

/**
 * @brief Trimite condiția de STOP pe magistrală.
 */
void I2C_Stop(void);

/**
 * @brief Trimite un octet (8 biți) de date pe magistrală.
 * @param data Valoarea ce urmează a fi transmisă.
 */
void I2C_Write(uint8_t data);

#endif // I2C_H