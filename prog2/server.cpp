#include "../headers/common_server.hpp"

int sockfd, connfd;    // Определение серверного и клиентского сокетов


// если ctrl+c, то закрываем сервак
void stop_server(int p)
{
    close(sockfd);
    std::cout<<std::endl<<"Close server"<<std::endl;
    exit(0);
}

int main()
{
    struct sockaddr_in  servaddr; // структурка в которой хранятся данные сети
    char                buff[BUFFSIZE]; // буфер для обмена информацией

    bzero(buff, BUFFSIZE);

    // создаем сокет
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd) {
        std::cout<<"Create socket error!"<<std::endl;
        exit(-1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(DEFAULT_PORT);

    // привязываем ip и порт к сокету
    if (-1 == bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) {
        std::cout<<"Bind error!"<<std::endl;
        exit(-1);
    }
    // слушаем и ожидаем запросы связи на данном порту
    if (-1 == listen(sockfd, MAXLINK)) {
        std::cout<<"Listen error!"<<std::endl;
        exit(-1);
    }
    std::cout<<"Listening on port: 16555..."<<std::endl;
    while (true)
    {
        signal(SIGINT, stop_server);

        // ожидаем запрос на связь. Если приняли запрос, то создаем новый сокет для
        // общения между клиентом и сервером
        connfd = accept(sockfd, NULL, NULL);
        if (connfd == -1) {
            std::cout<<"Cant accept! Error! Try again!" <<std::endl;
        }
        // записываем полученные данные в буфер
        recv(connfd, buff, BUFFSIZE - 1, 0);
        // обрабатываем данные
        print_msg(&buff[0]);
        // подчищаем за собой
        bzero(buff, BUFFSIZE);
        // закрываем сокет, иначе бо-бо
        close(connfd);
    }
    return 0;
}