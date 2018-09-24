#ifndef _HARDWARE_HELPER_HPP
#define _HARDWARE_HELPER_HPP
#include <cstdint>

#include "tiva_utils/pin_utils.hpp"

static const uint32_t PIN_CHAR_DESC_LEN = 3;

namespace tivaextra {

// general parsing
void parsePinDesc(const char pinDesc[PIN_CHAR_DESC_LEN],
                  uint32_t   outputPinDesc[PIN_DESCRIPTION_LEN]);

// adc
uint32_t adcPeriphAddrByName(const uint32_t &adcModuleNum);
uint32_t adcAddrFromName(const uint32_t &adcModuleNum);
uint32_t adcFifoOffsetFromName(const uint32_t adcSequenceNum);
uint32_t adcChannelMaskFromName(const uint32_t &pinNumber, char portName);
uint32_t adcTotalSequenceFromSequencer(const uint32_t &sequencerNum);
uint32_t adcDmaIntFlagFromSequencer(const uint32_t &sequencerNum);
uint32_t adcDmaChannelFlagFromSequencerAndMod(const uint32_t &adcModNum,
                                              const uint32_t &adcSequence);
uint32_t adcDmaChannelFromSequenceAndMod(const uint32_t &adcModNum, const uint32_t &adcSequence);

// gpio
uint32_t gpioPeriAddrFromName(const char &portName);
uint32_t gpioPortAddrFromName(const char &portName);
uint32_t gpioMaskFromName(const uint32_t &pinNumber);

// dma
uint32_t dmaSrcIncFromNum(const uint32_t &size);
uint32_t dmaDataSizeFromNum(const uint32_t &size);
uint32_t dmaDestIncFromNum(const uint32_t &size);
uint32_t dmaArbSizeFromNum(const uint32_t &arbSize);
}  // namespace tivaextra
#endif
