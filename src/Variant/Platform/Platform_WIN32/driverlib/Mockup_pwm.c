#include <stdbool.h>
#include <stdint.h>

static bool _PWMGenValid(uint32_t ui32Gen) { return 0; }

static bool _PWMOutValid(uint32_t ui32PWMOut) { return 0; }

void PWMGenConfigure(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Config) {}

void PWMGenPeriodSet(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Period) {}

uint32_t PWMGenPeriodGet(uint32_t ui32Base, uint32_t ui32Gen) { return 0; }

void PWMGenEnable(uint32_t ui32Base, uint32_t ui32Gen) {}

void PWMGenDisable(uint32_t ui32Base, uint32_t ui32Gen) {}

void PWMPulseWidthSet(uint32_t ui32Base, uint32_t ui32PWMOut, uint32_t ui32Width) {}

uint32_t PWMPulseWidthGet(uint32_t ui32Base, uint32_t ui32PWMOut) { return 0; }

void PWMDeadBandEnable(uint32_t ui32Base, uint32_t ui32Gen, uint16_t ui16Rise, uint16_t ui16Fall) {}

void PWMDeadBandDisable(uint32_t ui32Base, uint32_t ui32Gen) {}

void PWMSyncUpdate(uint32_t ui32Base, uint32_t ui32GenBits) {}

void PWMSyncTimeBase(uint32_t ui32Base, uint32_t ui32GenBits) {}

void PWMOutputState(uint32_t ui32Base, uint32_t ui32PWMOutBits, bool bEnable) {}

void PWMOutputInvert(uint32_t ui32Base, uint32_t ui32PWMOutBits, bool bInvert) {}

void PWMOutputFaultLevel(uint32_t ui32Base, uint32_t ui32PWMOutBits, bool bDriveHigh) {}

void PWMOutputFault(uint32_t ui32Base, uint32_t ui32PWMOutBits, bool bFaultSuppress) {}

static uint32_t _PWMGenIntNumberGet(uint32_t ui32Base, uint32_t ui32Gen) { return 0; }

void PWMGenIntRegister(uint32_t ui32Base, uint32_t ui32Gen, void (*pfnIntHandler)(void)) {}

void PWMGenIntUnregister(uint32_t ui32Base, uint32_t ui32Gen) {}

static uint32_t _PWMFaultIntNumberGet(uint32_t ui32Base) { return 0; }

void PWMFaultIntRegister(uint32_t ui32Base, void (*pfnIntHandler)(void)) {}

void PWMFaultIntUnregister(uint32_t ui32Base) {}

void PWMGenIntTrigEnable(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32IntTrig) {}

void PWMGenIntTrigDisable(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32IntTrig) {}

uint32_t PWMGenIntStatus(uint32_t ui32Base, uint32_t ui32Gen, bool bMasked) { return 0; }

void PWMGenIntClear(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Ints) {}

void PWMIntEnable(uint32_t ui32Base, uint32_t ui32GenFault) {}

void PWMIntDisable(uint32_t ui32Base, uint32_t ui32GenFault) {}

void PWMFaultIntClear(uint32_t ui32Base) {}

uint32_t PWMIntStatus(uint32_t ui32Base, bool bMasked) { return 0; }

void PWMFaultIntClearExt(uint32_t ui32Base, uint32_t ui32FaultInts) {}

void PWMGenFaultConfigure(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32MinFaultPeriod, uint32_t ui32FaultSenses) {}

void PWMGenFaultTriggerSet(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Group, uint32_t ui32FaultTriggers) {}

uint32_t PWMGenFaultTriggerGet(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Group) { return 0; }

uint32_t PWMGenFaultStatus(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Group) { return 0; }

void PWMGenFaultClear(uint32_t ui32Base, uint32_t ui32Gen, uint32_t ui32Group, uint32_t ui32FaultTriggers) {}

void PWMClockSet(uint32_t ui32Base, uint32_t ui32Config) {}

uint32_t PWMClockGet(uint32_t ui32Base) { return 0; }

void PWMOutputUpdateMode(uint32_t ui32Base, uint32_t ui32PWMOutBits, uint32_t ui32Mode) {}