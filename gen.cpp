#include <iostream>
#include <fstream>
#include "functions.h"
#include "macros.h"
using namespace std;
const int function = 1;


int generateClientStub(string fileName){
    ofstream clientStub(fileName + ".h");
    clientStub << "#include <arpa/inet.h>\n"
                "#include <iostream>\n"
                "#include <sys/socket.h>\n"
                "#include <unistd.h>\n"
                "#include <string.h>\n using namespace std;\n#define BUFFER_SIZE 1024\n#define INPUT_SIZE 256\n";


    clientStub << "int createClientConn(char ip_addr[30], int port_num){\n"
    "\tstruct sockaddr_in server;\n"

    "\tint clientSocket = socket(AF_INET , SOCK_STREAM , 0);\n"
    "\tif (clientSocket == -1){\n"
    "\t\tcout<<\"Error in socket creation\" << endl;\n"
    "\t\treturn -1;\n"
    "\t}\n"
    "\tcout << \"Socket creation successful\" << endl;\n"

    "\tserver.sin_addr.s_addr = inet_addr(ip_addr);\n"
    "\tserver.sin_family = AF_INET;\n"
    "\tserver.sin_port = htons(port_num);\n"

    "\tif (connect(clientSocket, (struct sockaddr *)&server , sizeof(server)) < 0){\n"
    "\t\tcout << \"Socket connection failed\" << endl;\n"
    "\t\treturn -1;\n"
    "\t}\n"
    "\tcout << \"Socket connection successful\" << endl;\n"

    "\treturn clientSocket;\n"
    "}\n\n";
    
    for(int i = 0; i < RPC_FUNC_ARRAY_SIZE; i++){
        clientStub << "void " << func_array[i].name << " (void * my_struct, void *res, int clientSocket){\n"
        "\tint valread;\n"
        "\tchar buffer[BUFFER_SIZE] = { 0 };\n"
        "\tchar message[INPUT_SIZE];\n"
        "\tunsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(my_struct);\n"
		"\tstd::string func_name = \""<< func_array[i].name <<"\";\n"
		"\tstd::strcpy(message, func_name.c_str());\n"
		"\tmessage[func_name.length()] = ';';\n"
		"\tstd::memcpy(message + func_name.length() + 1, my_struct, INPUT_SIZE - func_name.length());\n"

        "\tsend(clientSocket, message, INPUT_SIZE, 0);\n"
        "\tvalread = read(clientSocket, buffer, BUFFER_SIZE - 1);\n"
        "}\n\n";

    }

    clientStub.close();
    return 1;
}



int main() {
    generateClientStub("client_stub");

    return 0;
}
