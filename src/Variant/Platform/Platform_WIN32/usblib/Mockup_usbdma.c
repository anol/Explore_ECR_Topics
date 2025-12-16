
#include <stdint.h>
#include <stdbool.h>
#include <usblib/usblib.h>

static uint32_t uDMAUSBChannelStatus(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) { return 0; }

static uint32_t iDMAUSBChannelStatus(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) { return 0; }

static uint32_t uDMAUSBIntStatus(tUSBDMAInstance *psUSBDMAInst) { return 0; }

static uint32_t iDMAUSBIntStatus(tUSBDMAInstance *psUSBDMAInst) { return 0; }

static void DMAUSBIntStatusClear(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Status) {}

static void DMAUSBIntHandler(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32DMAIntStatus) {}

static void uDMAUSBChannelEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void iDMAUSBChannelEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void uDMAUSBChannelDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void iDMAUSBChannelDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void uDMAUSBChannelIntEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void iDMAUSBChannelIntEnable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void uDMAUSBChannelIntDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static void iDMAUSBChannelIntDisable(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) {}

static uint32_t uDMAUSBTransfer(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel,
                                void *pvBuffer, uint32_t ui32Size) { return 0; }

static uint32_t
iDMAUSBTransfer(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel, void *pvBuffer, uint32_t ui32Size) { return 0; }

static uint32_t uDMAUSBChannelAllocate(tUSBDMAInstance *psUSBDMAInst, uint8_t ui8Endpoint,
                                       uint32_t ui32MaxPacketSize, uint32_t ui32Config) { return 0; }

static uint32_t iDMAUSBChannelAllocate(tUSBDMAInstance *psUSBDMAInst, uint8_t ui8Endpoint,
                                       uint32_t ui32MaxPacketSize, uint32_t ui32Config) { return (0); }

static void uDMAUSBChannelRelease(tUSBDMAInstance *psUSBDMAInst, uint8_t ui32Channel) {}

static void iDMAUSBChannelRelease(tUSBDMAInstance *psUSBDMAInst, uint8_t ui32Channel) {}

static void uDMAUSBUnitSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel, uint32_t ui32BitSize) {}

static void iDMAUSBUnitSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel, uint32_t ui32BitSize) {}

static void uDMAUSBArbSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel, uint32_t ui32ArbSize) {
}

static void iDMAUSBArbSizeSet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel, uint32_t ui32ArbSize) {}

static uint32_t DMAUSBStatus(tUSBDMAInstance *psUSBDMAInst) { return (0); }

void *USBLibDMAAddrGet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) { return 0; }

uint32_t USBLibDMASizeGet(tUSBDMAInstance *psUSBDMAInst, uint32_t ui32Channel) { return 0; }

tUSBDMAInstance *USBLibDMAInit(uint32_t ui32Index) { return 0; }
