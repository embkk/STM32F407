#ifndef SD_H
#define SD_H

#include <stdio.h>
#include "ff.h"
#include "ffconf.h"
#include "sdcard.h"

#define MAX_BYTES_TO_READ (uint16_t)2048
#define FILENAME "myfile.txt"

extern FATFS fs;
extern FRESULT res;
extern FIL file;
extern FILINFO file_info;
extern DIR dir;
extern SD_CardInfo SDCardInfo;

FRESULT SD_CardMount(void);
FRESULT SD_CardFileRead(void);
FRESULT SD_CardCreateFile(void);
FRESULT SD_CardWriteStream(const char* stream, const uint32_t len);

#endif