// amelia/user/stdio.h
// PURPOSE: Define lib for user IO utilities.
//
// DESCRIPTION:
//  This file implements (using syscalls defined in kernel) API to allow user
//  processes to access low level functionalities for input output.

#ifndef _AMELIA_USER_STDIO_H
#define _AMELIA_USER_STDIO_H

#include <amelia/basic_types.h>

// Write a buffer to output (default miniuart). Right now it is not possible
// to pass params.
void write(char *buffer);

// Read from miniuart interface.
byte read();

#endif // _AMELIA_USER_STDIO_H
