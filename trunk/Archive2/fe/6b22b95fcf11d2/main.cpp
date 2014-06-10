#include <errno.h>
#include <stdarg.h>
#include <sys/ioctl.h>

const int kvm_fd = 2;

int kvm_ioctl(int type, ...)
{
int ret;
void *arg;
va_list ap;

va_start(ap, type);
arg = va_arg(ap, void *);
va_end(ap);

ret = ioctl(kvm_fd, type, arg);
if (ret == -1)
    ret = -errno;

return ret;
}

int main() {
    kvm_ioctl(0, 0, 0, 0);
}