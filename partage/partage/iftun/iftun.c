#include "iftun.h"

char msg_buffer[BUFFER_SIZE];

int read_util(int fd, char *buf, int count)
{
    int read_rv;
    if((read_rv = read(fd, buf, count)) < 0) {
        sprintf(msg_buffer, "Read data from fd %d\n", fd);
		msg_error(msg_buffer);
		close(fd);
    } else if(read_rv == 0) {
		sprintf(msg_buffer, "Read data from fd %d (the other part stopped)\n", fd);
		msg_info(msg_buffer);
		close(fd);
	} else {
		sprintf(msg_buffer, "Read %d bytes from fd %d\n", read_rv, fd);
		msg_info(msg_buffer);
	}
	return read_rv;
}

int write_util(int fd, char *buf, int count)
{
    int write_rv;
    if((write_rv = write(fd, buf, count)) < 0) {
        sprintf(msg_buffer, "Write data to fd %d\n", fd);
		msg_error(msg_buffer);
		close(fd);
    } else if(write_rv == 0) {
		sprintf(msg_buffer, "Write data to fd %d (the other part stopped)\n", fd);
		msg_info(msg_buffer);
		close(fd);		
	} else {
		sprintf(msg_buffer, "Written %d bytes to fd %d\n", write_rv, fd);
		msg_info(msg_buffer);
	}
	return write_rv;
}

int src_to_dst(int src, int dst)
{
	msg_start_func(__func__);

	char buffer[BUFFER_SIZE];
	int read_rv, write_rv;

	// read data from @src fd
	if((read_rv = read_util(src, buffer, BUFFER_SIZE)) <= 0) {
		msg_end_func(__func__);
		return read_rv;
	}

	// write data to @dst fd
	if((write_rv = write_util(dst, buffer, read_rv)) <= 0) {
		msg_end_func(__func__);
		return write_rv;
	}

	msg_end_func(__func__);
	return EXIT_SUCCESS;
}
