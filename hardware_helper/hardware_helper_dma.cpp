#include "hardware_helper.hpp"

#include <cassert>
#include <cstdint>

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

namespace tivaextra {

uint32_t dmaSrcIncFromNum(const uint32_t& size) {
  assert(size == 8 || size == 16 || size == 32);
  uint32_t result = 0;
  switch (size) {
    case 8:
      result = UDMA_SIZE_8;
      break;
    case 16:
      result = UDMA_SIZE_16;
      break;
    case 32:
      result = UDMA_SIZE_32;
      break;
  }
  return result;
}

uint32_t dmaDataSizeFromNum(const uint32_t& size) {
  assert(size == 0 || size == 8 || size == 16 || size == 32);
  uint32_t result = 0;
  switch (size) {
    case 0:
      result = UDMA_SRC_INC_NONE;
      break;
    case 8:
      result = UDMA_SRC_INC_8;
      break;
    case 16:
      result = UDMA_SRC_INC_16;
      break;
    case 32:
      result = UDMA_SRC_INC_32;
      break;
  }
  return result;
}
uint32_t dmaDestIncFromNum(const uint32_t& size) {
  assert(size == 0 || size == 8 || size == 16 || size == 32);
  uint32_t result = 0;
  switch (size) {
    case 0:
      result = UDMA_DST_INC_NONE;
      break;
    case 8:
      result = UDMA_DST_INC_8;
      break;
    case 16:
      result = UDMA_DST_INC_16;
      break;
    case 32:
      result = UDMA_DST_INC_32;
      break;
  }
  return result;
}

static const uint32_t TOTAL_VALID_ARB_SIZE = 15;
uint32_t              dmaArbSizeFromNum(const uint32_t& arbSize) {
  const uint32_t validSize[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  const uint32_t validFlag[] = {UDMA_ARB_1,
                                UDMA_ARB_2,
                                UDMA_ARB_4,
                                UDMA_ARB_8,
                                UDMA_ARB_16,
                                UDMA_ARB_32,
                                UDMA_ARB_64,
                                UDMA_ARB_128,
                                UDMA_ARB_256,
                                UDMA_ARB_512,
                                UDMA_ARB_1024};

  for (uint32_t validIndex = 0; validIndex < TOTAL_VALID_ARB_SIZE; ++validIndex) {
    if (validSize[validIndex] == arbSize) { return validFlag[validIndex]; }
  }

  for (;;) {
    // no reason to proceed
  }
}

}