#include <stdbool.h>
#include <stdint.h>

static bool _SSIBaseValid(uint32_t ui32Base) { return 0; }

static uint32_t _SSIIntNumberGet(uint32_t ui32Base) { return 0; }

void SSIConfigSetExpClk(uint32_t ui32Base, uint32_t ui32SSIClk, uint32_t ui32Protocol, uint32_t ui32Mode,
                        uint32_t ui32BitRate, uint32_t ui32DataWidth) {}

void SSIEnable(uint32_t ui32Base) {}

void SSIDisable(uint32_t ui32Base) {}

void SSIIntRegister(uint32_t ui32Base, void (*pfnHandler)(void)) {}

void SSIIntUnregister(uint32_t ui32Base) {}

void SSIIntEnable(uint32_t ui32Base, uint32_t ui32IntFlags) {}

void SSIIntDisable(uint32_t ui32Base, uint32_t ui32IntFlags) {}

uint32_t SSIIntStatus(uint32_t ui32Base, bool bMasked) { return 0; }

void SSIIntClear(uint32_t ui32Base, uint32_t ui32IntFlags) {}

void SSIDataPut(uint32_t ui32Base, uint32_t ui32Data) {}

int32_t SSIDataPutNonBlocking(uint32_t ui32Base, uint32_t ui32Data) { return 0; }

void SSIDataGet(uint32_t ui32Base, uint32_t *pui32Data) {}

int32_t SSIDataGetNonBlocking(uint32_t ui32Base, uint32_t *pui32Data) { return 0; }

void SSIDMAEnable(uint32_t ui32Base, uint32_t ui32DMAFlags) {}

void SSIDMADisable(uint32_t ui32Base, uint32_t ui32DMAFlags) {}

bool SSIBusy(uint32_t ui32Base) { return 0; }

void SSIClockSourceSet(uint32_t ui32Base, uint32_t ui32Source) {}

uint32_t SSIClockSourceGet(uint32_t ui32Base) { return 0; }

void SSIAdvModeSet(uint32_t ui32Base, uint32_t ui32Mode) {}

void SSIAdvDataPutFrameEnd(uint32_t ui32Base, uint32_t ui32Data) {}

int32_t SSIAdvDataPutFrameEndNonBlocking(uint32_t ui32Base, uint32_t ui32Data) { return 0; }

void SSIAdvFrameHoldEnable(uint32_t ui32Base) {}

void SSIAdvFrameHoldDisable(uint32_t ui32Base) {}

void SSILoopbackEnable(uint32_t ui32Base) {}

void SSILoopbackDisable(uint32_t ui32Base) {}