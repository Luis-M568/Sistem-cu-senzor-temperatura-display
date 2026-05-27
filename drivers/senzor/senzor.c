#include "senzor.h"
#include "drivers/adc/adc.h" // Se potrivește cu calea pe care ai specificat-o

void Senzor_Init(void) {
    // Hardware-ul ADC este inițializat global în main() prin ADC_Init()
}

void Senzor_SetConfig(SenzorConfig_t* config, uint16_t th_cold, uint16_t th_norm, uint16_t th_hot, uint16_t th_vhot) {
    config->cold_threshold = th_cold;
    config->normal_threshold = th_norm;
    config->hot_threshold = th_hot;
    config->very_hot_threshold = th_vhot;
}

uint16_t Senzor_GetRawValue(uint8_t adc_channel) {
    return ADC_Read(adc_channel); // Apelează funcția ta din adc.h
}

SenzorLevel_t Senzor_GetLevel(uint8_t adc_channel, SenzorConfig_t* config) {
    uint16_t pv = ADC_Read(adc_channel); // Apelează funcția ta din adc.h
    
    if (pv <= config->cold_threshold) { return SENZOR_VERY_COLD; } 
    else if (pv <= config->normal_threshold) { return SENZOR_COLD; } 
    else if (pv <= config->hot_threshold) { return SENZOR_NORMAL; } 
    else if (pv <= config->very_hot_threshold) { return SENZOR_HOT; } 
    
    return SENZOR_VERY_HOT;
}\