#include <avr/io.h>
#include <stdio.h>

// Includem driverele tale hardware personalizate
#include "drivers/adc/adc.h" 
#include "drivers/i2c/i2c.h"
#include "drivers/lcd/lcd.h"
#include "utils/delay.h" // Funcția ta Delay()

// Includem abstractizarea senzorului
#include "drivers/senzor/senzor.h"

int main(void) {
    // --- 1. INIȚIALIZĂRI HARDWARE ---
    ADC_Init();       // Funcția ta din adc.h
    Senzor_Init();    
    LCD_Init();       // Apelează automat I2C_Init() și folosește Delay()
    
    // Configurare praguri temperatură (valori brute ADC 0-1023)
    SenzorConfig_t config_temp;
    Senzor_SetConfig(&config_temp, 200, 400, 600, 800);

    // --- 2. SETUP ECRAN ---
    LCD_Clear();
    LCD_SetCursor(0, 0); 
    LCD_Print("Termometru:");
    
    char lcd_buffer[16];

    // --- 3. BUCLA PRINCIPALĂ ---
    while (1) {
        // Citim valoarea brută de pe A1 (0 - 1023) folosind ADC_Read() sub capotă
        uint16_t adc_val = Senzor_GetRawValue(SENZOR_CHANNEL_A1);
        
        // Calculăm temperatura logic (Exemplu pentru senzor tip LM35)
        uint32_t temp_x10 = ((uint32_t)adc_val * 5000) / 1024; 
        
        uint16_t temp_int = temp_x10 / 10;
        uint16_t temp_zecimal = temp_x10 % 10;
        
        // Evaluăm nivelul de alarmă
        SenzorLevel_t nivel = Senzor_GetLevel(SENZOR_CHANNEL_A1, &config_temp);
        
        // --- 4. AFIȘARE ---
        sprintf(lcd_buffer, "%d.%d \xDF" "C   ", temp_int, temp_zecimal);
        
        LCD_SetCursor(1, 0); 
        LCD_Print("Temp: ");
        LCD_Print(lcd_buffer); 
        
        // Alertă pe marginea dreaptă jos a LCD-ului
        LCD_SetCursor(1, 13); 
        if(nivel == SENZOR_HOT || nivel == SENZOR_VERY_HOT) {
            LCD_Print("HOT");
        } else if (nivel == SENZOR_VERY_COLD) {
            LCD_Print("COLD");
        } else {
            LCD_Print(" OK ");
        }

        // Folosim funcția ta de Delay pentru a face refresh de ecran la jumătate de secundă
        Delay(500); 
    }
    
    return 0;
}