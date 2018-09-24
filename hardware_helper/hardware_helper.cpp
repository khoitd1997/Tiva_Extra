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
#include "tiva_utils/pin_utils.hpp"

static const uint32_t PIN_DESC_CHAR_PORT_INDEX = 0;
static const uint32_t PIN_DESC_CHAR_PIN_INDEX  = 1;

namespace tivaextra {

static uint32_t charToNum(char target) {
  assert(isdigit(target));
  return target - '0';
}

// expected format to be like "E5"
void parsePinDesc(const char pinDesc[PIN_CHAR_DESC_LEN],
                  uint32_t   outputPinDesc[PIN_DESCRIPTION_LEN]) {
  assert(pinDesc);
  assert(outputPinDesc);
  assert(2 == strlen(pinDesc));

  outputPinDesc[PIN_DESC_CLOCK_INDEX] = gpioPeriAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
  outputPinDesc[PIN_DESC_PORT_INDEX]  = gpioPortAddrFromName(pinDesc[PIN_DESC_CHAR_PORT_INDEX]);
  outputPinDesc[PIN_DESC_PIN_INDEX] = gpioMaskFromName(charToNum(pinDesc[PIN_DESC_CHAR_PIN_INDEX]));
}
}