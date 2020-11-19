#include "tunalloc.h"

int tun_alloc(char *tun_name)
{
	struct ifreq ifr;
	int fd, err;

	msg_start_func(__func__);

	if((fd = open("/dev/net/tun", O_RDWR)) < 0) {
		msg_error("opening /dev/net/tun\n");
		msg_end_func(__func__);
		return fd;
	}

	memset(&ifr, 0, sizeof(ifr));

	/* Flags:
	*	IFF_TUN   - TUN device (no Ethernet headers)
	*   IFF_TAP   - TAP device
	*
	*	IFF_NO_PI - Do not provide packet information
	*/
	ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
	
	if(*tun_name)
		strncpy(ifr.ifr_name, tun_name, IFNAMSIZ);

	if((err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0) {
		close(fd);
		msg_error("ioctl\n");
		msg_end_func(__func__);
		return err;
	}

	strcpy(tun_name, ifr.ifr_name);

	/* Configuration de tunX via le fichier configure-tun.sh */
	char command[100];
	sprintf(command, "../configure-tun.sh %s", tun_name);
	system(command);
	sprintf(command, "Interface %s configurée !\n", tun_name);
	msg_info(command);

	sprintf(command, "Opened interface %s on file descriptor %d\n", tun_name, fd);
	msg_info(command);
	msg_end_func(__func__);
	return fd;
}