#include <stdint.h>
#include <stdio.h>
#include "cc1120_mcu.h"
#include <stdbool.h>

bool extended_address_check(uint8_t address){
    if ((address>0x39 && address<0x64) || (address>0xA0 && address<0xD2) || (address>0xD9)){
        return false;
    } else {
        return true;
    }
}

bool fifo_address_check(uint8_t address){
    if ((address>0x7F && address<0x80) || address>0xFF){
        return false;
    } else {
        return true;
    }
}


bool read_write_message(uint8_t rw_bit, uint8_t burst_bit, uint8_t data[], int data_len,  uint8_t address, uint8_t ext_address, uint8_t results[]) {

//check that bits are valid
    if (rw_bit == 0 || rw_bit == 1 || burst_bit == 0 || burst_bit == 1){

    } else {
        return false;
    }

//header definition
    uint8_t header = 0b00000000;
    header ^= (rw_bit << 7);
    header ^= (burst_bit << 6);
    header ^= address;

//Open port, send header
    mcu_cc1120_cs_assert();
    printf("%d", mcu_cc1120_spi_transfer(header));

//Pass extended address if relevant
    if (address == 0x2F){
        bool ext_address_status = extended_address_check(ext_address);
        if (ext_address_status == true){
        printf("%d", mcu_cc1120_spi_transfer(ext_address));
    } else if (address == 0x3E){
        bool fifo_address_status = fifo_address_check(ext_address);
        if (fifo_address_status == true){
        printf("%d", mcu_cc1120_spi_transfer(ext_address));
        }
    }

    printf("Return data");
//Send data (or garbage data if we're reaing)
    }
    if (burst_bit == 1){
        for (int i = 0; i < data_len; i++) {
         //   printf("%d", mcu_cc1120_spi_transfer(data[i]));
            results[i]=mcu_cc1120_spi_transfer(data[i]);
        }
    } else {
       // printf("%d", mcu_cc1120_spi_transfer(data[0]));
        results[0]=mcu_cc1120_spi_transfer(data[0]);
    }
    mcu_cc1120_cs_deassert();

    return true;

}
bool read_write_message(uint8_t rw_bit, uint8_t burst_bit, uint8_t data[], int data_len,  uint8_t address, uint8_t ext_address, uint8_t results[]);

