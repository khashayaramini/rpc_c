#include "functions.h"
#include "macros.h"
#include <cstring>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <sstream>
#include <iostream>
#define PORT 6666
#define BUFFER_SIZE 1024

std::vector<std::string> split (const std::string &s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss (s);
    std::string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

int main(int argc, char *argv[]){

    int server_fd, new_socket;
    ssize_t valread;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    if (bind(server_fd, (struct sockaddr*)&address,
             sizeof(address))
        < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket
         = accept(server_fd, (struct sockaddr*)&address,
                  &addrlen))
        < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int not_done = 1;
    while(not_done){
		char buffer[BUFFER_SIZE] = { 0 };
        valread = read(new_socket, buffer, BUFFER_SIZE);
        if(strcmp("end", buffer) == 0)
            not_done = 0;
		if(buffer[0] == 0)
			continue;
        printf("buffer is: %s\n", buffer);
        std::vector<std::string> v = split (buffer, ';');
        for(int i = 0; i < RPC_FUNC_ARRAY_SIZE; i++){
			auto the_func = func_array[i]; 
            if(strcmp(the_func.name, v[0].c_str()) == 0){
                std::cout << "name of func: " << func_array[i].name << std::endl;
                unsigned char arg[BUFFER_SIZE];
				memcpy(arg, buffer + v[0].size() + 1, BUFFER_SIZE - (v[0].size() + 1));
                unsigned char res[BUFFER_SIZE];
                the_func.fp((void *)&arg, (void *)&res);

				send(new_socket, res, BUFFER_SIZE, 0);
				
                memset(buffer, 0, BUFFER_SIZE);
                memset(res, 0, BUFFER_SIZE);
                memset(arg, 0, BUFFER_SIZE);
            }
        }
    }
    return 0;
}
