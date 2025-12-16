#include <stdbool.h>
#include <stdint.h>
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "usblib/usbhid.h"
#include "usblib/device/usbdhid.h"

static void HandleGetDescriptor(void *pvHIDInstance, tUSBRequest *psUSBRequest);

static void HandleRequest(void *pvHIDInstance, tUSBRequest *psUSBRequest);

static void HandleConfigChange(void *pvHIDInstance, uint32_t ui32Info);

static void HandleEP0DataReceived(void *pvHIDInstance, uint32_t ui32Info);

static void HandleEP0DataSent(void *pvHIDInstance, uint32_t ui32Info);

static void HandleReset(void *pvHIDInstance);

static void HandleSuspend(void *pvHIDInstance);

static void HandleResume(void *pvHIDInstance);

static void HandleDisconnect(void *pvHIDInstance);

static void HandleEndpoints(void *pvHIDInstance, uint32_t ui32Status);

static void HandleDevice(void *pvHIDInstance, uint32_t ui32Request, void *pvRequestData);

static void SetDeferredOpFlag(volatile uint16_t *pui16DeferredOp, uint16_t ui16Bit, bool bSet) {}

static void ClearReportTimer(const tUSBDHIDDevice *psHIDDevice, uint8_t ui8ReportID) {}

static void ClearIdleTimers(const tUSBDHIDDevice *psHIDDevice) {}

static void ProcessIdleTimers(const tUSBDHIDDevice *psHIDDevice, uint32_t ui32ElapsedmS) {}

static void SetIdleTimeout(const tUSBDHIDDevice *psHIDDevice, uint8_t ui8ReportID, uint8_t ui8Timeout4mS) {}

static uint32_t GetIdleTimeout(const tUSBDHIDDevice *psHIDDevice, uint8_t ui8ReportID) { return 0; }

static uint32_t FindHIDDescriptor(const tUSBDHIDDevice *a, uint8_t b, uint32_t c, uint32_t *d) { return 0; }

static int32_t ScheduleReportTransmission(tHIDInstance *psHIDInst) { return 0; }

static bool ProcessDataFromHost(tUSBDHIDDevice *psHIDDevice, uint32_t ui32Status) { return 0; }

static bool ProcessDataToHost(tUSBDHIDDevice *psHIDDevice, uint32_t ui32Status) { return 0; }

static void HandleEndpoints(void *pvHIDInstance, uint32_t ui32Status) {}

static void HandleConfigChange(void *pvHIDInstance, uint32_t ui32Info) {}

static void HandleDevice(void *pvHIDInstance, uint32_t ui32Request, void *pvRequestData) {}

static void HandleDisconnect(void *pvHIDInstance) {}

static void HandleGetDescriptor(void *pvHIDInstance, tUSBRequest *psUSBRequest) {}

static void HandleRequest(void *pvHIDInstance, tUSBRequest *psUSBRequest) {}

static void HandleEP0DataReceived(void *pvHIDInstance, uint32_t ui32DataSize) {}

static void HandleEP0DataSent(void *pvHIDInstance, uint32_t ui32Info) {}

static void HandleReset(void *pvHIDInstance) {}

static void HandleSuspend(void *pvHIDInstance) {}

static void HandleResume(void *pvHIDInstance) {}

static void HIDTickHandler(void *pvHIDInstance, uint32_t ui32TimemS) {}

void *USBDHIDInit(uint32_t ui32Index, tUSBDHIDDevice *psHIDDevice) { return 0; }

void *USBDHIDCompositeInit(uint32_t ui32Index, tUSBDHIDDevice *psHIDDevice, tCompositeEntry *psCompEntry) { return 0; }

void USBDHIDTerm(void *pvHIDInstance) {}

void *USBDHIDSetRxCBData(void *pvHIDInstance, void *pvCBData) { return 0; }

void *USBDHIDSetTxCBData(void *pvHIDInstance, void *pvCBData) { return 0; }

uint32_t USBDHIDReportWrite(void *pvHIDInstance, uint8_t *pi8Data, uint32_t ui32Length, bool bLast) { return 0; }

uint32_t USBDHIDPacketRead(void *pvHIDInstance, uint8_t *pi8Data, uint32_t ui32Length, bool bLast) { return 0; }

uint32_t USBDHIDTxPacketAvailable(void *pvHIDInstance) { return 0; }

uint32_t USBDHIDRxPacketAvailable(void *pvHIDInstance) { return 0; }
