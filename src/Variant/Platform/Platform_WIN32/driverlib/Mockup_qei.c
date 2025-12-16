#include <stdbool.h>
#include <stdint.h>

void QEIEnable(uint32_t ui32Base) {}

void QEIDisable(uint32_t ui32Base) {}

void QEIConfigure(uint32_t ui32Base, uint32_t ui32Config, uint32_t ui32MaxPosition) {}

uint32_t QEIPositionGet(uint32_t ui32Base) { return 0; }

void QEIPositionSet(uint32_t ui32Base, uint32_t ui32Position) {}

int32_t QEIDirectionGet(uint32_t ui32Base) { return 0; }

bool QEIErrorGet(uint32_t ui32Base) { return 0; }

void QEIFilterEnable(uint32_t ui32Base) {}

void QEIFilterDisable(uint32_t ui32Base) {}

void QEIFilterConfigure(uint32_t ui32Base, uint32_t ui32FiltCnt) {}

void QEIVelocityEnable(uint32_t ui32Base) {}

void QEIVelocityDisable(uint32_t ui32Base) {}

void QEIVelocityConfigure(uint32_t ui32Base, uint32_t ui32PreDiv, uint32_t ui32Period) {}

uint32_t QEIVelocityGet(uint32_t ui32Base) { return 0;}

static uint32_t _QEIIntNumberGet(uint32_t ui32Base) { return 0;}

void QEIIntRegister(uint32_t ui32Base, void (*pfnHandler)(void)) {}

void QEIIntUnregister(uint32_t ui32Base) {}

void QEIIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags) {}

void QEIIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags) {}

uint32_t QEIIntStatus(uint32_t ui32Base, bool bMasked) { return 0;}

void QEIIntClear(uint32_t ui32Base, uint32_t ui32IntFlags) {}