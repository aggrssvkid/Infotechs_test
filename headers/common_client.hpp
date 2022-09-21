#ifndef COMMON_CLIENT_HPP
#define COMMON_CLIENT_HPP

#include <cstring>
#include <thread>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define LIMIT 64       // максимальное кол-во символов,вводимое пользователем
#define SERVER_IP "127.0.0.1" // Ip-адрес, localhost (сервер будет на нашем компуктере)
#define SERVER_PORT 16555   // порт для соединения
#define BUFF_SIZE 1001

int         is_line_correct(std::string msg);
void        change_msg(std::string &msg);
void        get_msg_sum(char *buff_ptr);

#endif