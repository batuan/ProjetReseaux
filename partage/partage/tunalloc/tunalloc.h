#ifndef TUNALLOC__H
#define TUNALLOC__H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>			// strncpy, memset
#include <sys/socket.h>		// ifru_* for ih.h
#include <sys/ioctl.h>		// ioctl
#include <unistd.h>			// close
#include <fcntl.h>			// O_RDWR
#include <linux/if.h>		// struct ifreq, IFNAMSIZ
#include <linux/if_tun.h>	// IFF_TUN, IFF_NO_PI, TUNSETIFF

#include "../util.h"

int tun_alloc(char *dev);

#endif
