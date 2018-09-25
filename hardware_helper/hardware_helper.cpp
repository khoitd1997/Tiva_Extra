#include "hardware_helper.hpp"

#include <ctype.h>
#include <cassert>
#include <cstdint>
#include <cstring>

// peripheral
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/udma.h"

// hardware
#include "inc/hw_adc.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"

#include "tiva_utils/bit_manipulation.h"
#include "tiva_utils/peripheral_utils.hpp"
#include "tiva_utils/pin_utils.hpp"
#include "tiva_utils/pwm_utils.hpp"

static const uint32_t PIN_DESC_CHAR_PORT_INDEX = 0;
static const uint32_t PIN_DESC_CHAR_PIN_INDEX  = 1;

namespace tivaextra {

static uint32_t charToNum(char target) {
  assert(isdigit(target));
  return target - '0';
}

// expected format to be like "E5"
void initPeripheralPin(const char      pinDesc[PIN_CHAR_DESC_LEN],
                       uint32_t*       outputPinDesc,
                       const uint32_t& pinFlag,
                       PeripheralType  peripheralType) {
  assert(pinDesc);
  assert(outputPinDesc);
  assert(2 == strlen(pinDesc));

  uint32_t pinClock = gpioPeriAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
  uint32_t pinPort  = gpioPortAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
  uint32_t pinNum   = gpioMaskFromName(charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));

  switch (peripheralType) {
    case PeripheralType::GPIO_INPUT:
    case PeripheralType::GPIO_OUTPUT:
      outputPinDesc[PERIPH_DESCR_CLOCK_INDEX] =
          gpioPeriAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
      outputPinDesc[GPIO_DESCR_PORT_INDEX] =
          gpioPortAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
      outputPinDesc[GPIO_DESCR_PIN_INDEX] =
          gpioMaskFromName(charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
      break;

      // case PeripheralType::ADC:
      //   pinClock = adcPeriphAddrByName();
      //   pinPort  = ;
      //   pinNum   = ;
      //   break;

      // case PeripheralType::DMA:
      //   pinClock = ;
      //   pinPort  = ;
      //   pinNum   = ;
      //   break;

    case PeripheralType::PWM:
      outputPinDesc[PERIPH_DESCR_CLOCK_INDEX] = pwmPeriAddrFromName(
          pinDesc[PIN_DESC_CHAR_PORT_INDEX], charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
      outputPinDesc[PWM_DESCR_MODULE_INDEX] = pwmBaseAddrFromName(
          pinDesc[PIN_DESC_CHAR_PORT_INDEX], charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
      outputPinDesc[PWM_DESCR_GEN_INDEX] = pwmGenFromName(
          pinDesc[PIN_DESC_CHAR_PORT_INDEX], charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
      outputPinDesc[PWM_DESCR_OUTPUT_INDEX] = pwmOutputFromName(
          pinDesc[PIN_DESC_CHAR_PORT_INDEX], charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
      break;
  }
  enableClockPeripheral(pinClock, outputPinDesc[PERIPH_DESCR_CLOCK_INDEX]);
  configurePeripheralPin(pinPort, pinNum, pinFlag, peripheralType);
}
}  // namespace tivaextra