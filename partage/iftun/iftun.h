#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include "../tunalloc/tunalloc.h"

void src2dst(int src, char* dst);
int tun_write(int fd, char *buf, int len);
int tun_read(int fd, char *buf, int len);