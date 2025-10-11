/*
 * syscalls.c
 *
 *  Created on: Sep 25, 2025
 *      Author: user
 */


/**
 * @file syscalls.c
 * @brief Stubs for system calls used by the C library.
 */

#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/times.h>

// Make sure errno is defined
#undef errno
extern int errno;

// List of functions to be stubbed with minimal implementation
int _close(int file) {
    return -1;
}

int _fstat(int file, struct stat *st) {
    st->st_mode = S_IFCHR;
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

/*
 * This is the most important function. It's used by printf(), puts(), etc.
 * To make printf() work, you need to redirect the output to a UART, ITM, etc.
 *
 * For example, to redirect to UART1:
 *
 * extern UART_HandleTypeDef huart1; // In main.c
 * int _write(int file, char *ptr, int len) {
 * HAL_UART_Transmit(&huart1, (uint8_t*)ptr, len, HAL_MAX_DELAY);
 * return len;
 * }
 */
int _write(int file, char *ptr, int len) {
    // By default, do nothing.
    return len;
}

int _getpid(void) {
    return 1;
}

int _kill(int pid, int sig) {
    errno = EINVAL;
    return -1;
}

