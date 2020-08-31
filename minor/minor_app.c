#include <stdio.h>
#include <fcntl.h>    // open()
#include <unistd.h>   // write() read() ..
#include <stdlib.h>   // exit()
#include <string.h>   // strlen()

#define MINOR1_DEV_FILE_NAME  "/dev/minor1_dev"
#define MINOR2_DEV_FILE_NAME  "/dev/minor2_dev"

char *msg = "USER DATA";

int main(int argc, char **argv)
{
   int minor1_fd;
   int minor2_fd;

   char buf[1024];

   minor1_fd = open(MINOR1_DEV_FILE_NAME, O_RDWR);

   if(minor1_fd < 0)
   {
      printf(MINOR1_DEV_FILE_NAME " open error\n");

      exit(1);
   }

   minor2_fd = open(MINOR2_DEV_FILE_NAME, O_RDWR);

   if(minor2_fd < 0)
   {
      printf(MINOR2_DEV_FILE_NAME " open error\n");

      close(minor1_fd);

      exit(1);
   }

   read(minor1_fd, buf, 20);
   printf("read data: %s\n", buf);


   write(minor2_fd, msg, strlen(msg)+1);

   close(minor1_fd);
   close(minor2_fd);

   return 0;
}
