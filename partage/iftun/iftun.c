#include "iftun.h"
int tun_write(int fd, char *buf, int len) {

}
int tun_read(int fd, char *buf, int len) {

}

void src2dst(int src, char* dst) {
  printf("in src2dst");
  FILE *fp; 
  fp = fopen(dst, "w");
  int ret;
  unsigned char buf[4096] = {0};
  int i = 0;
  while(i < 1) {
    unsigned char ip[4];
    ret = read(src, buf, sizeof(buf));
    if (ret < 0) {
      printf("error ");
      break;
    }
    
    if(dst==NULL) write(1, buf, ret);
    else
    {
      printf("read %d bytes\n", ret);
      for(int i = 0; i<ret; i++){
        fputc(buf[i], fp);
      }
    }
    i++;
  }
  printf("Completed write to file");
  fclose(fp);
  // memcpy(ip, &buf[12], 4);
  //   memcpy(&buf[12], &buf[16], 4);
  //   memcpy(&buf[16], ip, 4);
  //   buf[20] = 0;
  //   *((unsigned short*)&buf[22]) += 8;
  //   ret = write(tunfd, buf, ret);
  //   printf("write %d bytes\n", ret);
}