#include "general_timer.hpp"

#include <cinttypes>
#include <cstdio>

// TivaC
// peripheral
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

// hardware
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_timer.h"
#include "inc/hw_types.h"

// timer value config
static const uint64_t TIMER_LOAD = 18446744073709551615ull;
static const uint32_t TIMER_MODE = TIMER_CFG_PERIODIC_UP;

// timer register configuration
static const uint32_t TIMER_BASE  = WTIMER0_BASE;
static const uint32_t TIMER_CLOCK = SYSCTL_PERIPH_WTIMER0;
static const uint32_t TIMER_NAME  = TIMER_A;

GeneralTimer& GeneralTimer::getTimer() {
  static auto singleTonTimer = GeneralTimer();
  return singleTonTimer;
}

GeneralTimer::GeneralTimer() {
  ROM_SysCtlPeripheralEnable(TIMER_CLOCK);
  while (!ROM_SysCtlPeripheralReady(TIMER_CLOCK)) {
    // wait until timer peripheral clock is ready
  }

  // use a concacentated 64 bit timer clock
  TimerConfigure(TIMER_BASE, TIMER_MODE);
  TimerLoadSet64(TIMER_BASE, TIMER_LOAD);
  TimerEnable(TIMER_BASE, TIMER_NAME);
}

void GeneralTimer::startTimer(uint64_t& timeStamp) {
  timeStamp = getTimeStamp(TIMER_BASE, TIMER_NAME);
}

uint64_t GeneralTimer::getTimeStamp(uint32_t timerBase, uint32_t timerName) {
  return TimerValueGet64(timerBase);
}

uint64_t GeneralTimer::tickToMicroSec(uint64_t tickCount) {
  return ((float)tickCount / (float)(SysCtlClockGet())) * 1000000;
}

// return time elapsed in microsecond
// TODO: handle clock change
uint64_t GeneralTimer::stopTimer(const uint64_t& intialTimeStamp) {
  uint64_t currTimeStamp = getTimeStamp(TIMER_BASE, TIMER_NAME);

  if (currTimeStamp > intialTimeStamp) {
    // no overflow case
    return tickToMicroSec(currTimeStamp - intialTimeStamp);
  } else {
    // this case meant overflow, assuming overflow once
    return tickToMicroSec(((TIMER_LOAD - intialTimeStamp) + currTimeStamp));
  }
}