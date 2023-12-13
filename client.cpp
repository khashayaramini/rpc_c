#include "functions.h"
#include "macros.h"
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <iostream>
#define PORT 6666
#define BUFFER_SIZE 1024
#define INPUT_SIZE 256
#include "client_stub.h"
int main(int argc, char **argv){
    int status, valread;
    struct sockaddr_in serv_addr;
    std::string end_message_string = "end"; // num of args, args, func name
    const char* end_message = end_message_string.c_str();
    char buffer[BUFFER_SIZE] = { 0 };
    int client_fd = createClientConn("127.0.0.1", PORT);

    /* std::cout << "Available remote functions:" << std::endl;
    for(int i = 0; i < RPC_FUNC_ARRAY_SIZE; i++){
        std::cout << func_array[i].name << std::endl;
    } */
    char message[INPUT_SIZE];
    int e = 2;
    test_struct_t my_struct = (test_struct_t){.i = 7, .j = 3.14, .name = {'y', 'o', 'l', 'o', '\0'}};
    nums mynums = (nums){.num1 = 5, .num2 = 6};
    int res;
    //my_test1(&my_struct, buffer, client_fd);
    my_add(&mynums, buffer, client_fd);
    printf("result in main %d\n", *reinterpret_cast<int*>(buffer));

    /* unsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(&my_struct);
    std::string func_name = "my_test1";
    std::strcpy(message, func_name.c_str());
    message[func_name.length()] = ';';
    std::memcpy(message + func_name.length() + 1, &my_struct, sizeof(my_struct));

    send(client_fd, message, INPUT_SIZE, 0);
    valread = read(client_fd, buffer, BUFFER_SIZE - 1);
    printf("%d\n", *reinterpret_cast<int*>(buffer));
    memset(buffer, 0, BUFFER_SIZE); */
    // if(strcmp(message, "end") == 0)
        return 0;
}