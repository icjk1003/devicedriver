#include <stdio.h>
#include <fcntl.h> // open()
#include <unistd.h> // write() read()..
#include <stdlib.h> // exit()
#include <string.h> // strlen()

#define MAJOR_DEV_FILE_NAME "/dev/major_dev"

char *msg = "USER DATA";

int main(int argc, char** argv)
{
	int fd;
	char buf[1024];

	fd = open(MAJOR_DEV_FILE_NAME, O_RDWR);

	if(fd < 0)
	{
		printf(MAJOR_DEV_FILE_NAME " open error\n");

		exit(1);
	}

	read(fd, buf, 0);
	printf("read data: %s\n", buf);

	write(fd, msg, strlen(msg)+1);

	close(fd);

	return 0;
}
