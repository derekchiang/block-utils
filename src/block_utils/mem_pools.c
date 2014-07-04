#include "stdlib.h"
#include "stddef.h"

#include "apr_pools.h"

#include "block_utils/mem_pools.h"

typedef struct pool_list {
    apr_pool_t *head;
    struct pool_list *prev;
} pool_list_t;

static __thread pool_list_t *pl = NULL;

apr_pool_t *bu_current_pool(void) {
    if (pl) return pl->head;
    else return NULL;
}

void *bu_alloc(size_t size) {
    return apr_palloc(pl->head, size);
}

void bu_with_pool(bu_normal_b block) {
    if (!pl) {
        pl = malloc(sizeof(pool_list_t));
        apr_pool_t *pool;
        apr_pool_create(&pool, NULL);
        pl->head = pool;
        pl->prev = NULL;
    } else {
        apr_pool_t *pool;
        apr_pool_create(&pool, pl->head);
        pool_list_t *next = apr_palloc(pl->head, sizeof(pool_list_t));
        next->head = pool;
        next->prev = pl;
        pl = next;
    }

    block();

    apr_pool_destroy(pl->head);
    if (!pl->prev) {  // is root
        free(pl);
        pl = NULL;
    } else {
        pl = pl->prev;
    }
}

