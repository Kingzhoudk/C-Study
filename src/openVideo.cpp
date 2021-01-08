#include<fcntl.h>
#include<unistd.h>
#include<iostream>

int main()
{
    int fd=open("/dev/video1",O_RDWR);  //open device
    sleep(5);
    printf("%d\n",fd);
    close(fd);
}
