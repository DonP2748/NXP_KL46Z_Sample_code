#ifndef _SREC_PARSING_H_
#define _SREC_PARSING_H_


#define CODE_OK 			0x01
#define CODE_SYNX 			0x02
#define CODE_TYPE 			0x03
#define CODE_BYTECNT		0x04
#define CODE_CKSUM			0x05
#define CODE_LINECNT  		0x06

typedef void(*SrecProcessDataCallback)(uint8_t* data,uint16_t len);


uint8_t srec_parse_line(uint8_t* data,uint16_t len);
uint8_t srec_is_file_valid(void);



 #endif//_SREC_PARSING_H_
