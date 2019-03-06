#include <string.h>
#include "ff.h"
#include <stdio.h>
#include "diskio.h"
#include "usbIO.h"

int scan_files (
    char* path        /* Start node to be scanned (***also used as work area***) */
)
{
  FRESULT res;
  DIR dir;
  UINT i;
  static FILINFO fno;
  res = f_opendir(&dir, path);                       /* Open the directory */
  if (res == FR_OK) {
    for (;;) {
      res = f_readdir(&dir, &fno);                   /* Read a directory item */
      if (res != FR_OK || fno.fname[0] == 0) break;  /* Break on error or end of dir */
      if (fno.fattrib & AM_DIR) {                    /* It is a directory */
        i = strlen(path);
        sprintf(&path[i], "%s", fno.fname);
        res = scan_files(path);                    /* Enter the directory */
        if (res != FR_OK) break;
        path[i] = 0;
      } else {                                       /* It is a file. */
        char printed[20];
        int length = 0;
        if((strcmp(path, "/")) == 0)
          length = sprintf(printed, "%s%s\r\n",path, fno.fname);
        else
          length = sprintf(printed, "%s/%s\r\n",path, fno.fname);
        write_usb_serial_blocking(printed, length);
      }
    }
    f_closedir(&dir);
  }
  return res;
}

int list_files()
{
  FATFS fs;
  FRESULT res;
  char buff[256];
  f_mount(&fs, "", 0);
  strcpy(buff, "/");
  scan_files(buff);
}

int file_exists(char * filename)
{
  FRESULT fr;
  FILINFO fno;
  FATFS fs;

  f_mount(&fs, "",0);
  fr = f_stat(filename, &fno);

  switch(fr){
    case FR_OK:
      write_usb_serial_blocking("Found it\r\n",10);
      break;
    case FR_NO_FILE:
      write_usb_serial_blocking("not found it\r\n",14);
      return 1;
    default:
      write_usb_serial_blocking("error\r\n", 7);
      return 1;
  }
  return 0;
}

int test_append(char * filename, char * contents, int len)
{
  FATFS FatFs;
  FIL fil;        /* File object */
  FRESULT fr;     /* FatFs return code */


  /* Register work area to the default drive */
  f_mount(&FatFs, "", 0);

  /* Open a text file */
  fr = f_open(&fil, filename, FA_OPEN_APPEND | FA_WRITE);
  //write_usb_serial_blocking("haha\r\n",6);
  if (fr) return (int)fr;
//  write_usb_serial_blocking("just test\r\n", 12);
  /* Read every line and display it */
  int length = 20;
  //write_usb_serial_blocking("haha\r\n",6);

  f_write(&fil, contents, len, &length);

//  write_usb_serial_blocking("yeet\r\n",6);unsigned short * test_read_part(char * filename)

  f_sync(&fil);
  /* Close the file */
  f_close(&fil);
  return 0;
}

unsigned long long file_pos = 0x30000;

unsigned short * test_read_part(char * filename, int mode)
{
  //write_usb_serial_blocking();
  FATFS FatFs;
  FIL fil;        /* File object */
  //char line[4096]; /* Line buffer */
  FRESULT fr;


  f_mount(&FatFs, "", 0);

  int amount_to_read = 10000;

  write_usb_serial_blocking("1\r\n", 3);

  fr = f_open(&fil, filename, FA_READ);

  if (fr) return (int)fr;

//  if(file_pos>=f_size(&fil))//upcoming error since length has to be on a per file basis
  //  return 1;

  int length = 0;

  volatile unsigned short line[amount_to_read];
  f_lseek(&fil, file_pos);
  f_read(&fil, line, sizeof(line), &length);
  file_pos += length;

  int i = 0;
  //for(i = 0; i<amount_to_read; i++)
  //{
    //char test[10];
    //int help = sprintf(test, "%x ", line[i]);
  //  write_usb_serial_blocking(test, help);
//  }

  write_usb_serial_blocking("success\r\n", 9);
  /* Close the file */
  f_close(&fil);

  return line;

}

int test_opening(char * filename)
{
    FATFS FatFs;
    FIL fil;        /* File object */
    //char line[4096]; /* Line buffer */
    FRESULT fr;     /* FatFs return code */

    //write_usb_serial_blocking("hahayes\r\n",10);

    /* Register work area to the default drive */
    f_mount(&FatFs, "", 0);

    /* Open a text file */
  //  fr = f_open(&fil, "/thisIsTheTestFile.txt", FA_READ);
    fr = f_open(&fil, filename, FA_READ);
    if (fr) return (int)fr;
    //int length = f_size(&fil);
    //write_usb_serial_blocking("guess not\r\n",11);

    /* Read every line and display it */
    //int length = sizeof(line);
  //  char line[length];
    //f_read(&fil, line, length, &length);
    int length = 0;
    char line[100];
    f_read(&fil, line, 100, &length);

  //  line[length+1] = '\r';
    //line[length+2] = '\n';
    int i = 0;
    for(i = 0; i<100; i++)
    {
      char test[10];
      int help = sprintf(test, "%x", line[i]);
      write_usb_serial_blocking(test, help);
    }
    //write_usb_serial_blocking(line,100);
    //write_usb_serial_blocking(line,length);

    write_usb_serial_blocking("\r\n", 2);
    /* Close the file */
    f_close(&fil);

    return 0;
}

int test_write(char * filename, char * contents, int len)
{
  FATFS FatFs;
  FIL fil;        /* File object */
  char *  line = "holyfuckifthisworks"; /* Line buffer */
  FRESULT fr;     /* FatFs return code */


  /* Register work area to the default drive */
  f_mount(&FatFs, "", 0);

  /* Open a text file */
  fr = f_open(&fil, filename, FA_WRITE | FA_CREATE_ALWAYS);
//  write_usb_serial_blocking("haha\r\n",6);
  if (fr) return (int)fr;
//  write_usb_serial_blocking("just test\r\n", 12);
  /* Read every line and display it */
  int length = 20;
//  write_usb_serial_blocking("haha\r\n",6);

  f_write(&fil, contents, len, &length);

//  write_usb_serial_blocking("yeet\r\n",6);

  f_sync(&fil);
  /* Close the file */
  f_close(&fil);
  return 0;

}

int mkdir_test(char * dir_name)
{
  FATFS FatFs;
  f_mount(&FatFs, "", 0);
  FRESULT res = f_mkdir(dir_name);
  if(res) return 1;
  return 0;
}

int main()
{
  serial_init();
  write_usb_serial_blocking("-----------------reset------------------\r\n",42);
  //write_usb_serial_blocking("file1\r\n", 7);
  //char buffer[256];
  FRESULT result;
//  scan_files("/");
//  if (result == FR_OK)
  //{
  write_usb_serial_blocking("before list files\r\n", 19);
  list_files();
  write_usb_serial_blocking("a\r\n", 3);
  list_files();
  write_usb_serial_blocking("b\r\n", 3);
  list_files();
  write_usb_serial_blocking("c\r\n", 3);
  list_files();
  write_usb_serial_blocking("d\r\n", 3);
  list_files();
  write_usb_serial_blocking("e\r\n", 3);
  list_files();
  write_usb_serial_blocking("after list files\r\n", 18);
  //test_opening("TestFile.txt");
  //test_write("pont.txt", "this was my test bois", sizeof("this was my test bois"));
  //test_opening();;
//  file_exists("wut.txt");

  write_usb_serial_blocking("-----------------end------------------\r\n",40);
  //result = scan_files(buffer);
  //}

  return result;
}
