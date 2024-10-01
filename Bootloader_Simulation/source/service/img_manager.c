

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "flash.h"
#include "debug.h"
#include "img_manager.h"

#define INVALID 				0xFF
#define IMG_INFO_ADDR 			0x3F000




void image_save_info(img_info_t* info)
{
	if(info){
		img_info_t temp = {0};
		uint32_t addr = (!info->slot) ? (IMG_INFO_ADDR) : (IMG_INFO_ADDR + sizeof(img_info_t));
		uint32_t addr_bk  = (addr != IMG_INFO_ADDR) ? (IMG_INFO_ADDR) : (IMG_INFO_ADDR + sizeof(img_info_t));
		//backup other slot
		flash_read(addr_bk,(uint32_t*)&temp,sizeof(img_info_t)/4);
		//write info
		flash_erase_sector(IMG_INFO_ADDR);
		flash_write(addr,(uint32_t*)info,sizeof(img_info_t)/4);
		flash_write(addr_bk,(uint32_t*)&temp,sizeof(img_info_t)/4);
	}
}

void image_get_info(img_info_t* info)
{
	if(info){
		uint32_t addr = (!info->slot) ? (IMG_INFO_ADDR) : (IMG_INFO_ADDR + sizeof(img_info_t));
		flash_read(addr,(uint32_t*)info,sizeof(img_info_t)/4);
	}
}



uint8_t image_check_firmware_update(void)
{
	uint8_t slot0_ver = 0;
	uint8_t slot1_ver = 0;
	img_info_t info = {0};
	//get slot0
	flash_read(IMG_INFO_ADDR,(uint32_t*)&info,sizeof(img_info_t)/4);
	slot0_ver = info.ver;
	//get slot1
	flash_read(IMG_INFO_ADDR + sizeof(img_info_t),(uint32_t*)&info,sizeof(img_info_t)/4);
	slot1_ver = info.ver;
	//check info
	if(slot0_ver == INVALID){//if slot0 have no image
		if(slot1_ver != INVALID){// and slot1 have an image
			return IMG_UPGRADE; //upgrade
		}
		else{//or if slot1 also have no iamge
			//if in boot mode, always update too
			return IMG_UPDATE;//update
		}
	}
	else{//if slot0 have image
		if(slot1_ver != INVALID){//slot1 have image
			return (slot1_ver > slot0_ver) ? IMG_UPGRADE : IMG_NONE;
		}
		else{//slot1 have no image
			//
		}
	}
	return IMG_NONE;
}



