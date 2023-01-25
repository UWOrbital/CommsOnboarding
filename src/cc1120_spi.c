#include "cc1120_spi.h"
#include "cc1120_regs.h"
#include <stdint.h>
#include <stdio.h>

#define R_BIT 1 << 7
#define BURST_BIT 1 << 6

bool cc1120_read_ext_addr_spi(uint8_t addr, uint8_t data[], uint8_t len) {
    bool status = true;

    if ((addr > CC1120_REGS_EXT_PA_CFG3 && addr < CC1120_REGS_EXT_WOR_TIME1) ||
        (addr > CC1120_REGS_EXT_XOSC_TEST0 && addr < CC1120_REGS_EXT_RXFIRST) ||
        (addr > CC1120_REGS_EXT_FIFO_NUM_RXBYTES)) {
        status = false; // invalid params
        return status;
    }

    if (len < 1) {
        status = false;
        return status;
    }
    

    if (status) {
        uint8_t header = (len > 1) ? (R_BIT | BURST_BIT | CC1120_REGS_EXT_ADDR) :
                                     (R_BIT | CC1120_REGS_EXT_ADDR);

        mcu_cc1120_cs_assert();
        status = cc1120_send_byte_receive_status(header);
        if (!status) {
            return status;
        }
    }

    if (status) {
        if (mcu_cc1120_spi_transfer(addr) != 0x00) { // When sending the extended address, SO will return all zeros. See section 3.2.
            status = false;
            return status;
        }
    }

    if (status) {
        uint8_t i;
        for(i = 0; i < len; i++) {
            data[i] = mcu_cc1120_spi_transfer(0x00);
            printf("Received: %i\n", data[i]);
        }
    }

    mcu_cc1120_cs_deassert();
    return status;
}

bool cc1120_send_byte_receive_status(uint8_t data) {
    bool status = true;
    union cc_st ccstatus;

    uint8_t i;
    for (i = 1; i <= 5; i++) {
        ccstatus.data = mcu_cc1120_spi_transfer(data);
        if (ccstatus.ccst.chip_ready == 0) {
            break;
        } else {
            status = false;
        }
    }

    return status;
}
