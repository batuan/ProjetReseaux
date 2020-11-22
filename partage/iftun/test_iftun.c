#include "iftun.h"

int main (int argc, char** argv){
  int tunfd;
  //printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  char command[50];
  int error = 0;
  sprintf(command, "sh ../configure-tun.sh %s", argv[1]);
  error = system(command);
  //printf("my command in test_iftun %s\n", command);
  //char * dst = "./test_dst.txt";
  char * dst = argv[2];
  src2dst(tunfd, dst);
  int ret;
  unsigned char buf[256] = {0};
  return 0;
}