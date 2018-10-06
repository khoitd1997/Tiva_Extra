#include "swo_segger.h"

void SWO_PrintChar(char c) {
  //
  // Check if ITM_TCR.ITMENA is set
  //
  if ((ITM_TCR & 1) == 0) { return; }
  //
  // Check if stimulus port is enabled
  //
  if ((ITM_ENA & 1) == 0) { return; }
  //
  // Wait until STIMx is ready,
  // then send data
  //
  while ((ITM_STIM_U8 & 1) == 0)
    ;
  ITM_STIM_U8 = c;
}

void SWO_PrintString(const char *s) {
  //
  // Print out character per character
  //
  while (*s) { SWO_PrintChar(*s++); }
}