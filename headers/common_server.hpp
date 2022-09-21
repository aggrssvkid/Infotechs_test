#ifndef COMMON_SERVER_HPP
#define COMMON_SERVER_HPP

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#define BUFFSIZE 1001
#define DEFAULT_PORT 16555    // Указываем порт как 16555
#define MAXLINK 10            // максимальное кол-во соединений в очереди

void    print_msg(char *buf_ptr);

#endif