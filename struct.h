#include<stdio.h>
#include<stdlib.h>

typedef struct RingInfo{
    size_t size;
    size_t size_p1;
    size_t size_p2;
    void (*sum)(void* , void* , void*);
    void (*mult)(void* , void* , void*);
    void (*transp)(void* , void*);
}RingInfo;

typedef struct matrix{
    void*** Mpoint;
    size_t lenght;
    size_t hight;
    RingInfo* ringinfo;
}matrix;