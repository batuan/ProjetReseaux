#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strcmp
#include <sys/ioctl.h> // TUNSETPERSIST
#include <linux/if_tun.h> // TUNSETPERSIST

#include "tunalloc.h"
#include "../util.h"

int main(int argc, char** argv) {
	if(argc < 3 || (strcmp(argv[2], "np") && strcmp(argv[2], "p") && strcmp(argv[2], "del"))) {
		fprintf(stderr, "Usage : %s [tun_name] [np (non persistant) | p (persistant) | del (delete)]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	msg_start_func("main_test_tunalloc");
	
	if( ! strcmp(argv[2], "del")) {
		int tunfd = tun_alloc(argv[1]);
		if(tunfd < 0) {
			msg_end_func("main_test_tunalloc");
			exit(EXIT_FAILURE);
		}

		if(ioctl(tunfd, TUNSETPERSIST, 0) < 0) {
			msg_error("ioctl");
			msg_end_func("main_test_tunalloc");
			exit(EXIT_FAILURE);
		}
		printf("Interface %s supprimée\n", argv[1]);
	}
	
	else {
		int tunfd = tun_alloc(argv[1]);
		if(tunfd < 0) {
			msg_end_func("main_test_tunalloc");
			exit(EXIT_FAILURE);
		}
		
		if( ! strcmp(argv[2], "p")) {
			if(ioctl(tunfd, TUNSETPERSIST, 1) < 0) {
				msg_error("ioctl");
				msg_end_func("main_test_tunalloc");
				exit(EXIT_FAILURE);
			}
			printf("Interface %s créée de manière persistante\n", argv[1]);
		}
		
		else if( ! strcmp(argv[2], "np")) {
			if(ioctl(tunfd, TUNSETPERSIST, 0) < 0) {
				msg_error("ioctl");
				msg_end_func("main_test_tunalloc");
				exit(EXIT_FAILURE);
			}
			printf("Interface %s créée de manière non-persistante\n", argv[1]);
		}
		//system("ip addr");
	}

	msg_end_func("main_test_tunalloc");
	return 0;
}