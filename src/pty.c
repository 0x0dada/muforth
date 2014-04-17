/*
 * This file is part of muFORTH: http://muforth.nimblemachines.com/
 *
 * Copyright (c) 2002-2014 David Frech. All rights reserved, and all wrongs
 * reversed. (See the file COPYRIGHT for details.)
 */

/* Quick and dirty pty - pseudo-tty - support */

#include "muforth.h"

#include <stdlib.h>
#include <fcntl.h>

void mu_open_pty()      /* ( - fd z") leaves pathname of slave */
{
    int fd;         /* fd of master */
    char *slave;    /* name of corresponding slave device */

    fd = posix_openpt(O_RDWR);
    if (fd == -1)
        return abort_strerror();
    if (grantpt(fd) == -1)
        return abort_strerror();
    if (unlockpt(fd) == -1)
        return abort_strerror();
    slave = ptsname(fd);
    if (slave == NULL)
        return abort_strerror();

    PUSH(fd);
    PUSH_ADDR(slave);
}
