#ifndef CC1120_MCU_H
#define CC1120_MCU_H

#include <stdarg.h>
#include <stdint.h>

/**
 * @brief Simultaneously sends and receives a byte over CC1120 SPI interface
 * 
 * @param data - Data to transfer 
 * @return uint8_t - Data received from CC1120
 */
uint8_t mcu_cc1120_spi_transfer(uint8_t data);

/**
 * @brief Calls the correct CS assert function based on the MCU selected.
 * 
 */
void mcu_cc1120_cs_assert();

/**
 * @brief Calls the correct CS deassert function based on the MCU selected.
 * 
 */
void mcu_cc1120_cs_deassert();

#endif /* CC1120_MCU_H */
