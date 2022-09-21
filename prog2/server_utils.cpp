#include "../headers/common_server.hpp"

void    print_msg(char *buf_ptr) {
    if (strlen(buf_ptr) < 3) {
        std::cout<<"Error! Size of number is lower then 3"<<std::endl;
        return ;
    }
    if (atoi(buf_ptr) % 32 != 0) {
        std::cout<<"Error! The number is not divisible by 32"<<std::endl;
        return ;
    }
    std::cout<<"Datas correct!"<<std::endl;
    std::cout<<buf_ptr<<std::endl;

}