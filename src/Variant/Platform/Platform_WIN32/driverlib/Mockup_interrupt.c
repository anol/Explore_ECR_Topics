#include <stdbool.h>
#include <stdint.h>

static void _IntDefaultHandler(void) {}

bool IntMasterEnable(void) { return 0; }

bool IntMasterDisable(void) { return 0; }

void IntRegister(uint32_t ui32Interrupt, void (*pfnHandler)(void)) {}

void IntUnregister(uint32_t ui32Interrupt) {}

void IntPriorityGroupingSet(uint32_t ui32Bits) {}

uint32_t IntPriorityGroupingGet(void) { return 0; }

void IntPrioritySet(uint32_t ui32Interrupt, uint8_t ui8Priority) {}

int32_t IntPriorityGet(uint32_t ui32Interrupt) { return 0; }

void IntEnable(uint32_t ui32Interrupt) {}

void IntDisable(uint32_t ui32Interrupt) {}

uint32_t IntIsEnabled(uint32_t ui32Interrupt) { return 0; }

void IntPendSet(uint32_t ui32Interrupt) {}

void IntPendClear(uint32_t ui32Interrupt) {}

void IntPriorityMaskSet(uint32_t ui32PriorityMask) {}

uint32_t IntPriorityMaskGet(void) { return 0; }

void IntTrigger(uint32_t ui32Interrupt) {}
