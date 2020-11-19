#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h> 
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

#include "iftun.h"
#include "../tunalloc/tunalloc.h"
#include "../util.h"

int main(int argc, char **argv)
{
	if(argc < 3) {
		fprintf(stderr, "Usage : %s [tun_name] [dst]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	msg_start_func("main_test_iftun");
	
	char tun_name[IFNAMSIZ];
	strcpy(tun_name, argv[1]);

	int src = tun_alloc(tun_name);
	if(src < 0) {
		msg_error("allocating interface");
		exit(EXIT_FAILURE);
	}
	
	int dst = atoi(argv[2]);
	src_to_dst(src, dst);

	msg_end_func("main_test_iftun");
	return EXIT_SUCCESS;
}
