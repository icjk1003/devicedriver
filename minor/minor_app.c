#include <stdio.h>
#include <fcntl.h>    // open()
#include <unisdt.h>   // write() read() ..
#include <stdlib.h>   // exit()
#include <string.h>   // strlen()
#define READ_DEVICE_FILE_NAME  "/dev/read_dev"
#define WRITE_DEVICE_FILE_NAME "/dev/write_dev"

char *msg = "USER DATA"

int main()
{
   int read_dev;
   int write_dev;
   
   char buf[1024];
   
   read_dev = open(READ_DEVICE_FILE_NAME, O_RDWR);
   
   if(read_dev < 0)
   {
      printf("READ_DEVICE_FILE_NAME " open error\n");
      exit(1);
   }
   
   write_dev = open(WRITE_DEVICE_FILE_NAME, O_RDWR);
   
   if(write_dev < 0)
   {
      printf("WRITE_DEVICE_FILE_NAME " open error\n");
      close(read_dev);
      exit(1);
   }
   
   read(read_dev, buf, 0);
   printf("read data: %s\n", buf);
   
   write(write_dev, msg, strlen(msg)+1);
   
   close(read_dev);
   close(write_dev);
   
   return 0;
}
