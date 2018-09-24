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
namespace tivaextra {

uint32_t gpioPeriAddrFromName(const char& portName) {
  assert(portName == 'A' || portName == 'B' || portName == 'C' || portName == 'D' ||
         portName == 'E' || portName == 'F');
  uint32_t result = 0;
  switch (portName) {
    case 'A':
      result = SYSCTL_PERIPH_GPIOA;
      break;

    case 'B':
      result = SYSCTL_PERIPH_GPIOB;
      break;

    case 'C':
      result = SYSCTL_PERIPH_GPIOC;
      break;

    case 'D':
      result = SYSCTL_PERIPH_GPIOD;
      break;

    case 'E':
      result = SYSCTL_PERIPH_GPIOE;
      break;

    case 'F':
      result = SYSCTL_PERIPH_GPIOF;
      break;
  }
  return result;
}

uint32_t gpioPortAddrFromName(const char& portName) {
  assert(portName == 'A' || portName == 'B' || portName == 'C' || portName == 'D' ||
         portName == 'E' || portName == 'F');
  uint32_t result = 0;
  switch (portName) {
    case 'A':
      result = GPIO_PORTA_BASE;
      break;

    case 'B':
      result = GPIO_PORTB_BASE;
      break;

    case 'C':
      result = GPIO_PORTC_BASE;
      break;

    case 'D':
      result = GPIO_PORTD_BASE;
      break;

    case 'E':
      result = GPIO_PORTE_BASE;
      break;

    case 'F':
      result = GPIO_PORTF_BASE;
      break;
  }
  return result;
}

uint32_t gpioMaskFromName(const uint32_t& pinNumber) {
  assert(pinNumber < 8);
  return BIT(pinNumber);
}

}