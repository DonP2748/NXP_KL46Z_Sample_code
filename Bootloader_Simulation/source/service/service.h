#ifndef _SERVICE_H_
#define _SERVICE_H_


#define PROC_STATE_NONE 			(0x00)
#define PROC_STATE_DOWNLOADING 		(0x01)
#define PROC_STATE_MOVING 			(0x02)
#define PROC_STATE_DONE 			(0x03)

typedef void(*FwDataDoneCallback)(void);

void data_receive_callback(uint8_t data);
void process_firmware_data(void);
void process_register_firmware_data_done_cb(FwDataDoneCallback callback);

void process_firmware_set_status(uint8_t state);
uint8_t process_firmware_get_status(void);
void process_srec_data_handler(uint32_t addr, uint8_t *data, uint16_t len);




 #endif//_SERVICE_H_
