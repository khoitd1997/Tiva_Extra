#include "pin_utils.hpp"

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

void enableClockPeripheral(const uint32_t pinDesc[PIN_DESC_CLOCK_INDEX]) {
  SysCtlPeripheralEnable(PIN_DESC_CLOCK_INDEX);
  while (!SysCtlPeripheralReady(pinDesc[PIN_DESC_CLOCK_INDEX])) {
    // wait for clock to be ready
  }
}

void pinDescCheck(uint32_t pinDesc[PIN_DESCRIPTION_LEN]) {
  const uint32_t clockFlag = pinDesc[PIN_DESC_CLOCK_INDEX];
  const uint32_t portFlag  = pinDesc[PIN_DESC_PORT_INDEX];
  const uint32_t pinFlag   = pinDesc[PIN_DESC_PIN_INDEX];

  assert((clockFlag == SYSCTL_PERIPH_GPIOB) || (clockFlag == SYSCTL_PERIPH_GPIOA) ||
         (clockFlag == SYSCTL_PERIPH_GPIOC) || (clockFlag == SYSCTL_PERIPH_GPIOD) ||
         (clockFlag == SYSCTL_PERIPH_GPIOE) || (clockFlag == SYSCTL_PERIPH_GPIOF));

  assert((portFlag == GPIO_PORTA_BASE) || (portFlag == GPIO_PORTB_BASE) ||
         (portFlag == GPIO_PORTC_BASE) || (portFlag == GPIO_PORTD_BASE) ||
         (portFlag == GPIO_PORTE_BASE) || (portFlag == GPIO_PORTF_BASE));

  assert((pinFlag == GPIO_PIN_0) || (pinFlag == GPIO_PIN_1) || (pinFlag == GPIO_PIN_2) ||
         (pinFlag == GPIO_PIN_5) || (pinFlag == GPIO_PIN_3) || (pinFlag == GPIO_PIN_6) ||
         (pinFlag == GPIO_PIN_4) || (pinFlag == GPIO_PIN_7));

  // check for specially allocated pins that should not be used
  assert(!(GPIO_PIN_0 == pinFlag && GPIO_PORTA_BASE == portFlag) &&
         !(GPIO_PIN_1 == pinFlag && GPIO_PORTA_BASE == portFlag) &&
         !(GPIO_PIN_5 == pinFlag && GPIO_PORTA_BASE == portFlag) &&
         !(GPIO_PIN_4 == pinFlag && GPIO_PORTA_BASE == portFlag) &&
         !(GPIO_PIN_3 == pinFlag && GPIO_PORTA_BASE == portFlag) &&
         !(GPIO_PIN_2 == pinFlag && GPIO_PORTA_BASE == portFlag) &&

         !(GPIO_PIN_3 == pinFlag && GPIO_PORTB_BASE == portFlag) &&
         !(GPIO_PIN_2 == pinFlag && GPIO_PORTB_BASE == portFlag) &&

         !(GPIO_PIN_3 == pinFlag && GPIO_PORTC_BASE == portFlag) &&
         !(GPIO_PIN_2 == pinFlag && GPIO_PORTC_BASE == portFlag) &&
         !(GPIO_PIN_1 == pinFlag && GPIO_PORTC_BASE == portFlag) &&
         !(GPIO_PIN_0 == pinFlag && GPIO_PORTC_BASE == portFlag) &&

         !(GPIO_PIN_7 == pinFlag && GPIO_PORTD_BASE == portFlag) &&

         !(GPIO_PIN_0 == pinFlag && GPIO_PORTF_BASE == portFlag));
}

void pinModeSwitch(const uint32_t pinDesc[PIN_DESCRIPTION_LEN], const bool &isInput) {
  if (isInput) {
    GPIOPinTypeGPIOInput(pinDesc[PIN_DESC_PORT_INDEX], pinDesc[PIN_DESC_PIN_INDEX]);
  } else {
    GPIOPinTypeGPIOOutput(pinDesc[PIN_DESC_PORT_INDEX], pinDesc[PIN_DESC_PIN_INDEX]);
  }
}

void pinWrite(const uint32_t pinDesc[PIN_DESCRIPTION_LEN], const bool &output) {
  uint8_t pinOutput = output ? pinDesc[PIN_DESC_PIN_INDEX] : 0;
  GPIOPinWrite(pinDesc[PIN_DESC_PORT_INDEX], pinDesc[PIN_DESC_PIN_INDEX], pinOutput);
}

bool pinRead(const uint32_t pinDesc[PIN_DESCRIPTION_LEN]) {
  return GPIOPinRead(pinDesc[PIN_DESC_PORT_INDEX], pinDesc[PIN_DESC_PIN_INDEX]) ? true : false;
}

}