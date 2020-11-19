#include "util.h"

int indent_trace = 0;
int indent_size = 4;

void msg_error(const char *msg)
{
    for(int i = 0; i < indent_trace; i++) {
        fprintf(stderr, " ");
    }
	fprintf(stderr, "!!! ERROR !!! ");
	fprintf(stderr, msg);
}

void msg_info(const char *msg)
{
    for(int i = 0; i < indent_trace; i++) {
        printf(" ");
    }
	printf("%s", msg);
}

void msg_start_func(const char *funcname)
{
    for(int i = 0; i < indent_trace; i++) {
        printf(" ");
    }
	printf("========== [%s] ==========\n", funcname);
    indent_trace += indent_size;
}

void msg_end_func(const char *funcname)
{
    indent_trace -= indent_size;
    for(int i = 0; i < indent_trace; i++) {
        printf(" ");
    }
	printf("========== [%s] ==========\n", funcname);
}
/*
ssize_t read_util(int fd, void *buf, size_t count)
{
    ssize_t r = read(fd, buf, count);

    if (r < 0) {
        perror(__func__);
    }
    else if (r == 0 && count != 0)
        fprintf(stderr, "[%s] : EOF detected for fd %d\n", __func__, fd);
    return r;
}

ssize_t read_str(int fd, char *buf, size_t count)
{
    if (count == 0) {
        fprintf(stderr, "%s: count>0 expected\n", __func__);
        //errno = EINVAL;
        return -1;
    }
    ssize_t r = read_util(fd, buf, count-1);
    if (r >= 0) buf[r] = '\0';
    return r;
}

ssize_t write_util(int fd, const void *buf, size_t count)
{
    ssize_t r = write(fd, buf, count);
    if (r < 0) perror(__func__);
    return r;
}

ssize_t write_str(int fd, const char *buf)
{
    return write_util(fd, buf, strlen(buf));
}
*/