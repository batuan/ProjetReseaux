#ifndef EXTREMITE__H
#define EXTREMITE__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "../util.h"
#include "../iftun/iftun.h"
#include "../tunalloc/tunalloc.h"

#define CLIENT 0
#define SERVER 1
#define PORT "123"

int extremite(char *tun_name, char *host, char *port, int mode);

#endif
