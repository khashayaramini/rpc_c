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
int main(int argc, char **argv){
    int status, valread, client_fd;
    struct sockaddr_in serv_addr;
    std::string end_message_string = "end"; // num of args, args, func name
    const char* end_message = end_message_string.c_str();
    char buffer[BUFFER_SIZE] = { 0 };
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }
 
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
 
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)
        <= 0) {
        printf(
            "\nInvalid address/ Address not supported \n");
        return -1;
    }
 
    if ((status
         = connect(client_fd, (struct sockaddr*)&serv_addr,
                   sizeof(serv_addr)))
        < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }

    int not_done = 1;
    while(not_done){
        std::cout << "Available remote functions:" << std::endl;
        for(int i = 0; i < RPC_FUNC_ARRAY_SIZE; i++){
            std::cout << func_array[i].name << std::endl;
        }
        char message[INPUT_SIZE];
		int e = 2;
		test_struct_t my_struct = (test_struct_t){.i = 7, .j = 3.14, .name = {'y', 'o', 'l', 'o', '\0'}};
		unsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(&my_struct);
		std::string func_name = "my_test1";
		std::strcpy(message, func_name.c_str());
		message[func_name.length()] = ';';
		std::memcpy(message + func_name.length() + 1, &my_struct, sizeof(my_struct));

        send(client_fd, message, INPUT_SIZE, 0);
        valread = read(client_fd, buffer, BUFFER_SIZE - 1);
        memset(buffer, 0, BUFFER_SIZE);
        if(strcmp(message, "end") == 0)
            return 0;
    }
}
