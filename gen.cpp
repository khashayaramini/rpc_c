#include <iostream>
#include <fstream>
#include "functions.h"
#include "macros.h"
using namespace std;
const int function = 1;


void generateClientStub(string fileName){
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
        clientStub << func_array[i].type << " " << func_array[i].name << " (void * my_struct, int clientSocket){\n"
        "\tchar buffer[BUFFER_SIZE] = { NULL };\n"
        "\tchar message[INPUT_SIZE];\n"
        "\tunsigned char* my_s_bytes = reinterpret_cast<unsigned char*>(my_struct);\n"
		"\tstd::string func_name = \""<< func_array[i].name <<"\";\n"
		"\tstd::strcpy(message, func_name.c_str());\n"
		"\tmessage[func_name.length()] = ';';\n"
		"\tstd::memcpy(message + func_name.length() + 1, my_struct, INPUT_SIZE - func_name.length());\n"

        "\tsend(clientSocket, message, INPUT_SIZE, 0);\n"
        "\tread(clientSocket, buffer, BUFFER_SIZE - 1);\n"
        "\tif(buffer[0] == NULL)\n"
		"\t\tread(clientSocket, buffer, BUFFER_SIZE - 1);\n"
        "\treturn *reinterpret_cast<" << func_array[i].type << "*>(buffer);\n" 
        "}\n\n";

    }

    clientStub.close();
}

void generateServerStub(string fileName) {
    ofstream serverStub(fileName + ".cpp");
    serverStub << "#include \"functions.h\"\n"
    "#include \"macros.h\"\n"
    "#include <cstring>\n"
    "#include <string>\n"
    "#include <sys/socket.h>\n"
    "#include <netinet/in.h>\n"
    "#include <stdio.h>\n"
    "#include <stdlib.h>\n"
    "#include <unistd.h>\n"
    "#include <vector>\n"
    "#include <sstream>\n"
    "#include <iostream>\n"
    "#define PORT 6666\n"
    "#define BUFFER_SIZE 1024\n"

    "std::vector<std::string> split (const std::string &s, char delim) {\n"
    "\tstd::vector<std::string> result;\n"
    "\tstd::stringstream ss (s);\n"
    "\tstd::string item;\n"
    "\twhile (getline (ss, item, delim)) {\n"
    "\t\tresult.push_back (item);\n"
    "\t}\n"
    "\treturn result;\n"
    "}\n"
    "int main(int argc, char *argv[]){\n"
    "\tint server_fd, new_socket;\n"
    "\tssize_t valread;\n"
    "\tstruct sockaddr_in address;\n"
    "\tint opt = 1;\n"
    "\tsocklen_t addrlen = sizeof(address);\n"
    "\tif ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {\n"
    "\t\tperror(\"socket failed\");\n"
    "\t\texit(EXIT_FAILURE);\n"
    "\t}\n"
    "\tif (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {\n"
    "\t\tperror(\"setsockopt\");\n"
    "\t\texit(EXIT_FAILURE);\n"
    "\t}\n"
    "\taddress.sin_family = AF_INET;\n"
    "\taddress.sin_addr.s_addr = INADDR_ANY;\n"
    "\taddress.sin_port = htons(PORT);\n"
    "\tif (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {\n"
    "\t\tperror(\"bind failed\");\n"
    "\t\texit(EXIT_FAILURE);\n"
    "\t}\n"
    "\tif(listen(server_fd, 3) < 0) {\n"
    "\t\tperror(\"listen\");\n"
    "\t\texit(EXIT_FAILURE);\n"
    "\t}\n"
    "\tint not_done = 1;\n"
    "\twhile(not_done){\n"
    "\t\tif ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {\n"
    "\t\t\tperror(\"accept\");\n"
    "\t\t\texit(EXIT_FAILURE);\n"
    "\t\t}\n"
    "\t\tchar buffer[BUFFER_SIZE] = { 0 };\n"
    "\t\twhile (valread = read(new_socket, buffer, BUFFER_SIZE) > 0) {\n"
    "\t\t\tstd::vector<std::string> v = split (buffer, ';');\n"
    "\t\t\tfor(int i = 0; i < RPC_FUNC_ARRAY_SIZE; i++){\n"
    "\t\t\t\tauto the_func = func_array[i]; \n"
    "\t\t\t\tif(strcmp(the_func.name, v[0].c_str()) == 0){\n"
    "\t\t\t\t\tstd::cout << \"name of func: \" << func_array[i].name << std::endl;\n"
    "\t\t\t\t\tunsigned char arg[BUFFER_SIZE];\n"
    "\t\t\t\t\tmemcpy(arg, buffer + v[0].size() + 1, BUFFER_SIZE - (v[0].size() + 1));\n"
    "\t\t\t\t\tunsigned char res[BUFFER_SIZE];\n"
    "\t\t\t\t\tthe_func.fp((void *)&arg, (void *)&res);\n"
    "\t\t\t\t\tsend(new_socket, res, BUFFER_SIZE, 0);\n"
    "\t\t\t\t\tmemset(buffer, 0, BUFFER_SIZE);\n"
    "\t\t\t\t\tmemset(res, 0, BUFFER_SIZE);\n"
    "\t\t\t\t\tmemset(arg, 0, BUFFER_SIZE);\n"
    "\t\t\t\t}\n"
    "\t\t\t}\n"
    "\t\t}\n"
    "\t\tif(valread == 0) {\n"
    "\t\t\tstd::cout << \"client disconencted\\n\";\n"
    "\t\t\tclose(new_socket);\n"
    "\t\t\tfflush(stdout);\n"
    "\t\t}\n"
    "\t}\n"
    "\treturn 0;\n"
    "}\n";

}



int main() {
    generateClientStub("client_stub");
    generateServerStub("server");
    return 0;
}
