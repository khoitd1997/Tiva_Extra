#include "pwm_utils.hpp"

#include "peripheral_utils.hpp"

// peripheral
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/udma.h"

// hardware
#include <cassert>
#include <cstdint>
#include "inc/hw_memmap.h"
#include "inc/hw_pwm.h"
#include "inc/hw_types.h"

namespace tivaextra {

void pwmConfigure(const uint32_t  pinDesc[PWM_DESCR_LEN],
                  const uint32_t& pwmClockFlag,
                  const float&    pwmFreqKHz,
                  const float&    pwmPulseWidthPercent) {
  PWMGenConfigure(PWM0_BASE,
                  PWM_GEN_0,
                  PWM_GEN_MODE_UP_DOWN | PWM_GEN_MODE_NO_SYNC | PWM_GEN_MODE_GEN_NO_SYNC |
                      PWM_GEN_MODE_FAULT_LATCHED);
  SysCtlPWMClockSet(pwmClockFlag);
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

  PWMPulseWidthSet(PWM0_BASE, PWM_OUT_0, pwmPulseWidthPercent * pwmClockPeriodTick / 100);
}

void pwmEnable(const uint32_t pinDesc[PWM_DESCR_LEN]) {
  PWMGenEnable(pinDesc[PWM_DESCR_MODULE_INDEX], pinDesc[PWM_DESCR_GEN_INDEX]);

  PWMOutputState(pinDesc[PWM_DESCR_MODULE_INDEX],
                 ((PWM_OUT_0 == pinDesc[PWM_DESCR_OUTPUT_INDEX]) ? PWM_OUT_0_BIT : PWM_OUT_1_BIT),
                 true);
}

}  // namespace tivaextra