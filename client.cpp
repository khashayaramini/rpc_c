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
    char buffer[BUFFER_SIZE] = { 0 };
    int client_fd = createClientConn("127.0.0.1", PORT);

    char message[INPUT_SIZE];
    int e = 2;
    // test_struct_t my_struct = (test_struct_t){.i = 7, .j = 3.14, .name = {'y', 'o', 'l', 'o', '\0'}};
    nums mynums = (nums){.num1 = 5, .num2 = 6};
    int res;
    res = my_add(&mynums, buffer, client_fd);
    printf("result in main %d\n", res);
    mynums.num1 = 7;
    sleep(3);
	memset(buffer, 0, BUFFER_SIZE);
    printf("new val :%d\n", mynums.num1);
    res = my_add(&mynums, buffer, client_fd);
    printf("result in main %d\n", res);
    

    return 0;
}
