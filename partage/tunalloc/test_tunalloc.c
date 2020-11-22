#include "tunalloc.h"

int main (int argc, char** argv){

  int tunfd;
  printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  printf("Faire la configuration de %s...\n",argv[1]);
  
  char command[50];
  int error = 0;
  sprintf(command, "sh ../configure-tun.sh %s", argv[1]);
  error = system(command);
  printf("my command %s\n", command);
  printf("Appuyez sur une touche pour continuer\n");
  getchar();
  printf("\n \n");
  printf("Interface %s Configurée:\n",argv[1]);
  system("ip addr");
  printf("\n \n");
  //char * dst = "./test_dst.txt";
  // char * dst = 1;
  //src2dst(tunfd, dst);
  int ret;
  unsigned char buf[4096] = {0};
  int i = 0;
  while(i < 5) {
    unsigned char ip[4];
    ret = read(tunfd, buf, sizeof(buf));
    if (ret < 0) break;
    printf("read %d bytes\n", ret);
    memcpy(ip, &buf[12], 4);
    memcpy(&buf[12], &buf[16], 4);
    memcpy(&buf[16], ip, 4);
    buf[20] = 0;
    *((unsigned short*)&buf[22]) += 8;
    ret = write(1, buf, ret);
    printf("write %d bytes\n", ret);
    i++;
  }

  printf("Appuyez sur une touche pour terminer\n");
  getchar();

  return 0;
}