/* Linux fcntl syscall implementation.
   Copyright (C) 2000-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#include <fcntl.h>
#include <stdarg.h>
#include <errno.h>
#include <sysdep-cancel.h>
#include <not-cancel.h>

#ifndef __NR_fcntl64
# define __NR_fcntl64 __NR_fcntl
#endif

#ifndef FCNTL_ADJUST_CMD
# define FCNTL_ADJUST_CMD(__cmd) __cmd
#endif

int
__libc_fcntl (int fd, int cmd, ...)
{
  va_list ap;
  void *arg;

  va_start (ap, cmd);
  arg = va_arg (ap, void *);
  va_end (ap);

  cmd = FCNTL_ADJUST_CMD (cmd);

  if (cmd == F_SETLKW || cmd == F_SETLKW64)
    return SYSCALL_CANCEL (fcntl64, fd, cmd, (void *) arg);

  return __fcntl_nocancel_adjusted (fd, cmd, arg);
}
libc_hidden_def (__libc_fcntl)

weak_alias (__libc_fcntl, __fcntl)
libc_hidden_weak (__fcntl)
weak_alias (__libc_fcntl, fcntl)
