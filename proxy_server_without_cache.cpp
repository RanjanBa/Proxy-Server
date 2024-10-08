#include <iostream>
#include <fstream>
#include <thread>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <curl/curl.h>

#define PORT_NUMBER 8080

using namespace std;

int proxy_socket_id;

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

void connectToRemoteServer(char url[])
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "error : %s\n", curl_easy_strerror(res));
        } else {
            cout << "ok!" << endl;
        }

        curl_easy_cleanup(curl);

        std::cout << readBuffer << std::endl;
        fstream file;
        file.open("index.html", ios::out);

        if (!file)
        {
            cout << "Error in creating file!!!";
            return;
        }

        file << readBuffer;
        file.close();
    }

}

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        cout << "Give url" << endl;
        return 0;
    }
    char *url = argv[1];
    connectToRemoteServer(url);
    return 0;
}