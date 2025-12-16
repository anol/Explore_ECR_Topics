//
// Created by aeols on 12.12.2022.
//

#include "Axis_HID_descriptors.h"
#include "HID_endpoint.h"

HID_endpoint *HID_endpoint::the_one_endpoint{};

HID_endpoint::HID_endpoint() {
    the_one_endpoint = this;
}

HID_device_parameters *HID_endpoint::initialize(uint32_t ui32Index, HID_device_parameters *optional_device) {
    if (optional_device) {
        tUSBDHIDDevice *psHIDDevice = &optional_device->sPrivateData.sHIDDevice;
        void *pvRetcode = composite_initialize(ui32Index, optional_device, nullptr);
        auto *pConfigDesc = (tConfigDescriptor *) get_HID_device_configuration_descriptor();
        pConfigDesc->bmAttributes = optional_device->ui8PwrAttributes;
        pConfigDesc->bMaxPower = (uint8_t) (optional_device->ui16MaxPowermA / 2);
        if (pvRetcode) {
            pvRetcode = USBDHIDInit(ui32Index, psHIDDevice);
            return optional_device;
        }
    }
    return {};
}

void HID_endpoint::terminate(HID_device_parameters *psGamepad) {
    tUSBDHIDDevice *psHIDDevice;
    ASSERT(psGamepad);
    // Get a pointer to the HID device data.
    psHIDDevice = &psGamepad->sPrivateData.sHIDDevice;
    // Mark the device as no longer connected.
    psGamepad->sPrivateData.iState = eHIDGamepadStateNotConnected;
    // Terminate the low level HID driver.
    USBDHIDTerm(psHIDDevice);
}

uint32_t HID_endpoint::on_transmit(void *device, uint32_t event, uint32_t data, void */*optional_data*/) {
    if (device) {
        auto *psGamepad = (HID_device_parameters *) device;
        auto *psInst = (tUSBDGamepadInstance_t *) &psGamepad->sPrivateData;
        if (USB_EVENT_TX_COMPLETE == event) {
            // The last transmission is complete so return to the idle state.
            psInst->iState = eHIDGamepadStateIdle;
            psGamepad->pfnCallback(psGamepad->pvCBData, USB_EVENT_TX_COMPLETE, data, nullptr);
        }
    }
    return (0);
}

uint32_t HID_endpoint::on_receive(void *pvGamepad, uint32_t event, uint32_t data, void *optional_data) {
    tUSBDGamepadInstance_t *psInst;
    HID_device_parameters *psGamepad;
    uint32_t ui32Ret;
    ASSERT(pvGamepad);
    ui32Ret = 0;
    // Get a pointer to our instance data
    psGamepad = (HID_device_parameters *) pvGamepad;
    psInst = &psGamepad->sPrivateData;
    // Which event were we sent?
    switch (event) {
        // The host has connected to us and configured the device.
        case USB_EVENT_CONNECTED: {
            // Now in the idle state.
            psInst->iState = eHIDGamepadStateIdle;
            // Pass the information on to the application.
            psGamepad->pfnCallback(psGamepad->pvCBData, USB_EVENT_CONNECTED, 0, (void *) 0);
            break;
        }
            // The host has disconnected from us.
        case USB_EVENT_DISCONNECTED: {
            psInst->iState = eHIDGamepadStateNotConnected;
            // Pass the information on to the application.
            ui32Ret = psGamepad->pfnCallback(psGamepad->pvCBData, USB_EVENT_DISCONNECTED, 0, (void *) 0);
            break;
        }
            // This handles the Set Idle command.
        case USBD_HID_EVENT_IDLE_TIMEOUT: {
            // Give the pointer to the idle report structure.
            *(void **) optional_data = (void *) &psInst->sReportIdle;
            ui32Ret = sizeof(psInst->sReportIdle);
            break;
        }
            // The host is polling for a particular report and the HID driver is asking for the latest version to transmit.
        case USBD_HID_EVENT_GET_REPORT: {
            // If this is an IN request then pass the request on to the application.  All other requests are ignored.
            if (data == USB_HID_REPORT_IN) {
                ui32Ret = psGamepad->pfnCallback(psGamepad->pvCBData, USBD_HID_EVENT_GET_REPORT, 0, optional_data);
            }
            break;
        }
            // The device class driver has completed sending a report to the host in response to a Get_Report request.
        case USBD_HID_EVENT_REPORT_SENT: {
            // We have nothing to do here.
            ui32Ret = psGamepad->pfnCallback(psGamepad->pvCBData, event, data, optional_data);
            break;
        }
            // Pass these events to the client unchanged.
        case USB_EVENT_ERROR:
        case USB_EVENT_SUSPEND:
        case USB_EVENT_RESUME:
        case USB_EVENT_LPM_RESUME:
        case USB_EVENT_LPM_SLEEP:
        case USB_EVENT_LPM_ERROR: {
            ui32Ret = psGamepad->pfnCallback(psGamepad->pvCBData, event, data, optional_data);
            break;
        }
            // This event is sent in response to a host Set_Report request which is not supported for gamepads.
        case USBD_HID_EVENT_GET_REPORT_BUFFER:
            // We ignore all other events.
        default: {
            ui32Ret = psGamepad->pfnCallback(psGamepad->pvCBData, event, data, optional_data);
            break;
        }
    }
    return (ui32Ret);
}

HID_device_parameters *
HID_endpoint::composite_initialize(uint32_t ui32Index, HID_device_parameters *psGamepad,
                                   tCompositeEntry *psCompEntry) {
    tUSBDGamepadInstance_t *psInst;
    tUSBDHIDDevice *psHIDDevice;
    ASSERT(psGamepad);
    ASSERT(psGamepad->ppui8StringDescriptors);
    ASSERT(psGamepad->pfnCallback);
    // Get a pointer to our instance data
    psInst = &psGamepad->sPrivateData;
    // Initialize the various fields in our instance structure.
    psInst->iState = eHIDGamepadStateNotConnected;
    // Get a pointer to the HID device data.
    psHIDDevice = &psInst->sHIDDevice;
    // Initialize the HID device class instance structure based on input from
    // the caller.
    psHIDDevice->ui16PID = psGamepad->ui16PID;
    psHIDDevice->ui16VID = psGamepad->ui16VID;
    psHIDDevice->ui16MaxPowermA = psGamepad->ui16MaxPowermA;
    psHIDDevice->ui8PwrAttributes = psGamepad->ui8PwrAttributes;
    psHIDDevice->ui8Subclass = 0;
    psHIDDevice->ui8Protocol = 0;
    psHIDDevice->ui8NumInputReports = 1;
    psHIDDevice->psReportIdle = &psInst->sReportIdle;
    psInst->sReportIdle.ui8Duration4mS = 125;
    psInst->sReportIdle.ui8ReportID = 0;
    psInst->sReportIdle.ui32TimeSinceReportmS = 0;
    psInst->sReportIdle.ui16TimeTillNextmS = 0;
    psHIDDevice->pfnTxCallback = on_transmit;
    psHIDDevice->pvRxCBData = (void *) psGamepad;
    psHIDDevice->pfnRxCallback = on_receive;
    psHIDDevice->pvTxCBData = (void *) psGamepad;
    psHIDDevice->bUseOutEndpoint = false;
    psHIDDevice->psHIDDescriptor = get_HID_descriptor();
    psHIDDevice->ppui8ClassDescriptors = get_HID_class_descriptor_table();
    psHIDDevice->ppui8StringDescriptors = psGamepad->ppui8StringDescriptors;
    psHIDDevice->ui32NumStringDescriptors = psGamepad->ui32NumStringDescriptors;
    psHIDDevice->ppsConfigDescriptor = get_HID_configuration_descriptor_table();
//    // If there was an override for the report descriptor then use it.
//    if (psGamepad->pui8ReportDescriptor) {
//        // Save the report descriptor in the list of report descriptors.
//        g_HID_class_descriptor_table[0] = psGamepad->pui8ReportDescriptor;
//        // Override the report descriptor size.
//        g_HID_descriptor.sClassDescriptor[0].wDescriptorLength = psGamepad->ui32ReportSize;
//    }
    // Initialize the lower layer HID driver and pass it the various structures
    // and descriptors necessary to declare that we are a gamepad.
    return static_cast<HID_device_parameters *>(USBDHIDCompositeInit(ui32Index, psHIDDevice, psCompEntry));
}

uint32_t HID_endpoint::send_report(HID_device_parameters *psHIDGamepad, void *pvReport, uint32_t ui32Size) {
    uint32_t ui32Retcode, ui32Count;
    tUSBDGamepadInstance_t *psInst;
    tUSBDHIDDevice *psHIDDevice;
    // Get a pointer to the HID device data.
    psHIDDevice = &psHIDGamepad->sPrivateData.sHIDDevice;
    // Get a pointer to our instance data
    psInst = &psHIDGamepad->sPrivateData;
    // If we are not configured, return an error here before trying to send anything.
    if (psInst->iState == eHIDGamepadStateNotConnected) {
        return (HID_not_configured);
    }
    // Only send a report if the transmitter is currently free.
    if (USBDHIDTxPacketAvailable((void *) psHIDDevice)) {
        // Send the report to the host.
        psInst->iState = eHIDGamepadStateSending;
        ui32Count = USBDHIDReportWrite((void *) psHIDDevice, (uint8_t *) pvReport, ui32Size, true);
        if (ui32Count == 0) {
            ui32Retcode = HID_TX_error;
        } else {
            ui32Retcode = HID_success;
        }
    } else {
        ui32Retcode = HID_TX_error;
    }
    return (ui32Retcode);
}
