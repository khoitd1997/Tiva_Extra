#include "hardware_helper.hpp"

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

// TODO: recheck the duplicate pins
namespace tivaextra {
uint32_t pwmPeriAddrFromName(const char &portName, const uint32_t &pinName) {
  switch (portName) {
    case 'A':
      switch (pinName) {
        case 6:
          return SYSCTL_PERIPH_PWM1;
          break;
        case 7:
          return SYSCTL_PERIPH_PWM1;
          break;
      }
      break;

    case 'B':
      switch (pinName) {
        case 6:
          return SYSCTL_PERIPH_PWM0;
          break;

        case 7:
          return SYSCTL_PERIPH_PWM0;
          break;

        case 4:
          return SYSCTL_PERIPH_PWM0;
          break;

        case 5:
          return SYSCTL_PERIPH_PWM0;
          break;
      }
      break;

    case 'C':
      switch (pinName) {
        case 4:
          return SYSCTL_PERIPH_PWM0;
          break;
        case 5:
          return SYSCTL_PERIPH_PWM0;
          break;
      }
      break;

    case 'D':
      switch (pinName) {
        case 6:
          return SYSCTL_PERIPH_PWM0;
          break;
        case 2:
          return SYSCTL_PERIPH_PWM0;
          break;

          // Note: the PD0 and PD1 can also be in the PWM0 also it's not the preferred choice
        case 0:
          return SYSCTL_PERIPH_PWM1;
          break;

        case 1:
          return SYSCTL_PERIPH_PWM1;
          break;
      }
      break;

    case 'E':
      switch (pinName) {
        case 4:
          return SYSCTL_PERIPH_PWM0;
          break;

        case 5:
          return SYSCTL_PERIPH_PWM0;
          break;
      }
      break;

    case 'F':
      switch (pinName) {
        case 2:
          return SYSCTL_PERIPH_PWM1;
          break;

        case 4:
          return SYSCTL_PERIPH_PWM1;
          break;

        case 0:
          return SYSCTL_PERIPH_PWM1;
          break;

        case 1:
          return SYSCTL_PERIPH_PWM1;
          break;

        case 3:
          return SYSCTL_PERIPH_PWM1;
          break;
      }
      break;
  }
  assert(1 == 0);  // can't find any match so there is a mistake somewhere
  return 0;
}

uint32_t pwmBaseAddrFromName(const char &portName, const uint32_t &pinName) {
  switch (portName) {
    case 'A':
      switch (pinName) {
        case 6:
          return PWM1_BASE;
          break;
        case 7:
          return PWM1_BASE;
          break;
      }
      break;

    case 'B':
      switch (pinName) {
        case 6:
          return PWM0_BASE;
          break;

        case 7:
          return PWM0_BASE;
          break;

        case 4:
          return PWM0_BASE;
          break;

        case 5:
          return PWM0_BASE;
          break;
      }
      break;

    case 'C':
      switch (pinName) {
        case 4:
          return PWM0_BASE;
          break;
        case 5:
          return PWM0_BASE;
          break;
      }
      break;

    case 'D':
      switch (pinName) {
        case 6:
          return PWM0_BASE;
          break;
        case 2:
          return PWM0_BASE;
          break;

          // Note: the PD0 and PD1 can also be in the PWM0 also it's not the preferred choice
        case 0:
          return PWM1_BASE;
          break;

        case 1:
          return PWM1_BASE;
          break;
      }
      break;

    case 'E':
      switch (pinName) {
        case 4:
          return PWM0_BASE;
          break;

        case 5:
          return PWM0_BASE;
          break;
      }
      break;

    case 'F':
      switch (pinName) {
        case 2:
          return PWM1_BASE;
          break;

        case 4:
          return PWM1_BASE;
          break;

        case 0:
          return PWM1_BASE;
          break;

        case 1:
          return PWM1_BASE;
          break;

        case 3:
          return PWM1_BASE;
          break;
      }
      break;
  }
  assert(1 == 0);  // can't find any match so there is a mistake somewhere
  return 0;
}

uint32_t pwmGenFromName(const char &portName, const uint32_t &pinName) {
  switch (portName) {
    case 'A':
      switch (pinName) {
        case 6:
          return PWM_GEN_1;
          break;
        case 7:
          return PWM_GEN_1;
          break;
      }
      break;

    case 'B':
      switch (pinName) {
        case 6:
          return PWM_GEN_0;
          break;

        case 7:
          return PWM_GEN_0;
          break;

        case 4:
          return PWM_GEN_1;
          break;

        case 5:
          return PWM_GEN_1;
          break;
      }
      break;

    case 'C':
      switch (pinName) {
        case 4:
          return PWM_GEN_3;
          break;
        case 5:
          return PWM_GEN_3;
          break;
      }
      break;

    case 'D':
      switch (pinName) {
        case 6:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;
        case 2:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;

          // Note: the PD0 and PD1 can also be in the PWM0 also it's not the preferred choice
        case 0:
          return PWM_GEN_0;
          break;

        case 1:
          return PWM_GEN_0;
          break;
      }
      break;

    case 'E':
      switch (pinName) {
        case 4:
          return PWM_GEN_2;
          break;

        case 5:
          return PWM_GEN_2;
          break;
      }
      break;

    case 'F':
      switch (pinName) {
        case 2:
          return PWM_GEN_3;
          break;

        case 4:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;

        case 0:
          return PWM_GEN_2;
          break;

        case 1:
          return PWM_GEN_2;
          break;

        case 3:
          return PWM_GEN_3;
          break;
      }
      break;
  }
  assert(1 == 0);  // can't find any match so there is a mistake somewhere
  return 0;
}

uint32_t pwmOutputFromName(const char &portName, const uint32_t &pinName) {
  switch (portName) {
    case 'A':
      switch (pinName) {
        case 6:
          return PWM_OUT_0;
          break;
        case 7:
          return PWM_OUT_1;
          break;
      }
      break;

    case 'B':
      switch (pinName) {
        case 6:
          return PWM_OUT_0;
          break;

        case 7:
          return PWM_OUT_1;
          break;

        case 4:
          return PWM_OUT_0;
          break;

        case 5:
          return PWM_OUT_1;
          break;
      }
      break;

    case 'C':
      switch (pinName) {
        case 4:
          return PWM_OUT_0;
          break;
        case 5:
          return PWM_OUT_1;
          break;
      }
      break;

    case 'D':
      switch (pinName) {
        case 6:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;
        case 2:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;

          // Note: the PD0 and PD1 can also be in the PWM0 also it's not the preferred choice
        case 0:
          return PWM_OUT_0;
          break;

        case 1:
          return PWM_OUT_1;
          break;
      }
      break;

    case 'E':
      switch (pinName) {
        case 4:
          return PWM_OUT_0;
          break;

        case 5:
          return PWM_OUT_1;
          break;
      }
      break;

    case 'F':
      switch (pinName) {
        case 2:
          return PWM_OUT_0;
          break;

        case 4:
          assert(1 == 0);  // this shouldn' have a generator num
          return 0;
          break;

        case 0:
          return PWM_OUT_0;
          break;

        case 1:
          return PWM_OUT_1;
          break;

        case 3:
          return PWM_OUT_1;
          break;
      }
      break;
  }
  assert(1 == 0);  // can't find any match so there is a mistake somewhere
  return 0;
}
}