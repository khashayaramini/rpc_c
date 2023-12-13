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
#include "client_stub.h"
#define PORT 6666

int main(int argc, char **argv){
    int client_fd = createClientConn("127.0.0.1", PORT);

 
    nums mynums = (nums){.num1 = 5, .num2 = 6};
    int res = my_add(&mynums, client_fd);
    printf("result in main %d\n", res);
    sleep(6);
    test_struct_t my_struct = (test_struct_t){.i = 7, .j = 3.14, .name = {'y', 'o', 'l', 'o', '\0'}};
    float floatres = my_test1(&my_struct, client_fd);
    printf("result in main %f\n", floatres);
    return 0;
}
