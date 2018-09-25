#ifndef _PERIPH_UTILS_HPP
#define _PERIPH_UTILS_HPP

#include <cstdint>

namespace tivaextra {

static const uint32_t PERIPH_DESCR_CLOCK_INDEX = 0;

enum class PeripheralType {
  GPIO_INPUT,
  GPIO_OUTPUT,
  GPIO_OUTPUT_OD,
  ADC,
  PWM,
  DMA,
  CAN,
  UART,
  SPI,
  I2C,
  I2C_SCL,
  TIMER,
  USB_DIGITAL,
  USB_ANALOG,
  QEI,
  TRACE,
  COMPARATOR,
  COMPARATOR_OUTPUT
};

void enableClockPeripheral(const uint32_t& gpioClock, const uint32_t& peripClock);

void configurePeripheralPin(const uint32_t&       portName,
                            const uint32_t&       pinName,
                            const uint32_t&       pinFlag,
                            const PeripheralType& periphType);
}  // namespace tivaextra
#endif