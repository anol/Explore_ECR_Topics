
#include <stdint.h>

void FPUEnable(void) {}

void FPUDisable(void) {}

void FPUStackingEnable(void) {}

void FPULazyStackingEnable(void) {}

void FPUStackingDisable(void) {}

void FPUHalfPrecisionModeSet(uint32_t ui32Mode) {}

void FPUNaNModeSet(uint32_t ui32Mode) {}

void FPUFlushToZeroModeSet(uint32_t ui32Mode) {}

void FPURoundingModeSet(uint32_t ui32Mode) {}