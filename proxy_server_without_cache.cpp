#include<iostream>
#include <fstream>
#include<thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>

#include "lru_cache.h"

#define PORT_NUMBER 8080

using namespace std;

int proxy_socket_id;

void connectToRemoteServer(string url) {
    string get_http = "GET " + url + "\r\nConnection: close\r\n\r\n";
    struct hostent *host;
    const char *char_url = url.c_str();
    host = gethostbyname(char_url);

    if(host == NULL) return;
    cout << "TEST1\n";

    int remote_socket = socket(AF_INET, SOCK_STREAM, 0);

    if(remote_socket < 0) {
        cout << "can't create socket\n";
        return;
    }

    cout << "TEST2\n";

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);
    server_address.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    int status = connect(remote_socket, (struct sockaddr*)&server_address, sizeof(server_address));

    if(status != 0) {
        cout << "Could not connect to url\n" << endl;
        return;
    }

    cout << "TEST3\n";

    send(remote_socket, get_http.c_str(), strlen(get_http.c_str()), 0);
    int data_len = 0;
    char buffer[1024];
    string html;
    while((data_len = recv(remote_socket, buffer, sizeof(buffer), 0)) > 0) {
        int idx = 0;
        while(idx < data_len) {
            html += buffer[idx];
            idx++;
        }
        cout << "Data recv length : " << data_len << endl;
    }
    
    fstream file; 
    file.open("test.html", ios::out); 
  
    if(!file) 
    {
        cout << html << endl;
        cout << html.size() << endl;
        cout <<"Error in creating file!!!"; 
        return; 
    } 
  
    file << html; 
    file.close();

    shutdown(remote_socket, SHUT_RDWR);
    close(remote_socket);
}

int main(int argc, char* argv[]) {
    // proxy_socket_id = socket(AF_INET, SOCK_STREAM, 0);
    // cout << "proxy socket id : " << proxy_socket_id << endl;

    // close(proxy_socket_id);
    connectToRemoteServer("www.geeksforgeeks.org");
    return 0;
}