#include "vector.h"
#include <stdio.h>


int __vector_PushPtr(Vector *v, void *elem) {
    if (v->top == v->cap - 1) {
        Vector_Resize(v, v->cap ? v->cap*2 : 1);
    }
    
    __vector_PutPtr(v, v->top, elem);
    v->top++;
    return v->top;
}


int Vector_Get(Vector *v, int pos, void *ptr) {
    if (pos >= v->top) {
        return 0;
    }
    memcpy(ptr, v->data + (pos * v->elemSize), v->elemSize);
    return 1;
}


int __vector_PutPtr(Vector *v, int pos, void *elem) {
    if (pos > v->cap) {
        Vector_Resize(v, pos+1);
    }
    
    memcpy(v->data + pos*v->elemSize, elem, v->elemSize);
    if (pos > v->top) {
        v->top = pos;
    }
    return 1;
}


int Vector_Resize(Vector *v, int newcap) {
    int oldcap = v->cap;
    v->cap = newcap;
    
    v->data = realloc(v->data, v->cap*v->elemSize);
    int offset = v->top*v->elemSize;
    memset(v->data + offset, 0, v->cap*v->elemSize - offset);
    return v->cap;
}


Vector *__newVectorSize(size_t elemSize, size_t cap) {
    printf("allocating %zd elems of %zd size\n", cap, elemSize);
    Vector *vec = malloc(sizeof(Vector));
    vec->data = calloc(cap, elemSize);
    vec->top = 0;
    vec->elemSize = elemSize;
    vec->cap = cap;
   
    return vec;  
}

void Vector_Free(Vector *v) {
    free(v->data);
    free(v);
}
 