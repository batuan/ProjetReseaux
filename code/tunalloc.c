
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
#include "tunalloc.h"

int tun_alloc(char *dev)
{
  struct ifreq ifr;
  int fd, err;

  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(-1);
  }

  memset(&ifr, 0, sizeof(ifr));

  /* Flags: IFF_TUN   - TUN device (no Ethernet headers) 
   *        IFF_TAP   - TAP device  
   *
   *        IFF_NO_PI - Do not provide packet information  
   */ 
  ifr.ifr_flags = IFF_TUN; 
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}      

int main (int argc, char** argv){

  int tunfd;
  printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  printf("Faire la configuration de %s...\n",argv[1]);
  printf("Faire la configuration de %d...\n",tunfd);
  printf("Appuyez sur une touche pour continuer\n");
  getchar();
  printf("Interface %s Configurée:\n",argv[1]);
  system("ip addr");

  if(tunfd < 0) {
    perror("tun_create");
    return 1
  }
  int ret;
  while(1) {
    unsigned char ip[4];
 
    ret = read(tun, buf, sizeof(buf));
    if (ret < 0) break;
    printf("read %d bytes\n", ret);
    memcpy(ip, &buf[12], 4);
    memcpy(&buf[12], &buf[16], 4);
    memcpy(&buf[16], ip, 4);
    buf[20] = 0;
    *((unsigned short*)&buf[22]) += 8;
    ret = write(tun, buf, ret);
    printf("write %d bytes\n", ret);
  }

  printf("Appuyez sur une touche pour terminer\n");
  getchar();

  return 0;
}
