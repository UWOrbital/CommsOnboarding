#include "cc1120_arduino.h"

extern "C" {
#include "cc1120_spi.h"
}

#include "cc1120_regs.h"
#include <SPI.h>

cc1120_log_level_t CC1120_FILE_LOG_LEVEL = CC1120_LOG_LEVEL_OFF;
cc1120_log_level_t CC1120_SERIAL_LOG_LEVEL = CC1120_LOG_LEVEL_DEBUG;

const uint8_t CC1120_RST = 49;
const uint8_t CC1120_CS = 53;
const uint8_t CC1120_MOSI = 51;
const uint8_t CC1120_MISO = 50;
const uint8_t CC1120_SCLK = 52;

/**
 * @brief Set up the SPI pins and the CS pin, run E2E tests.
 * 
 */
void setup() {

}

/**
 * @brief Empty loop.
 * 
 */
void loop() {

}


/**
 * @brief Simultaneously sends and receives a byte over CC1120 SPI interface
 * 
 * @param data - Data to transfer 
 * @return uint8_t - Data received from CC1120
 */
uint8_t arduino_cc1120_spi_transfer(uint8_t data) {
    return SPI.transfer(data);
}

/**
 * @brief Pulls the CS pin low.
 * 
 */
void arduino_cc1120_cs_assert() {
    digitalWrite(CC1120_CS, LOW);
    return;
}

/**
 * @brief Pulls the CS pin high.
 * 
 */
void arduino_cc1120_cs_deassert() {
    digitalWrite(CC1120_CS, HIGH);
    return;
}
