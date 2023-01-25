#ifndef CC1120_SPI_H
#define CC1120_SPI_H
#include <stdbool.h>
#include <stdint.h>

struct cc_status {
  uint8_t res : 4;
  uint8_t state : 3;
  uint8_t chip_ready : 1;
};

union cc_st {
  struct cc_status ccst;
  uint8_t data;
};

bool cc1120_read_ext_addr_spi(uint8_t addr, uint8_t data[], uint8_t len);

bool cc1120_send_byte_receive_status(uint8_t data);

#endif /* CC1120_SPI_H */
