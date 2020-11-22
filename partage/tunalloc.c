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
  printf("Interface %s Configurée:\n \n",argv[1]);
  system("ip addr");

  printf("\n \n");

  if(tunfd < 0) {
    perror("tun_create");
    return 1;
  }
  printf("run configuration: \n");
  char command[50];
  int error = 0;
  sprintf(command, "sh configure-tun.sh %s", argv[1]);
  printf("command:  %s\n", command);
  error = system(command);
  if (error != 0) 
  {
    perror("error ");
    /* code */
  }
  int ret;
  unsigned char buf[4096] = {0};
  
  while(1) {
    unsigned char ip[4];
    ret = read(tunfd, buf, sizeof(buf));
    if (ret < 0) {
      printf("no read\n");
      break;
    }
    printf("read %d bytes\n", ret);
    for (int i = 0; i < ret; ++i)
    {
      printf("%x ", buf[i]);
    }
    
    memcpy(ip, &buf[12], 4);
    memcpy(&buf[12], &buf[16], 4); 
    memcpy(&buf[16], ip, 4);
    buf[20] = 0;
    *((unsigned short*)&buf[22]) += 8;
    ret = write(tunfd, buf, ret);
    printf("write %d bytes\n", ret);
  }

  printf("Appuyez sur une touche pour terminer\n");
  getchar();

  return 0;
}
