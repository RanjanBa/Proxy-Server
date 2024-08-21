#pragma once

class Cache {
    public:
        std::string url;
        char* data;
        int data_len;
        Cache* next;
        Cache* prev;
        Cache(std::string url);
};