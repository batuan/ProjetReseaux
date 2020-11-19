#include <stdlib.h>
#include <stdio.h>
#include <string.h> // strncpy
#include <stdarg.h> // getopt

#include "extremite.h"

int debug = 0;

void usage(char *prog_name)
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "%s -i <tun_interface_name> [-s|-c <server_ip_address>] [-p <port>] [-d]\n", prog_name);
	fprintf(stderr, "%s -h\n", prog_name);
	fprintf(stderr, "\n");
	fprintf(stderr, "\t-i <tun_interface_name> : name of interface to use (mandatory)\n");
	fprintf(stderr, "\t-s|-c <server_ip_address> : run in server mode (-s), or specify server address (-c <server_ip_address>) (mandatory)\n");
	fprintf(stderr, "\t-p <port> : port to listen on (if run in server mode) or to connect to (in client mode), default is 123\n");
	fprintf(stderr, "\t-h : prints this help text\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv) {
	// prog args
	char *prog_name = argv[0];
	int option;

	// tun interface
	char tun_name[IFNAMSIZ] = "\0";

	// extremite args
	char host[NI_MAXHOST] = "\0";
	char port[6]; strncpy(port, PORT, strlen(PORT));
	int mode = -1;

	while((option = getopt(argc, argv, "i:sc:p:h")) > 0) {
		switch(option) {
			case 'i':
				strncpy(tun_name, optarg, IFNAMSIZ);
				break;
			case 's':
				mode = SERVER;
				break;
			case 'c':
				mode = CLIENT;
				strncpy(host, optarg, NI_MAXHOST);
				break;
			case 'p':
				strncpy(port, optarg, 6);
				break;
			case 'h':
				usage(prog_name);
				break;
			default:
				fprintf(stderr, "Unknown option %c\n", option);
				usage(prog_name);
		}
	}

	argv += optind;
	argc -= optind;

	if(argc > 0) {
		fprintf(stderr, "Too many options !\n");
		usage(prog_name);
	}

	if(*tun_name == '\0') {
		fprintf(stderr, "You must specify tun interface name !\n");
		usage(prog_name);
	} else if(mode < 0) {
		fprintf(stderr, "You must specify the mode !\n");
		usage(prog_name);
	} else if((mode == CLIENT) && (*host == '\0')) {
		fprintf(stderr, "You must specify the server ip address !\n");
		usage(prog_name);
	}

	extremite(tun_name, host, port, mode);
	return EXIT_SUCCESS;
}
