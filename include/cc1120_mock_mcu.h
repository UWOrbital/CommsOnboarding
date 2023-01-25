#ifndef CC1120_MOCK_MCU_H
#define CC1120_MOCK_MCU_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Simultaneously sends and receives a byte over CC1120 SPI interface
 * 
 * @param data - Data to transfer 
 * @return uint8_t - Data received from CC1120
 */
uint8_t mock_cc1120_spi_transfer(uint8_t data);

/**
 * @brief Pulls the CS pin low.
 * 
 */
void mock_cc1120_cs_assert();

/**
 * @brief Pulls the CS pin high.
 * 
 */
void mock_cc1120_cs_deassert();

uint8_t cc1120_command_byte_sim(uint8_t data);

uint8_t cc1120_rw_sim(uint8_t data);

#endif /* CC1120_MOCK_MCU_H */
