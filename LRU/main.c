#include <stdio.h>
#include <stdlib.h>
#include "lru.h"


int main(int argc, char *argv[])
{
    int size = atoi(argv[1]);
    int hash_type = atoi(argv[2]);
    LRUCache *cache = lRUCacheCreate(size,hash_type);
    int *collision_count=malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++) {
        collision_count[i] = 0;
    }

    int test_times = 1000000;
    for (int i = 0; i < test_times; i++) {
        int key = rand();
        int value = rand();

        if (rand() % 2) {
            lRUCachePut(collision_count,cache, key, value);
        } else {
            lRUCacheGet(cache, key);
        }
    }
    int total_count = 0;
    for (int i = 0; i < size; i++) {
        printf("Hash table[%d] collision_count: %d\n",i,collision_count[i]);
        total_count += collision_count[i];
    }
    printf("Total collision_count : %d",total_count);

    return 0;
}
