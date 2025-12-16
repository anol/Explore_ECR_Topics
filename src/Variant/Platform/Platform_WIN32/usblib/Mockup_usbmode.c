#include <stdbool.h>
#include <stdint.h>
#include <usblib/usblib.h>

static void USBOTGSetMode(tUSBMode iUSBMode) {}

void USBStackModeSet(uint32_t ui32Index, tUSBMode iUSBMode, tUSBModeCallback pfnCallback) {}

void USB0DualModeIntHandler(void) {}

void USBDualModeInit(uint32_t ui32Index) {}

void USBDualModeTerm(uint32_t ui32Index) {}

void USBOTGModeTerm(uint32_t ui32Index) {}

void USBOTGModeInit(uint32_t ui32Index, uint32_t ui32PollingRate, void *pvPool, uint32_t ui32PoolSize) {}

static void USBOTGRemovePower(uint32_t ui32Index) {}

void USBOTGPollRate(uint32_t ui32Index, uint32_t ui32PollRate) {}

void USB0OTGModeIntHandler(void) {}

void OTGDeviceDisconnect(uint32_t ui32Index) {}

void USBOTGMain(uint32_t ui32MsTicks) {}

bool USBOTGFeatureSet(uint32_t ui32Index, uint32_t ui32Feature, void *pvFeature) {}
