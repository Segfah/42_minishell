#include "ft_pf.h"
int     ft_fprintf(int fd, const char *format, ...)
{
    va_list arg;
    int     done;

    va_start(arg, format);
    done = ft_vprintf(fd, format, arg);
    va_end(arg);
    return (done);
}
