#ifndef _IMG_MANAGER_H_
#define _IMG_MANAGER_H_


#define IMG_SLOT0 			0
#define IMG_SLOT1 			1


typedef struct img_info_t{
	uint8_t slot;
	uint8_t ver;
	uint16_t status;
	uint32_t size;
}img_info_t;


#define IMG_NONE 			0x00
#define IMG_UPGRADE 		0x01
#define IMG_UPDATE 			0x02


void image_save_info(img_info_t* info);
void image_get_info(img_info_t* info);
uint8_t image_check_firmware_update(void);

 #endif//_IMG_MANAGER_H_
