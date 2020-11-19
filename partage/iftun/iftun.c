#include "iftun.h"

int tun_write(int fd, char *buf, int len) {

}
int tun_read(int fd, char *buf, int len) {

}

void src2dst(int src, char* dst) {

}

int main (int argc, char** argv){
  int tunfd;
  printf("Création de %s\n",argv[1]);
  tunfd = tun_alloc(argv[1]);
  char command[50];
  int error = 0;
  sprintf(command, "sh ../test.sh %s", argv[1]);
  error = system(command);
  if(error!=0) {
    perror("config error");
    return 0;
  }

  int ret;
  unsigned char buf[256] = {0};
  while (1)
  {
    /* code */
    unsigned char ip[4];
    ret = read(tunfd, buf, sizeof(buf));
    if (ret < 0) break;
    buf = malloc(size);
  }
  

  return 0;
}