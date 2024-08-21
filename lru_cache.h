#pragma once
#include<unordered_map>
#include "cache.h"

class LRUCache {
    private:
        const int max_capacity;
        int number_of_items;
        Cache* head;
        Cache* tail;
        std::unordered_map<std::string, Cache*> mp;
        void pushFront(Cache* cache);
        Cache* popBack();
        void removeCache(Cache* cache);
    public:
        LRUCache(int capacity=10);
        Cache* getCache(std::string url);
        void addCache(Cache *cache);
        void debug();
        void reverseDebug();
};