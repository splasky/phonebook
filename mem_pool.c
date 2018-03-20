#include "mem_pool.h"
#include <stdlib.h>

m_pool* pool_allocate(int size)
{
    m_pool* pool = malloc(sizeof(m_pool));
    pool->head = pool->next = calloc(1, size);
    pool->tail = pool->head + size;

    return pool;
}

void* pool_access(m_pool* pool, int size)
{
    if (pool->tail - pool->next < size)
        return NULL;

    void* tmp = pool->next;
    pool->next = pool->next + size;

    return tmp;
}

void pool_free(m_pool* pool)
{
    free(pool->head);
    free(pool);
}
