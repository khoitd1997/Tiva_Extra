#ifndef _PWM_UTILS_HPP
#define _PWM_UTILS_HPP

#include <cstdint>

namespace tivaextra {

static const uint32_t PWM_DESCR_LEN = 4;

static const uint32_t PWM_DESCR_MODULE_INDEX = 1;

static const uint32_t PWM_DESCR_GEN_INDEX = 2;

static const uint32_t PWM_DESCR_OUTPUT_INDEX = 3;

void pwmConfigure(const uint32_t  pinDesc[PWM_DESCR_LEN],
                  const uint32_t& pwmClockFlag,
                  const float&    pwmFreqKHz,
                  const float&    pwmPulseWidthFraction,
                  const uint32_t& configFlags);
void pwmConfigureDeadband(const uint32_t  pinDesc[PWM_DESCR_LEN],
                          const bool&     isDeadbBandEnabled,
                          const uint32_t& riseTimeDelay,
                          const uint32_t& fallTimeDelay);
void pwmEnable(const uint32_t pinDesc[PWM_DESCR_LEN], const bool& isDeadBandEnabled);

}  // namespace tivaextra

#endif