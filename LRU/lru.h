#include "list.h"
#include <stdint.h>
#include <math.h>

typedef struct {
    int capacity;
    int count;
    int hash_type;
    struct list_head dhead;
    struct hlist_head hhead[];
} LRUCache;

typedef struct {
    int key;
    int value;
    struct hlist_node node;
    struct list_head link;
} LRUNode;

int division_hash(LRUCache *obj,int key){
    return key % obj->capacity;
}

int multiplication_hash(LRUCache *obj,int key){
    double A = (sqrt(5) - 1) / 2;
    double s = key * A;
    double x = s - floor(s);
    return floor(obj->capacity * x);
}

int hash_function(LRUCache *obj,int key){
    if(obj->hash_type==0)
        return division_hash(obj,key);
    return multiplication_hash(obj,key);
}

void print_LRU_list(struct list_head* dhead){
    
    if(dhead->next == dhead)
        return;

    struct list_head *pos;
    LRUNode *c = NULL;
    printf("The recent used list : \n");
    list_for_each(pos,dhead){
        c = list_entry(pos, LRUNode, link);
        printf("(key:%d, value:%d) => ",c->key,c->value);
    }
    printf("\n");
    
}

LRUCache *lRUCacheCreate(int capacity,int hash_type)
{
    LRUCache *cache = malloc(2 * sizeof(int) + sizeof(struct list_head) +
                             capacity * sizeof(struct hlist_head) + sizeof(int));
    cache->capacity = capacity;
    cache->count = 0;
    cache->hash_type = hash_type;
    INIT_LIST_HEAD(&cache->dhead);
    for (int i = 0; i < capacity; i++)
        INIT_HLIST_HEAD(&cache->hhead[i]);
    return cache;
}

void lRUCacheFree(LRUCache *obj)
{
    struct list_head *pos, *n;
    list_for_each_safe (pos, n, &obj->dhead) {
        LRUNode *cache = list_entry(pos, LRUNode, link);
        list_del(&cache->link);
        free(cache);
    }
    free(obj);
}

int lRUCacheGet(LRUCache *obj, int key)
{
    int hash = hash_function(obj,key);
    struct hlist_node *pos;
    hlist_for_each (pos, &obj->hhead[hash]) {
        LRUNode *cache = list_entry(pos, LRUNode, node);
        if (cache->key == key) {
            list_move(&cache->link, &obj->dhead);
            hlist_del(&cache->node);
            hlist_add_head(&cache->node, &obj->hhead[hash]);
            return cache->value;
        }
    }
    return -1;
}

void lRUCachePut(void * priv, LRUCache *obj, int key, int value)
{
    LRUNode *cache = NULL;
    int hash = hash_function(obj,key);
    struct hlist_node *pos;
    hlist_for_each (pos, &obj->hhead[hash]) {
        LRUNode *c = list_entry(pos, LRUNode, node);
        if (c->key == key) {    
            hlist_del(&c->node);
            hlist_add_head(&c->node, &obj->hhead[hash]);
            list_move(&c->link, &obj->dhead);
            cache = c;
        }
    }
    if(obj->hhead[hash].first != NULL)
        *((int *)priv+hash) += 1;

    if (!cache) {
        if (obj->count == obj->capacity) {
            cache = list_last_entry(&obj->dhead, LRUNode, link);
            list_move(&cache->link, &obj->dhead);
            hlist_del(&cache->node);
            hlist_add_head(&cache->node, &obj->hhead[hash]);
        } else {
            cache = malloc(sizeof(LRUNode));
            hlist_add_head(&cache->node, &obj->hhead[hash]);
            list_add(&cache->link, &obj->dhead);
            obj->count++;
        }
        cache->key = key;
    }
    cache->value = value;
}
