#include "cc1120_mcu.h"
#include "cc1120_mock_mcu.h"
#include <stdio.h>
#include <stdint.h>

/**
 * @brief Simultaneously sends and receives a byte over CC1120 SPI interface
 * 
 * @param data - Data to transfer 
 * @return uint8_t - Data received from CC1120
 */
uint8_t mcu_cc1120_spi_transfer(uint8_t data) {
    uint8_t received;
    #ifdef CC1120_MOCK_MCU_H
    received = mock_cc1120_spi_transfer(data);
    #elif defined CC1120_ARDUINO_H
    received = arduino_cc1120_spi_transfer(data);
    #elif defined CC1120_RM46_H
    received = rm46_cc1120_spi_transfer(data);
    #endif

    return received;
}

/**
 * @brief Calls the correct CS assert function based on the MCU selected.
 * 
 */
void mcu_cc1120_cs_assert() {
    #ifdef CC1120_MOCK_MCU_H
    mock_cc1120_cs_assert();
    #elif defined CC1120_ARDUINO_H
    arduino_cc1120_cs_assert();
    #elif defined CC1120_RM46_H
    rm46_cc1120_cs_assert();
    #endif
}

/**
 * @brief Calls the correct CS deassert function based on the MCU selected.
 * 
 */
void mcu_cc1120_cs_deassert() {
    #ifdef CC1120_MOCK_MCU_H
    mock_cc1120_cs_deassert();
    #elif defined CC1120_ARDUINO_H
    arduino_cc1120_cs_deassert();
    #elif defined CC1120_RM46_H
    rm46_cc1120_cs_deassert();
    #endif
}
