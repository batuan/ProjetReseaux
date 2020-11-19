#ifndef UTIL_H
#define UTIL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 8192

void msg_error(const char *msg);
void msg_info(const char *msg);
void msg_start_func(const char *funcname);
void msg_end_func(const char *funcname);

#endif