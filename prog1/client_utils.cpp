#include "../headers/common_client.hpp"

// проверяем данные на корректность
int is_line_correct(std::string msg) {
    if (LIMIT < msg.size() || msg.size() == 0)
        return (0);
    int i = 0;
    int k;

    while (i < msg.size() && (k = isdigit(msg[i])) != 0)
        i++;
    if (k == 0)
        return (0);
    return (1);
}

//изменяем данные, введенные пользователем с помощью change_msg()
void   change_msg(std::string &msg) {
    std::string::iterator iter;
    int k;

    std::sort(msg.begin(), msg.end(), std::greater <char>());
    iter = msg.begin();
    while (iter != msg.end()) {
        if ((*iter - '0') % 2 == 0) {
            *iter = 'B';
            iter = msg.insert(iter, 'K');
            iter += 2;
        }
        else
            iter++;
    }
}

// находим искомую сумму цифр
void    get_msg_sum(char *buff_ptr) {
    char        *help_ptr;
    std::string nbr;
    int         sum = 0;

    help_ptr = buff_ptr;
    while (*help_ptr != '\0') {
        if (isdigit(*help_ptr) != 0)
            sum += *help_ptr - '0';
        help_ptr++;
    }
    nbr = std::to_string(sum);
    help_ptr = (char *) nbr.c_str();
    strcpy(buff_ptr, help_ptr);
}