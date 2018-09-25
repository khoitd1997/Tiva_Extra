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

#include "tiva_utils/peripheral_utils.hpp"

namespace tivaextra {

void pinDescCheck(uint32_t pinDesc[GPIO_DESCR_LEN]) {
  const uint32_t clockFlag = pinDesc[PERIPH_DESCR_CLOCK_INDEX];
  const uint32_t portFlag  = pinDesc[GPIO_DESCR_PORT_INDEX];
  const uint32_t pinFlag   = pinDesc[GPIO_DESCR_PIN_INDEX];

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

         !(GPIO_PIN_7 == pinFlag && GPIO_PORTD_BASE == portFlag));

  // namespace tivaextra
}

void gpioModeSwitch(const uint32_t pinDesc[GPIO_DESCR_LEN], const bool &isInput) {
  if (isInput) {
    GPIOPinTypeGPIOInput(pinDesc[GPIO_DESCR_PORT_INDEX], pinDesc[GPIO_DESCR_PIN_INDEX]);
  } else {
    GPIOPinTypeGPIOOutput(pinDesc[GPIO_DESCR_PORT_INDEX], pinDesc[GPIO_DESCR_PIN_INDEX]);
  }
}

void pinWrite(const uint32_t pinDesc[GPIO_DESCR_LEN], const bool &output) {
  uint8_t pinOutput = output ? pinDesc[GPIO_DESCR_PIN_INDEX] : 0;
  GPIOPinWrite(pinDesc[GPIO_DESCR_PORT_INDEX], pinDesc[GPIO_DESCR_PIN_INDEX], pinOutput);
}

bool pinRead(const uint32_t pinDesc[GPIO_DESCR_LEN]) {
  return GPIOPinRead(pinDesc[GPIO_DESCR_PORT_INDEX], pinDesc[GPIO_DESCR_PIN_INDEX]) ? true : false;
}

void gpioPadConfig(const uint32_t  pinDesc[GPIO_DESCR_LEN],
                   const uint32_t &driveStrengthFlag,
                   const uint32_t &pinTypeFlag) {
  assert(pinDesc);
  assert(GPIO_STRENGTH_2MA == driveStrengthFlag || GPIO_STRENGTH_4MA == driveStrengthFlag ||
         GPIO_STRENGTH_6MA == driveStrengthFlag || GPIO_STRENGTH_8MA == driveStrengthFlag ||
         GPIO_STRENGTH_8MA_SC == driveStrengthFlag);

  assert(GPIO_PIN_TYPE_STD == pinTypeFlag || GPIO_PIN_TYPE_STD_WPU == pinTypeFlag ||
         GPIO_PIN_TYPE_STD_WPD == pinTypeFlag || GPIO_PIN_TYPE_OD == pinTypeFlag ||
         GPIO_PIN_TYPE_ANALOG == pinTypeFlag || GPIO_PIN_TYPE_WAKE_HIGH == pinTypeFlag ||
         GPIO_PIN_TYPE_WAKE_LOW == pinTypeFlag);

  GPIOPadConfigSet(pinDesc[GPIO_DESCR_PORT_INDEX],
                   pinDesc[GPIO_DESCR_PIN_INDEX],
                   driveStrengthFlag,
                   pinTypeFlag);
}
}  // namespace tivaextra