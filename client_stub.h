#include <arpa/inet.h>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
 using namespace std;
#define BUFFER_SIZE 1024
#define INPUT_SIZE 256
int createClientConn(char ip_addr[30], int port_num){
	struct sockaddr_in server;
	int clientSocket = socket(AF_INET , SOCK_STREAM , 0);
	if (clientSocket == -1){
		cout<<"Error in socket creation" << endl;
		return -1;
	}
	cout << "Socket creation successful" << endl;
	server.sin_addr.s_addr = inet_addr(ip_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(port_num);
	if (connect(clientSocket, (struct sockaddr *)&server , sizeof(server)) < 0){
		cout << "Socket connection failed" << endl;
		return -1;
	}
	cout << "Socket connection successful" << endl;
	return clientSocket;
}

double my_test1 (void * my_struct, void *res, int clientSocket){
	int valread;
	char buffer[BUFFER_SIZE] = { 0 };
	char message[INPUT_SIZE];
	unsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(my_struct);
	std::string func_name = "my_test1";
	std::strcpy(message, func_name.c_str());
	message[func_name.length()] = ';';
	std::memcpy(message + func_name.length() + 1, my_struct, INPUT_SIZE - func_name.length());
	send(clientSocket, message, INPUT_SIZE, 0);
	valread = read(clientSocket, buffer, BUFFER_SIZE - 1);
	return *reinterpret_cast<double*>(buffer);
}

int my_add (void * my_struct, void *res, int clientSocket){
	int valread;
	char buffer[BUFFER_SIZE] = { NULL };
	char message[INPUT_SIZE];
	unsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(my_struct);
	std::string func_name = "my_add";
	std::strcpy(message, func_name.c_str());
	message[func_name.length()] = ';';
	std::memcpy(message + func_name.length() + 1, my_struct, INPUT_SIZE - func_name.length());
	send(clientSocket, message, INPUT_SIZE, 0);
	valread = read(clientSocket, buffer, BUFFER_SIZE - 1);
	if(buffer[0] == NULL)
		valread = read(clientSocket, buffer, BUFFER_SIZE - 1);
	return *reinterpret_cast<int*>(buffer);
}

int my_sub (void * my_struct, void *res, int clientSocket){
	int valread;
	char buffer[BUFFER_SIZE] = { 0 };
	char message[INPUT_SIZE];
	unsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(my_struct);
	std::string func_name = "my_sub";
	std::strcpy(message, func_name.c_str());
	message[func_name.length()] = ';';
	std::memcpy(message + func_name.length() + 1, my_struct, INPUT_SIZE - func_name.length());
	send(clientSocket, message, INPUT_SIZE, 0);
	valread = read(clientSocket, buffer, BUFFER_SIZE - 1);
	return *reinterpret_cast<int*>(buffer);
}

