#include "types.h"

void* mnalloc(size_t size){
    void* z=malloc(size);
    assert(z);
    return z;
}
void* mnrealloc(void* ptr,size_t size){
    void* z=realloc(ptr,size);
    assert(z);
    return z;
}
void* mncalloc(size_t count,size_t size){
    void* z= calloc(count,size);
    assert(z);
    return z;
}
void mnfree(void* ptr){
    free(ptr);
}

