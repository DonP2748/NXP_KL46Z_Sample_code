
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "uart.h"
#include "debug.h"
#include "flash.h"
#include "led.h"
#include "srec_parsing.h"
#include "service.h"
#include "img_manager.h"


#define IN_COMPLETED 		0
#define COMPLETED 			1

#define INVALID  			0xFFFF

#define MAIL_BOX 			(3) 	//number of mail box
#define LINE_SIZE 			(258) 	//srec line max size

#define MB_FREE 			0
#define MB_FULL 			1


//process firmware info
static uint8_t __status = PROC_STATE_NONE;

//download info
typedef struct mail_box_t{
	uint8_t status;
	uint16_t start;
 	uint16_t end;
}mail_box_t;



static volatile uint16_t recv_count = 0;
static volatile uint8_t line_done_flg = 0;
static volatile uint16_t start = 0;
static volatile uint16_t end = 0;

static uint8_t buffer[MAIL_BOX*LINE_SIZE] = {0};


static FwDataDoneCallback __callback = NULL;
//image info
static uint8_t img_fake_ver = 0;  //fake version for each image download
static uint32_t img_size_cnt = 0;




static void process_firmware_data_done(void);
static void process_firmware_data_moving(void);
static void process_firmware_data_download(void);
static void download_firmware_data_start(void);
static void download_firmware_data_stop(void);
static void write_flash_data(uint32_t addr, uint32_t *data, uint16_t len);


void data_receive_callback(uint8_t data)
{
	//colection data if queue empty and not full
	buffer[recv_count] = data;
	if(data == 'S'){
		start = recv_count;
	}
	else if(data == '\n'){
		end = recv_count;
		line_done_flg++;
		recv_count = 0;
		return;
	}
	recv_count++;
}



void process_firmware_data(void)
{
	switch(__status){
		case PROC_STATE_NONE:
			//do nothing
			break;
		case PROC_STATE_DOWNLOADING:
			//download firmware from uart
			process_firmware_data_download();
			__status = PROC_STATE_MOVING;
			//break; 	//fall through
		case PROC_STATE_MOVING:
			//moving from slot 1(upgrade firmware) to slot 0(running firmware)
			process_firmware_data_moving();
			__status = PROC_STATE_DONE;
			//break; 	//fall through
		case PROC_STATE_DONE:
			//now new firmware ready to run
			process_firmware_data_done();
			__status = PROC_STATE_NONE;
			break;
		default:
			break;
		}
}


uint8_t process_firmware_get_status(void)
{
	return __status;
}

void process_firmware_set_status(uint8_t state)
{
	__status = state;
}


void process_register_firmware_data_done_cb(FwDataDoneCallback callback)
{
	__callback = callback;
}


void process_srec_data_handler(uint32_t addr, uint8_t *data, uint16_t len)
{
	//save to slot 1
	//write 4 bytes per time and len is number of multi uin32_t
	write_flash_data(addr+FW_UPGRADE,(uint32_t*)data,len/4);
	//fake info size
	img_size_cnt += len;
}



static void process_firmware_data_download(void)
{
	uint8_t ret = CODE_OK;
	download_firmware_data_start();
	while(!srec_is_file_valid()){
		if(line_done_flg){ //if line_done_flag so handle line full
			//process firmware data
			uint8_t temp[LINE_SIZE] = {0};
			uint16_t len = end - start + 1;
			memcpy(temp,buffer,len);
			ret = srec_parse_line(temp,len);
			//stop if got error
			if(ret != CODE_OK){
				download_firmware_data_stop();
				debug_log_printf("Process Line start %d end: %d\r\n",start,end);
				while(1);
			}
			line_done_flg--;
		}
	}
	download_firmware_data_stop();
	img_info_t info = {
			.slot   = IMG_SLOT1,
			.ver    = img_fake_ver++,
			.status = COMPLETED,
			.size   = img_size_cnt,
	};
	image_save_info(&info);
	//clear fake img size count
	img_size_cnt = 0;
}


#define BYTES_MOVE 	64
static void process_firmware_data_moving(void)
{
	img_info_t info = {0};
	uint32_t count = 0;

	uint32_t buff[BYTES_MOVE] = {0};
	while(count < info.size){
		uint32_t remain = info.size - count; //update remain bytes
		uint16_t length = (remain < BYTES_MOVE) ? remain : BYTES_MOVE;
		flash_read(FW_UPGRADE+count, buff, length);
		write_flash_data(FW_RUNNING+count, buff, length);
		count += (remain < BYTES_MOVE) ? remain : BYTES_MOVE;
	}

	info.slot = IMG_SLOT1;
	image_get_info(&info);
	info.slot = IMG_SLOT0;
	image_save_info(&info);
}




static void process_firmware_data_done(void)
{
	//run callback when process firmware done
	if(__callback){
		__callback();
	}
}

static void download_firmware_data_start(void)
{
	uart_enable_recv_interrupts(true); //enable transmit last
}


static void download_firmware_data_stop(void)
{
	//stop download firmware with disable transmit first
	uart_enable_recv_interrupts(false);
}




static void write_flash_data(uint32_t addr, uint32_t *data, uint16_t len)
{
	//step over other sector, so erase sector
	if((addr%FLASH_SECTOR_SZ) == 0){
		flash_erase_sector(addr);
	}
	flash_write(addr,data,len);
}





