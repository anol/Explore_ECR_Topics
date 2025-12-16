#include <stdbool.h>
#include <stdint.h>

static uint_fast8_t _ADCIntNumberGet(uint32_t ui32Base, uint32_t ui32SequenceNum) { return 0; }

void ADCIntRegister(uint32_t ui32Base, uint32_t ui32SequenceNum, void (*pfnHandler)(void)) {}

void ADCIntUnregister(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCIntDisable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCIntEnable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

uint32_t ADCIntStatus(uint32_t ui32Base, uint32_t ui32SequenceNum, bool bMasked) { return 0; }

void ADCIntClear(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCSequenceEnable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCSequenceDisable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCSequenceConfigure(uint32_t ui32Base, uint32_t ui32SequenceNum, uint32_t ui32Trigger, uint32_t ui32Priority) {}

void ADCSequenceStepConfigure(uint32_t ui32Base, uint32_t ui32SequenceNum, uint32_t ui32Step, uint32_t ui32Config) {}

int32_t ADCSequenceOverflow(uint32_t ui32Base, uint32_t ui32SequenceNum) { return 0; }

void ADCSequenceOverflowClear(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

int32_t ADCSequenceUnderflow(uint32_t ui32Base, uint32_t ui32SequenceNum) { return 0; }

void ADCSequenceUnderflowClear(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

int32_t ADCSequenceDataGet(uint32_t ui32Base, uint32_t ui32SequenceNum, uint32_t *pui32Buffer) { return 0; }

void ADCProcessorTrigger(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCSoftwareOversampleConfigure(uint32_t ui32Base, uint32_t ui32SequenceNum, uint32_t ui32Factor) {}

void ADCSoftwareOversampleStepConfigure(int32_t ui32Base, uint32_t ui32SequenceNum,
                                        uint32_t ui32Step, uint32_t ui32Config) {}

void
ADCSoftwareOversampleDataGet(uint32_t ui32Base, uint32_t ui32SequenceNum, uint32_t *pui32Buffer, uint32_t ui32Count) {}

void ADCHardwareOversampleConfigure(uint32_t ui32Base, uint32_t ui32Factor) {}

void ADCComparatorConfigure(uint32_t ui32Base, uint32_t ui32Comp, uint32_t ui32Config) {}

void ADCComparatorRegionSet(uint32_t ui32Base, uint32_t ui32Comp, uint32_t ui32LowRef, uint32_t ui32HighRef) {}

void ADCComparatorReset(uint32_t ui32Base, uint32_t ui32Comp, bool bTrigger, bool bInterrupt) {}

void ADCComparatorIntDisable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCComparatorIntEnable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

uint32_t ADCComparatorIntStatus(uint32_t ui32Base) { return 0; }

void ADCComparatorIntClear(uint32_t ui32Base, uint32_t ui32Status) {}

void ADCIntDisableEx(uint32_t ui32Base, uint32_t ui32IntFlags) {}

void ADCIntEnableEx(uint32_t ui32Base, uint32_t ui32IntFlags) {}

uint32_t ADCIntStatusEx(uint32_t ui32Base, bool bMasked) { return 0; }

void ADCIntClearEx(uint32_t ui32Base, uint32_t ui32IntFlags) {}

void ADCReferenceSet(uint32_t ui32Base, uint32_t ui32Ref) {}

uint32_t ADCReferenceGet(uint32_t ui32Base) { return 0; }

void ADCPhaseDelaySet(uint32_t ui32Base, uint32_t ui32Phase) {}

uint32_t ADCPhaseDelayGet(uint32_t ui32Base) { return 0; }

void ADCSequenceDMAEnable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

void ADCSequenceDMADisable(uint32_t ui32Base, uint32_t ui32SequenceNum) {}

bool ADCBusy(uint32_t ui32Base) { return 0; }

void ADCClockConfigSet(uint32_t ui32Base, uint32_t ui32Config, uint32_t ui32ClockDiv) {}

uint32_t ADCClockConfigGet(uint32_t ui32Base, uint32_t *pui32ClockDiv) { return 0; }