#ifndef SENZOR_H
#define SENZOR_H

#include <stdint.h>

// Includem driverul tău pentru ADC
// Asigură-te că această cale reflectă exact structura folderelor tale
#include "../adc/adc.h"

// Definim canalul ADC pentru pinul A1
#define SENZOR_CHANNEL_A1 1

/**
 * @brief Nivelurile de temperatură abstractizate.
 */
typedef enum {
    SENZOR_VERY_COLD,  
    SENZOR_COLD,       
    SENZOR_NORMAL,     
    SENZOR_HOT,        
    SENZOR_VERY_HOT    
} SenzorLevel_t;

/**
 * @brief Structura pentru configurarea pragurilor senzorului.
 * Valorile sunt pe 10 biți (0 - 1023) corespunzătoare citirilor ADC.
 */
typedef struct {
    uint16_t cold_threshold;      
    uint16_t normal_threshold;    
    uint16_t hot_threshold;       
    uint16_t very_hot_threshold;  
} SenzorConfig_t;

/**
 * @brief Inițializare hardware pentru senzor.
 */
void Senzor_Init(void);

/**
 * @brief Configurează pragurile pentru senzor (calibrare).
 * * @param config Pointer către structura de configurare
 * @param th_cold Pragul de Very Cold
 * @param th_norm Pragul de Cold / Normal
 * @param th_hot Pragul de Normal / Hot
 * @param th_vhot Pragul de Hot / Very Hot
 */
void Senzor_SetConfig(SenzorConfig_t* config, uint16_t th_cold, uint16_t th_norm, uint16_t th_hot, uint16_t th_vhot);

/**
 * @brief Returnează valoarea analogică brută citită.
 * * @param adc_channel Canalul de pe care se face citirea (ex. SENZOR_CHANNEL_A1)
 * @return uint16_t Valoarea brută (0 - 1023)
 */
uint16_t Senzor_GetRawValue(uint8_t adc_channel);

/**
 * @brief Returnează starea abstractizată a senzorului pe baza valorii ADC și a pragurilor.
 * * @param adc_channel Canalul de pe care se face citirea
 * @param config Pointer către structura cu praguri setate anterior
 * @return SenzorLevel_t Nivelul de temperatură evaluat
 */
SenzorLevel_t Senzor_GetLevel(uint8_t adc_channel, SenzorConfig_t* config);

#endif // SENZOR_H