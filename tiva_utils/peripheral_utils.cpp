#include "peripheral_utils.hpp"

// peripheral
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"

// hardware
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include <cassert>
#include <cstdint>

namespace tivaextra {
void enableClockPeripheral(const uint32_t& gpioClock, const uint32_t& peripClock) {
  SysCtlPeripheralEnable(gpioClock);
  while (!SysCtlPeripheralReady(gpioClock)) {
    // wait for clock to be ready
  }

  SysCtlPeripheralEnable(peripClock);
  while (!SysCtlPeripheralReady(peripClock)) {
    // wait for clock to be ready
  }
}

static void configurePinType(const uint32_t&       portName,
                             const uint32_t&       pinName,
                             const PeripheralType& periphType) {
  switch (periphType) {
    case PeripheralType::GPIO_INPUT:
      GPIOPinTypeGPIOInput(portName, pinName);
      break;
    case PeripheralType::GPIO_OUTPUT:
      GPIOPinTypeGPIOOutput(portName, pinName);
      break;
    case PeripheralType::GPIO_OUTPUT_OD:
      GPIOPinTypeGPIOOutputOD(portName, pinName);
      break;
    case PeripheralType::ADC:
      GPIOPinTypeADC(portName, pinName);
      break;
    case PeripheralType::PWM:
      GPIOPinTypePWM(portName, pinName);
      break;
    case PeripheralType::DMA:
      break;
    case PeripheralType::CAN:
      GPIOPinTypeCAN(portName, pinName);
      break;
    case PeripheralType::UART:
      GPIOPinTypeUART(portName, pinName);
      break;
    case PeripheralType::SPI:
      GPIOPinTypeSSI(portName, pinName);
      break;
    case PeripheralType::I2C:
      GPIOPinTypeI2C(portName, pinName);
      break;
    case PeripheralType::I2C_SCL:
      GPIOPinTypeI2CSCL(portName, pinName);
      break;
    case PeripheralType::TIMER:
      GPIOPinTypeTimer(portName, pinName);
      break;
    case PeripheralType::USB_DIGITAL:
      GPIOPinTypeUSBDigital(portName, pinName);
      break;
    case PeripheralType::USB_ANALOG:
      GPIOPinTypeUSBAnalog(portName, pinName);
      break;
    case PeripheralType::QEI:
      GPIOPinTypeQEI(portName, pinName);
      break;
    case PeripheralType::TRACE:
      GPIOPinTypeTrace(portName, pinName);
      break;
    case PeripheralType::COMPARATOR:
      GPIOPinTypeComparator(portName, pinName);
      break;
    case PeripheralType::COMPARATOR_OUTPUT:
      GPIOPinTypeComparatorOutput(portName, pinName);
      break;
  }
}

void configurePeripheralPin(const uint32_t&       portName,
                            const uint32_t&       pinName,
                            const uint32_t&       pinFlag,
                            const PeripheralType& periphType) {
  configurePinType(portName, pinName, periphType);
  if ((PeripheralType::GPIO_INPUT != periphType) && (PeripheralType::GPIO_OUTPUT != periphType) &&
      (PeripheralType::GPIO_OUTPUT_OD != periphType)) {
    GPIOPinConfigure(pinFlag);
  }

  // // TODO: finish deciding what to do with this
  // switch (portName) {
  //   case GPIO_PORTA_BASE:
  //     switch (pinName) {
  //       case GPIO_PIN_0:
  //         switch (periphType) {
  //           case PeripheralType::UART:
  //             GPIOPinConfigure(GPIO_PA0_U0RX);
  //             break;
  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PA0_CAN1RX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_1:
  //         switch (periphType) {
  //           case PeripheralType::UART:
  //             GPIOPinConfigure(GPIO_PA1_U0TX);
  //             break;
  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PA1_CAN1TX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_2:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PA2_SSI0CLK);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_3:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PA3_SSI0FSS);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_4:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PA4_SSI0RX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_5:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PA5_SSI0TX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_6:
  //         switch (periphType) {
  //           case PeripheralType::I2C_SCL:
  //             GPIOPinConfigure(GPIO_PA6_I2C1SCL);
  //             break;

  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PA6_M1PWM2);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_7:
  //         switch (periphType) {
  //           case PeripheralType::I2C:
  //             GPIOPinConfigure(GPIO_PA7_I2C1SDA);
  //             break;

  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PA7_M1PWM3);
  //             break;
  //         }
  //         break;
  //     }
  //     break;

  //   case GPIO_PORTB_BASE:
  //     switch (pinName) {
  //       case GPIO_PIN_0:
  //         switch (periphType) {
  //           case PeripheralType::UART:
  //             GPIOPinConfigure(GPIO_PB0_U1RX);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB0_T2CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_1:
  //         switch (periphType) {
  //           case PeripheralType::UART:
  //             GPIOPinConfigure(GPIO_PB1_U1TX);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB1_T2CCP1);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_2:
  //         switch (periphType) {
  //           case PeripheralType::I2C_SCL:
  //             GPIOPinConfigure(GPIO_PB2_I2C0SCL);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB2_T3CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_3:
  //         switch (periphType) {
  //           case PeripheralType::I2C:
  //             GPIOPinConfigure(GPIO_PB3_I2C0SDA);
  //             break;

  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB3_T3CCP1);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_4:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB4_SSI2CLK);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB4_M0PWM2);
  //             break;

  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB4_T1CCP0);
  //             break;

  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PB4_CAN0RX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_5:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB5_SSI2FSS);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB5_M0PWM3);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB5_T1CCP1);
  //             break;
  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PB5_CAN0TX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_6:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB6_SSI2RX);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB6_M0PWM0);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB6_T0CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_7:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB7_SSI2TX);
  //             break;

  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB7_M0PWM1);
  //             break;

  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB7_T0CCP1);
  //             break;
  //         }
  //         break;
  //     }

  //     break;

  //   case GPIO_PORTC_BASE:
  //     switch (pinName) {
  //       case GPIO_PIN_0:
  //         switch (periphType) {
  //           // TODO: Check the TRACE SWD thingy of this pin
  //           case PeripheralType::TRACE:
  //             GPIOPinConfigure(GPIO_PC0_TCK);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PC0_T4CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_1:
  //         // TODO: Check the TRACE SWD thingy of this pin
  //         switch (periphType) {
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PC1_T4CCP1);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_2:
  //         switch (periphType) {
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PC2_T5CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_3:
  //         switch (periphType) {
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PC3_T5CCP1);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_4:
  //         switch (periphType) {
  //           case PeripheralType::UART:
  //             GPIOPinConfigure(GPIO_PB4_SSI2CLK);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB4_M0PWM2);
  //             break;

  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB4_T1CCP0);
  //             break;

  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PB4_CAN0RX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_5:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB5_SSI2FSS);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB5_M0PWM3);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB5_T1CCP1);
  //             break;
  //           case PeripheralType::CAN:
  //             GPIOPinConfigure(GPIO_PB5_CAN0TX);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_6:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB6_SSI2RX);
  //             break;
  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB6_M0PWM0);
  //             break;
  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB6_T0CCP0);
  //             break;
  //         }
  //         break;

  //       case GPIO_PIN_7:
  //         switch (periphType) {
  //           case PeripheralType::SPI:
  //             GPIOPinConfigure(GPIO_PB7_SSI2TX);
  //             break;

  //           case PeripheralType::PWM:
  //             GPIOPinConfigure(GPIO_PB7_M0PWM1);
  //             break;

  //           case PeripheralType::TIMER:
  //             GPIOPinConfigure(GPIO_PB7_T0CCP1);
  //             break;
  //         }
  //         break;
  //     }

  //     break;
  // }

  // #define GPIO_PC4_U4RX 0x00021001
  // #define GPIO_PC4_U1RX 0x00021002
  // #define GPIO_PC4_M0PWM6 0x00021004
  // #define GPIO_PC4_IDX1 0x00021006
  // #define GPIO_PC4_WT0CCP0 0x00021007
  // #define GPIO_PC4_U1RTS 0x00021008

  // #define GPIO_PC5_U4TX 0x00021401
  // #define GPIO_PC5_U1TX 0x00021402
  // #define GPIO_PC5_M0PWM7 0x00021404
  // #define GPIO_PC5_PHA1 0x00021406
  // #define GPIO_PC5_WT0CCP1 0x00021407
  // #define GPIO_PC5_U1CTS 0x00021408

  // #define GPIO_PC6_U3RX 0x00021801
  // #define GPIO_PC6_PHB1 0x00021806
  // #define GPIO_PC6_WT1CCP0 0x00021807
  // #define GPIO_PC6_USB0EPEN 0x00021808

  // #define GPIO_PC7_U3TX 0x00021C01
  // #define GPIO_PC7_WT1CCP1 0x00021C07
  // #define GPIO_PC7_USB0PFLT 0x00021C08

  // #define GPIO_PD0_SSI3CLK 0x00030001
  // #define GPIO_PD0_SSI1CLK 0x00030002
  // #define GPIO_PD0_I2C3SCL 0x00030003
  // #define GPIO_PD0_M0PWM6 0x00030004
  // #define GPIO_PD0_M1PWM0 0x00030005
  // #define GPIO_PD0_WT2CCP0 0x00030007

  // #define GPIO_PD1_SSI3FSS 0x00030401
  // #define GPIO_PD1_SSI1FSS 0x00030402
  // #define GPIO_PD1_I2C3SDA 0x00030403
  // #define GPIO_PD1_M0PWM7 0x00030404
  // #define GPIO_PD1_M1PWM1 0x00030405
  // #define GPIO_PD1_WT2CCP1 0x00030407

  // #define GPIO_PD2_SSI3RX 0x00030801
  // #define GPIO_PD2_SSI1RX 0x00030802
  // #define GPIO_PD2_M0FAULT0 0x00030804
  // #define GPIO_PD2_WT3CCP0 0x00030807
  // #define GPIO_PD2_USB0EPEN 0x00030808

  // #define GPIO_PD3_SSI3TX 0x00030C01
  // #define GPIO_PD3_SSI1TX 0x00030C02
  // #define GPIO_PD3_IDX0 0x00030C06
  // #define GPIO_PD3_WT3CCP1 0x00030C07
  // #define GPIO_PD3_USB0PFLT 0x00030C08

  // #define GPIO_PD4_U6RX 0x00031001
  // #define GPIO_PD4_WT4CCP0 0x00031007

  // #define GPIO_PD5_U6TX 0x00031401
  // #define GPIO_PD5_WT4CCP1 0x00031407

  // #define GPIO_PD6_U2RX 0x00031801
  // #define GPIO_PD6_M0FAULT0 0x00031804
  // #define GPIO_PD6_PHA0 0x00031806
  // #define GPIO_PD6_WT5CCP0 0x00031807

  // #define GPIO_PD7_U2TX 0x00031C01
  // #define GPIO_PD7_PHB0 0x00031C06
  // #define GPIO_PD7_WT5CCP1 0x00031C07
  // #define GPIO_PD7_NMI 0x00031C08

  // #define GPIO_PE0_U7RX 0x00040001

  // #define GPIO_PE1_U7TX 0x00040401

  // #define GPIO_PE4_U5RX 0x00041001
  // #define GPIO_PE4_I2C2SCL 0x00041003
  // #define GPIO_PE4_M0PWM4 0x00041004
  // #define GPIO_PE4_M1PWM2 0x00041005
  // #define GPIO_PE4_CAN0RX 0x00041008

  // #define GPIO_PE5_U5TX 0x00041401
  // #define GPIO_PE5_I2C2SDA 0x00041403
  // #define GPIO_PE5_M0PWM5 0x00041404
  // #define GPIO_PE5_M1PWM3 0x00041405
  // #define GPIO_PE5_CAN0TX 0x00041408

  // #define GPIO_PF0_U1RTS 0x00050001
  // #define GPIO_PF0_SSI1RX 0x00050002
  // #define GPIO_PF0_CAN0RX 0x00050003
  // #define GPIO_PF0_M1PWM4 0x00050005
  // #define GPIO_PF0_PHA0 0x00050006
  // #define GPIO_PF0_T0CCP0 0x00050007
  // #define GPIO_PF0_NMI 0x00050008
  // #define GPIO_PF0_C0O 0x00050009

  // #define GPIO_PF1_U1CTS 0x00050401
  // #define GPIO_PF1_SSI1TX 0x00050402
  // #define GPIO_PF1_M1PWM5 0x00050405
  // #define GPIO_PF1_PHB0 0x00050406
  // #define GPIO_PF1_T0CCP1 0x00050407
  // #define GPIO_PF1_C1O 0x00050409
  // #define GPIO_PF1_TRD1 0x0005040E

  // #define GPIO_PF2_SSI1CLK 0x00050802
  // #define GPIO_PF2_M0FAULT0 0x00050804
  // #define GPIO_PF2_M1PWM6 0x00050805
  // #define GPIO_PF2_T1CCP0 0x00050807
  // #define GPIO_PF2_TRD0 0x0005080E

  // #define GPIO_PF3_SSI1FSS 0x00050C02
  // #define GPIO_PF3_CAN0TX 0x00050C03
  // #define GPIO_PF3_M1PWM7 0x00050C05
  // #define GPIO_PF3_T1CCP1 0x00050C07
  // #define GPIO_PF3_TRCLK 0x00050C0E

  // #define GPIO_PF4_M1FAULT0 0x00051005
  // #define GPIO_PF4_IDX0 0x00051006
  // #define GPIO_PF4_T2CCP0 0x00051007
  // #define GPIO_PF4_USB0EPEN 0x00051008
}
}  // namespace tivaextra