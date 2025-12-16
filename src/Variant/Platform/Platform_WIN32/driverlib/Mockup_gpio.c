#include <stdbool.h>
#include <stdint.h>

#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>

int32_t GPIOPinRead(uint32_t ui32Port, uint8_t ui8Pins) {
    if ((ui32Port == GPIO_PORTE_BASE) && (ui8Pins == (GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3))) {
        return 10; // X
    } else {
        return 8;
    }
}

static uint32_t _GPIOIntNumberGet(uint32_t ui32Port) { return 0; }

void GPIODirModeSet(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32PinIO) {}

uint32_t GPIODirModeGet(uint32_t ui32Port, uint8_t ui8Pin) { return 0; }

void GPIOIntTypeSet(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32IntType) {}

uint32_t GPIOIntTypeGet(uint32_t ui32Port, uint8_t ui8Pin) { return 0; }

void GPIOPadConfigSet(uint32_t ui32Port, uint8_t ui8Pins, uint32_t ui32Strength, uint32_t ui32PinType) {}

void GPIOPadConfigGet(uint32_t ui32Port, uint8_t ui8Pin, uint32_t *pui32Strength, uint32_t *pui32PinType) {}

void GPIOIntEnable(uint32_t ui32Port, uint32_t ui32IntFlags) {}

void GPIOIntDisable(uint32_t ui32Port, uint32_t ui32IntFlags) {}

uint32_t GPIOIntStatus(uint32_t ui32Port, bool bMasked) {}

void GPIOIntClear(uint32_t ui32Port, uint32_t ui32IntFlags) {}

void GPIOIntRegister(uint32_t ui32Port, void (*pfnIntHandler)(void)) {}

void GPIOIntUnregister(uint32_t ui32Port) {}

void GPIOIntRegisterPin(uint32_t ui32Port, uint32_t ui32Pin, void (*pfnIntHandler)(void)) {}

void GPIOIntUnregisterPin(uint32_t ui32Port, uint32_t ui32Pin) {}

void GPIOPinWrite(uint32_t ui32Port, uint8_t ui8Pins, uint8_t ui8Val) {}

void GPIOPinTypeADC(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeCAN(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeComparator(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeComparatorOutput(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeDIVSCLK(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeEPI(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeEthernetLED(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeEthernetMII(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeGPIOInput(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeGPIOOutput(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeGPIOOutputOD(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeHibernateRTCCLK(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeI2C(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeI2CSCL(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeLCD(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeOneWire(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypePWM(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeQEI(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeSSI(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeTimer(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeTrace(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeUART(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeUSBAnalog(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeUSBDigital(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeWakeHigh(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOPinTypeWakeLow(uint32_t ui32Port, uint8_t ui8Pins) {}

uint32_t GPIOPinWakeStatus(uint32_t ui32Port) { return 0; }

void GPIOPinConfigure(uint32_t ui32PinConfig) {}

void GPIODMATriggerEnable(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIODMATriggerDisable(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOADCTriggerEnable(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOADCTriggerDisable(uint32_t ui32Port, uint8_t ui8Pins) {}

void GPIOUnlockPin(uint32_t ui32Port, uint8_t ui8Pins) {}
