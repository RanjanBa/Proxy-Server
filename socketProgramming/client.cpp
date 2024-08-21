#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <chrono>
using namespace std;

int main() {
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(6000);
    server_address.sin_addr.s_addr = INADDR_ANY;

    connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    const char *message = "Hello, server!";

    send(client_socket, message, strlen(message), 0);

    while(1) {
        cout << "running..." << endl;
        char buffer[1024] = {0};
        recv(client_socket, buffer, sizeof(buffer), 0);
        cout << "Message from server : " << buffer << endl;
        sleep(1000);
    }

    close(client_socket);

    return 0;
}