#include "lcd.h"
#include "drivers/i2c/i2c.h" 
#include "utils/delay.h" // Includem funcția ta personalizată de delay

#define LCD_ADDR 0x27

#define LCD_BACKLIGHT 0x08
#define LCD_ENABLE    0x04
#define LCD_RS        0x01

static void LCD_WriteI2C(uint8_t data) {
    I2C_Start();
    I2C_Write(LCD_ADDR << 1);
    I2C_Write(data | LCD_BACKLIGHT);
    I2C_Stop();
}

static void LCD_PulseEnable(uint8_t data) {
    LCD_WriteI2C(data | LCD_ENABLE);
    
    // Înlocuim _delay_us(1) cu Delay(1) - minimul suportat de funcția ta
    Delay(1); 
    
    LCD_WriteI2C(data & ~LCD_ENABLE);
    
    // Înlocuim _delay_us(50) cu Delay(1)
    Delay(1); 
}

static void LCD_Send4Bits(uint8_t data) {
    LCD_WriteI2C(data);
    LCD_PulseEnable(data);
}

static void LCD_Send(uint8_t value, uint8_t mode) {
    uint8_t high_nibble = value & 0xF0;
    uint8_t low_nibble  = (value << 4) & 0xF0;

    LCD_Send4Bits(high_nibble | mode);
    LCD_Send4Bits(low_nibble | mode);
}

static void LCD_Command(uint8_t command) {
    LCD_Send(command, 0);
}

static void LCD_Data(uint8_t data) {
    LCD_Send(data, LCD_RS);
}

void LCD_Init(void) {
    I2C_Init();

    Delay(50); // Folosim funcția ta

    LCD_Send4Bits(0x30);
    Delay(5); // Folosim funcția ta

    LCD_Send4Bits(0x30);
    Delay(1); // Folosim funcția ta (aprox. de la 150us)

    LCD_Send4Bits(0x30);
    Delay(1); // Folosim funcția ta (aprox. de la 150us)

    LCD_Send4Bits(0x20);

    LCD_Command(0x28);
    LCD_Command(0x0C);
    LCD_Command(0x06);
    LCD_Clear();
}

void LCD_Clear(void) {
    LCD_Command(0x01);
    Delay(2); // Folosim funcția ta
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t address;

    if (row == 0) {
        address = 0x00 + col;
    } else {
        address = 0x40 + col;
    }

    LCD_Command(0x80 | address);
}

void LCD_Print(const char *text) {
    while (*text) {
        LCD_Data((uint8_t)*text);
        text++;
    }
}

void LCD_PrintNumber(uint16_t number) {
    char buffer[6];
    uint8_t i = 0;

    if (number == 0) {
        LCD_Data('0');
        return;
    }

    while (number > 0 && i < sizeof(buffer)) {
        buffer[i++] = (char)('0' + (number % 10));
        number /= 10;
    }

    while (i > 0) {
        LCD_Data(buffer[--i]);
    }
}