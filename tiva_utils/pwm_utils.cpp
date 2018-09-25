#include "pwm_utils.hpp"

#include "peripheral_utils.hpp"

#include <cassert>
#include <cstdint>

// peripheral
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/udma.h"

// hardware
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"

#include "tiva_utils/bit_manipulation.h"

namespace tivaextra {

void pwmConfigure(const uint32_t  pinDesc[PWM_DESCR_LEN],
                  const uint32_t& pwmClockFlag,
                  const float&    pwmFreqKHz,
                  const float&    pwmPulseWidthFraction,
                  const uint32_t& configFlags) {
  PWMGenConfigure(pinDesc[PWM_DESCR_MODULE_INDEX], pinDesc[PWM_DESCR_GEN_INDEX], configFlags);
  SysCtlPWMClockSet(pwmClockFlag);
  for (uint32_t waitIndex = 0; waitIndex < 50; ++waitIndex) {
    // wait until  the PWM clock is set
  }

  assert(pwmClockFlag == SysCtlPWMClockGet());

  uint32_t pwmClockHz = SysCtlClockGet();
  switch (pwmClockFlag) {
    case SYSCTL_PWMDIV_1:
      pwmClockHz /= 1;
      break;
    case SYSCTL_PWMDIV_2:
      pwmClockHz /= 2;
      break;
    case SYSCTL_PWMDIV_4:
      pwmClockHz /= 4;
      break;
    case SYSCTL_PWMDIV_8:
      pwmClockHz /= 8;
      break;
    case SYSCTL_PWMDIV_16:
      pwmClockHz /= 16;
      break;
    case SYSCTL_PWMDIV_32:
      pwmClockHz /= 32;
      break;
    case SYSCTL_PWMDIV_64:
      pwmClockHz /= 64;
      break;
  }

  uint32_t pwmClockPeriodTick = pwmClockHz * (1 / (1000 * pwmFreqKHz));

  PWMGenPeriodSet(
      pinDesc[PWM_DESCR_MODULE_INDEX], pinDesc[PWM_DESCR_GEN_INDEX], pwmClockPeriodTick);

  PWMPulseWidthSet(pinDesc[PWM_DESCR_MODULE_INDEX],
                   pinDesc[PWM_DESCR_OUTPUT_INDEX],
                   (pwmPulseWidthFraction * pwmClockPeriodTick));
}

void pwmConfigureDeadband(const uint32_t  pinDesc[PWM_DESCR_LEN],
                          const bool&     isDeadbBandEnabled,
                          const uint32_t& riseTimeDelay,
                          const uint32_t& fallTimeDelay) {
  isDeadbBandEnabled
      ? PWMDeadBandEnable(pinDesc[PWM_DESCR_MODULE_INDEX],
                          pinDesc[PWM_DESCR_GEN_INDEX],
                          riseTimeDelay,
                          fallTimeDelay)
      : PWMDeadBandDisable(pinDesc[PWM_DESCR_MODULE_INDEX], pinDesc[PWM_DESCR_GEN_INDEX]);
}

void pwmEnable(const uint32_t pinDesc[PWM_DESCR_LEN], const bool& isDeadBandEnabled) {
  uint32_t pwmOutputNumber = (bit_get(pinDesc[PWM_DESCR_OUTPUT_INDEX], 0xf));
  uint32_t pwmOutBit       = 1 << pwmOutputNumber;

  if (isDeadBandEnabled) {
    if (pwmOutputNumber % 2 != 0) {
      pwmOutBit |= 1 << (pwmOutputNumber - 1);
    } else {
      pwmOutBit |= 1 << (pwmOutputNumber + 1);
    }
  }

  PWMOutputState(pinDesc[PWM_DESCR_MODULE_INDEX], pwmOutBit, true);

  PWMGenEnable(pinDesc[PWM_DESCR_MODULE_INDEX], pinDesc[PWM_DESCR_GEN_INDEX]);
}
}  // namespace tivaextra