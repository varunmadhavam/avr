/*
 * isp.h
 *
 * Created: 06-01-2017 10:48:29
 *  Author: varunmohan
 */ 

#ifndef ISP_H_
#define ISP_H_

#define RESET SS_POS
#define DIR_RST SPI_DDR
#define PORT_RST SPI_PORT

#define ERROR_DEVICE_NOT_IN_SYNC 0x01
#define SUCCESSFULLY_ENTERD_PROGRAMMING_MODE 0x02
#define SUCCESSFULLY_LEFT_PROGRAMMING_MODE 0x03
#define ERROR_CODE 0xEE
#define SUCCESS_CODE 0x00

void initIsp();
void enableProgramming();
void disableProgramming();
void readSignature();
void chip_erase();
void read_fuse();
void read_lock();
void read_flash();
void write_flash();
void read_eeprom();
void my_delay_ms(int ms);
uint8_t spi_transaction(uint8_t a,uint8_t b,uint8_t c,uint8_t d,int pos);
void spi_transaction_z(uint8_t a,uint8_t b,uint8_t c,uint8_t d);




#endif /* ISP_H_ */