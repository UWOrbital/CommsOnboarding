#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "cc1120_spi.h"
#include "cc1120_regs.h"


void main() {
    uint8_t results[3];
    uint8_t sample_array[3] = {0,0,0};
    read_write_message(1, 1, sample_array, 3,  0x2F, CC1120_REGS_EXT_FREQ2, results);

    for (int i = 0; i < 3; i++) {
        printf("%d ", results[i]);
    }
    uint32_t frequency = (results[0] << 16) | (results[1] << 8) | results[2];
    uint32_t divisor = 1;
    for (int i = 0; i<17; i++){
        divisor = divisor*2;
    }

    frequency = (frequency/divisor * 32)/4;
    printf("\n");
    printf("%d", frequency);
    printf("\n");
    return;
}
