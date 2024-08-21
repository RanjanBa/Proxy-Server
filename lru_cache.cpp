#include<iostream>
#include "cache.h"
#include "lru_cache.h"

LRUCache::LRUCache(int capacity) : max_capacity(capacity) , number_of_items(0) {
    head = NULL;
    tail = NULL;
}

void LRUCache::pushFront(Cache* cache) {
    if(cache == NULL) return;
    cache->prev = NULL;
    cache->next = NULL;
    
    if(head == NULL) {
        head = cache;
        tail = cache;
        return;
    }

    cache->next = head;
    head->prev = cache;

    head = cache;
    number_of_items++;
}

Cache* LRUCache::popBack() {
    if(tail == NULL) return NULL;

    Cache* tmp = tail;

    Cache* prev = tail->prev;
    if(prev) {
        prev->next = NULL;
    } else {
        head = NULL;
    }

    tail = prev;
    number_of_items--;
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
}

void LRUCache::removeCache(Cache *cache) {
    if(cache == NULL) return;

    Cache* prev = cache->prev;
    Cache* next = cache->next;

    if(prev == NULL) {
        head = next;
    } else {
        prev->next = next;
    }

    if(next == NULL) {
        tail = prev;
    } else {
        next->prev = prev;
    }

    cache->prev = NULL;
    cache->next = NULL;
    number_of_items--;
}

Cache* LRUCache::getCache(std::string url) {
    if(mp.find(url) != mp.end()) {
        Cache* cache = mp[url];
        removeCache(cache);
        pushFront(cache);
        return cache;
    }

    std::cout << "Not Found!" << std::endl;
    return NULL;
}

void LRUCache::addCache(Cache *cache) {
    if(cache == NULL) return;

    if(mp.find(cache->url) != mp.end()) {
        cache = mp[cache->url];
        removeCache(cache);
        pushFront(cache);
        return;
    }

    pushFront(cache);
    mp[cache->url] = cache;
    
    while(number_of_items > max_capacity) {
        Cache* last = popBack();
        if(last) {
            mp.erase(last->url);
        }
        std::cout << "remove : " << number_of_items << ", mp size : " << mp.size() << std::endl;
    }
}

void LRUCache::debug() {
    Cache *cache = head;
    std::cout << "number of items : " << number_of_items << " : mp size : " << mp.size() << std::endl;
    while(cache) {
        std::cout << cache->url << " ";
        cache = cache->next;
    }
    std::cout << std::endl;
}

void LRUCache::reverseDebug() {
    Cache *cache = tail;
    std::cout << "Reverse iter :\n number of items : " << number_of_items << " : mp size : " << mp.size() << std::endl;
    while(cache) {
        std::cout << cache->url << " ";
        cache = cache->prev;
    }
    std::cout << std::endl;
}
