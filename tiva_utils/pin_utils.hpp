#ifndef _PIN_UTILS_HPP
#define _PIN_UTILS_HPP

#include <cstdint>

namespace tivaextra {

/**
 * @brief how long is the array of array describing each pin, there are 3
 * members for describing: the clock port(like SYSCTL_PERIPH_GPIOB), the gpio
 * port(like GPIO_PORTB_BASE) and the gpio pin(like GPIO_PIN_6)
 */
static const uint32_t PIN_DESCRIPTION_LEN = 3;

/**
 * @brief array index of the member that has the macro for the gpio clock port
 */
static const uint32_t PIN_DESC_CLOCK_INDEX = 0;
/**
 * @brief array index of the member that has the macro for the gpio port
 */
static const uint32_t PIN_DESC_PORT_INDEX = 1;

/**
 * @brief  array index of the member that has the macro for the gpio pin
 */
static const uint32_t PIN_DESC_PIN_INDEX = 2;

void enableClockPeripheral(const uint32_t pinDesc[PIN_DESC_CLOCK_INDEX]);

void pinDescCheck(uint32_t pinDesc[PIN_DESCRIPTION_LEN]);

void pinModeSwitch(const uint32_t pinDesc[PIN_DESCRIPTION_LEN], const bool &isInput);

void pinWrite(const uint32_t pinDesc[PIN_DESCRIPTION_LEN], const bool &output);

bool pinRead(const uint32_t pinDesc[PIN_DESCRIPTION_LEN]);

}  // namespace tivaextra
#endif