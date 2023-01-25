#include "cc1120_mock_mcu.h"
#include <stdlib.h>
#include <stdint.h>
#include "cc1120_regs.h"
#include <stdio.h>

static bool isCSHigh = false;
static bool isCommandByte = true;
static bool isExtAddrByte = true;
static bool rOrW;
static uint8_t addr;
static bool burstMode;
static uint8_t freqVals[3] = {0x6CU, 0x7AU, 0xE1U};
static uint8_t freqIdx = 0;

/**
 * @brief Simultaneously sends and receives a byte over CC1120 SPI interface
 * 
 * @param data - Data to transfer 
 * @return uint8_t - Data received from CC1120
 */
uint8_t mock_cc1120_spi_transfer(uint8_t data) {
    if ((isCommandByte || isExtAddrByte) && !isCSHigh)
        return cc1120_command_byte_sim(data);
    else if (!isCSHigh)
        return cc1120_rw_sim(data);
    
    printf("ERROR: Illegal SPI transfer...\n");
    return 0;
}

/**
 * @brief Pulls the CS pin low.
 * 
 */
void mock_cc1120_cs_assert() {
    isCSHigh = false;
    isCommandByte = true;
    isExtAddrByte = false;
    return;
}

/**
 * @brief Pulls the CS pin high.
 * 
 */
void mock_cc1120_cs_deassert() {
    isCSHigh = true;
    if (!isCommandByte)
        isCommandByte = true;
    return;
}

uint8_t cc1120_command_byte_sim(uint8_t data) {
    if (isExtAddrByte) {
        isExtAddrByte = false;
        addr = data;
        return 0;
    }

    uint8_t chp_rdy = 0;
    if (!chp_rdy && isCommandByte) {
        isCommandByte = false;
        rOrW = data & (1 << 7);
        burstMode = data & (1 << 6);
        addr = data & ((1 << 6)-1);
        if (addr == CC1120_REGS_EXT_ADDR)
            isExtAddrByte = true;
    } else if (!isCommandByte && !isExtAddrByte) {
        printf("ERROR: Something went wrong with the CC1120 sim.\n");
    }
    return (chp_rdy << 7);
}

uint8_t cc1120_rw_sim(uint8_t data) {
    if (!rOrW) {
        printf("ERROR: I don't support write yet!\n");
        return 0;
    }

    printf("Returning: %i\n", freqVals[freqIdx]);
    if (addr == CC1120_REGS_EXT_FREQ2 && burstMode && freqIdx < 3) {
        return freqVals[freqIdx++];
    } else {
        printf("ERROR: You might not be reading the right registers\n");
        return 0;
    }
}
