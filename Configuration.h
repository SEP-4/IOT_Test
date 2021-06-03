
#include "FreeRTOS.h"
#include "semphr.h"

void configuration_create();
uint8_t configuration_get_windows_data();
void configuration_set_windows_data(uint8_t value);
uint8_t configuration_get_humidity_data();
void configuration_set_humidity_data(uint8_t value);
SemaphoreHandle_t get_mutex();