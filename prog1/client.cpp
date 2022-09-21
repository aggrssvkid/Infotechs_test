#include "../headers/common_client.hpp"

static char buff_between_threads[BUFF_SIZE]; // буфер для обмена инфой между потоками

void    thread_1(std::mutex &mx) {
    const char  *str; // указатель для записи данных в буфер обмена инфой между потоками
    std::string msg; // сюда запишем данные, введенные с консольки
    
    while (true) {
        std::cout<<"Please enter the line!"<<std::endl;
        // лочим мьютекс и дальше идем по нашему коду. Если он уже залочен другим потоком, то ждемс
        mx.lock();
        // далее считываем данные с консоли, пока не будут введены корректные данные
        while (getline(std::cin, msg)) {
            if (is_line_correct(msg) == 1)
                break;
            std::cout<<"GO again! Your line incorrect!"<<std::endl;
        }
        // обрабатываем ошибки ввода
        if (std::cin.bad()) {
            std::cout<<"Input error! You can restart prog."<<std::endl;
            exit(0);
        }
        else if (std::cin.eof()) {
            std::cout<<"EOF, my friend! Goodbuy! Just restart prog."<<std::endl;
            exit(0);
        }
        // делаем что-то с введенными данными, как указано в задании
        change_msg(std::ref(msg));
        str = msg.c_str();
        strcpy(buff_between_threads, str);
        // С чувством выполненного долга, освобождаем мьютекс для потока №2
        mx.unlock();
        // и небольшую задержечку, чтобы поток №2 первым взял мьютекс!
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    struct sockaddr_in  servaddr; // структурка в которой хранятся данные сети
    int                 sockfd;   // сокет для связи с сервером и обмена информацией 
    char                buff_between_progs[BUFF_SIZE]; // буфер для обмена информацией между прогами

    // далее инициализируем нашу структурку...
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET, SERVER_IP, &servaddr.sin_addr);
    servaddr.sin_port = htons(SERVER_PORT);

    // мьютекс для синхронизации между потоками. 
    // Пока один поток им владеет, другой может только ждать...
    std::mutex mx;
    // создаем 1-й поток для обмена данных с юзернеймом
    // передаю его по ссылке, так что это не глобальная переменная!
    std::thread t(thread_1, std::ref(mx));
    t.detach(); //отрубаем его от main-потока, чтобы каждый поток делал свое дело

    // небольшая задержка, чтобы поток 1 успел первым до мьютекса
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    while (true) {
        mx.lock();
        std::cout<<"I am thread №2! I'v got this datas:"<<std::endl;
        std::cout<<buff_between_threads<<std::endl;
        /*
        далее готовим полученные данные с консоли для доставки их серверу!
        сперва, копируем данные в буфер для обмена инфой между программами
        затем, зачищаем буфер, в который мы записали данные с консоли
        */
        strcpy(buff_between_progs, buff_between_threads);
        bzero(buff_between_threads, sizeof(buff_between_threads));
        // создаем сокет для соеденения с сервером
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if(sockfd == -1) {
            std::cout<<"Sorry, socket was not created! Try again"<<std::endl;
        }
        // коннектимся к серверу
        else if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1) {
            std::cout<<"Connect error! You can try again!"<<std::endl;
        }
        // если ошибок при коннекте и создания сокета не возникло, то отправляем смс
        else {
            get_msg_sum(&buff_between_progs[0]);
            send(sockfd, buff_between_progs, strlen(buff_between_progs), 0);
        }
        // чистим буфер
        bzero(buff_between_progs, sizeof(buff_between_progs));
        if (sockfd != -1)
            close(sockfd);
        mx.unlock();
        //хрр...(немножечко поспали для более надежной синхронизации)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}