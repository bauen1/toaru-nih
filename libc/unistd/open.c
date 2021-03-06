#include <unistd.h>
#include <fcntl.h>
#include <va_list.h>
#include <errno.h>

#include <syscall.h>

DEFN_SYSCALL3(open,  2, const char *, int, int);

int open(const char *name, int flags, ...) {
	va_list argp;
	int mode = 0;
	int result;
	va_start(argp, flags);
	if (flags & O_CREAT) mode = va_arg(argp, int);
	va_end(argp);

	result = syscall_open(name, flags, mode);
	if (result == -1) {
		if (flags & O_CREAT) {
			errno = EACCES;
		} else {
			errno = ENOENT;
		}
	} else if (result < 0) {
		errno = -result;
	}
	return result;
}

