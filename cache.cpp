#include<iostream>
#include "cache.h"

Cache::Cache(std::string url) {
    prev = NULL;
    next = NULL;
    this->url = url;
}