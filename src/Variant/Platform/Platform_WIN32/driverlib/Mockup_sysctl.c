#include <stdbool.h>
#include <stdint.h>

static uint32_t _SysCtlMemTimingGet(uint32_t ui32SysClock) { return 0; }

static uint32_t _SysCtlFrequencyGet(uint32_t ui32Xtal) { return 0; }

static bool _SysCtlPeripheralValid(uint32_t ui32Peripheral) { return 0; }

uint32_t SysCtlSRAMSizeGet(void) { return 0; }

uint32_t SysCtlFlashSizeGet(void) { return 0; }

uint32_t SysCtlFlashSectorSizeGet(void) { return 0; }

bool SysCtlPeripheralPresent(uint32_t ui32Peripheral) { return true; }

bool SysCtlPeripheralReady(uint32_t ui32Peripheral) { return 0; }

void SysCtlPeripheralPowerOn(uint32_t ui32Peripheral) {}

void SysCtlPeripheralPowerOff(uint32_t ui32Peripheral) {}

void SysCtlPeripheralReset(uint32_t ui32Peripheral) {}

void SysCtlPeripheralEnable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralDisable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralSleepEnable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralSleepDisable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralDeepSleepEnable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralDeepSleepDisable(uint32_t ui32Peripheral) {}

void SysCtlPeripheralClockGating(bool bEnable) {}

void SysCtlIntRegister(void (*pfnHandler)(void)) {}

void SysCtlIntUnregister(void) {}

void SysCtlIntEnable(uint32_t ui32Ints) {}

void SysCtlIntDisable(uint32_t ui32Ints) {}

void SysCtlIntClear(uint32_t ui32Ints) {}

uint32_t SysCtlIntStatus(bool bMasked) { return 0; }

void SysCtlLDOSleepSet(uint32_t ui32Voltage) {}

uint32_t SysCtlLDOSleepGet(void) { return 0; }

void SysCtlLDODeepSleepSet(uint32_t ui32Voltage) {}

uint32_t SysCtlLDODeepSleepGet(void) { return 0; }

void SysCtlSleepPowerSet(uint32_t ui32Config) {}

void SysCtlDeepSleepPowerSet(uint32_t ui32Config) {}

void SysCtlReset(void) {}

void SysCtlSleep(void) {}

void SysCtlDeepSleep(void) {}

uint32_t SysCtlResetCauseGet(void) { return 0; }

void SysCtlResetCauseClear(uint32_t ui32Causes) {}

void SysCtlDelay(uint32_t ui32Count) {}

void SysCtlMOSCConfigSet(uint32_t ui32Config) {}

uint32_t SysCtlPIOSCCalibrate(uint32_t ui32Type) { return 0; }

void SysCtlResetBehaviorSet(uint32_t ui32Behavior) {}

uint32_t SysCtlResetBehaviorGet(void) { return 0; }

uint32_t SysCtlClockFreqSet(uint32_t ui32Config, uint32_t ui32SysClock) { return 0; }

void SysCtlClockSet(uint32_t ui32Config) {}

uint32_t SysCtlClockGet(void) { return 0; }

void SysCtlDeepSleepClockSet(uint32_t ui32Config) {}

void SysCtlDeepSleepClockConfigSet(uint32_t ui32Div, uint32_t ui32Config) {}

void SysCtlPWMClockSet(uint32_t ui32Config) {}

uint32_t SysCtlPWMClockGet(void) { return 0; }

void SysCtlGPIOAHBEnable(uint32_t ui32GPIOPeripheral) {}

void SysCtlGPIOAHBDisable(uint32_t ui32GPIOPeripheral) {}

void SysCtlUSBPLLEnable(void) {}

void SysCtlUSBPLLDisable(void) {}

void SysCtlVoltageEventConfig(uint32_t ui32Config) {}

uint32_t SysCtlVoltageEventStatus(void) { return 0; }

void SysCtlVoltageEventClear(uint32_t ui32Status) {}

bool SysCtlVCOGet(uint32_t ui32Crystal, uint32_t *pui32VCOFrequency) { return 0; }

uint32_t SysCtlNMIStatus(void) { return 0; }

void SysCtlNMIClear(uint32_t ui32Ints) {}

void SysCtlClockOutConfig(uint32_t ui32Config, uint32_t ui32Div) {}

void SysCtlAltClkConfig(uint32_t ui32Config) {}