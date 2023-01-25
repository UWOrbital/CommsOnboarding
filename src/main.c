#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

#include "cc1120_spi.h"
#include "cc1120_regs.h"


void main() {
    uint8_t freqValue[3];
    
    cc1120_read_ext_addr_spi(CC1120_REGS_EXT_FREQ2, freqValue, 3);

    uint32_t frequency = (freqValue[0] << 16) | (freqValue[1] << 8) | freqValue[2];
    printf("%i, %i, %i\n", freqValue[0], freqValue[1], freqValue[2]);
    return;
}
