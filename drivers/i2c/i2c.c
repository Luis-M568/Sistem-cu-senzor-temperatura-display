#include "i2c.h"
#include <avr/io.h>

void I2C_Init(void) {
    /*
     * Calcul frecvență SCL:
     * SCL = F_CPU / (16 + 2 * TWBR * prescaler)
     *
     * Pentru F_CPU = 16 MHz și I2C = 100 kHz (Standard Mode):
     * TWBR = 72, prescaler = 1
     */
    TWSR = 0x00;        // Setăm prescalerul la 1
    TWBR = 72;          // Setăm baud rate-ul pentru 100 kHz
    TWCR = (1 << TWEN); // Activăm perifericul TWI (I2C)
}

void I2C_Start(void) {
    // Generăm condiția de START
    TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);

    // Așteptăm ca hardware-ul să seteze flag-ul TWINT, indicând finalizarea acțiunii
    while (!(TWCR & (1 << TWINT))) {
        ;
    }
}

void I2C_Stop(void) {
    // Generăm condiția de STOP
    TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
    
    // Notă: Pentru STOP nu trebuie să așteptăm setarea flag-ului TWINT în buclă
}

void I2C_Write(uint8_t data) {
    // Încărcăm datele în registrul de date
    TWDR = data;

    // Începem transmisia
    TWCR = (1 << TWINT) | (1 << TWEN);

    // Așteptăm ca hardware-ul să finalizeze transmisia pachetului
    while (!(TWCR & (1 << TWINT))) {
        ;
    }
}