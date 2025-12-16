#include <stdint.h>

void SysTickEnable(void) {}

void SysTickDisable(void) {}

void SysTickIntRegister(void (*pfnHandler)(void)) {}

void SysTickIntUnregister(void) {}

void SysTickIntEnable(void) {}

void SysTickIntDisable(void) {}

void SysTickPeriodSet(uint32_t ui32Period) {}

uint32_t SysTickPeriodGet(void) { return 0; }

uint32_t SysTickValueGet(void) { return 0; }