#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <unistd.h>

void* malloc(size_t size) {
    
    char buffer[32];
    sprintf(buffer, "malloc %ld", strlen(buffer));
    write(2, buffer, strlen(buffer));  
    void* (*real_malloc)(size_t);
    real_malloc = dlsym(RTLD_NEXT, "malloc");
    void* ptr_function = real_malloc(size);
    return ptr_function;
}

void free(void* ptr)
{
    char buffer[32];
    sprintf(buffer, "malloc %ld", strlen(buffer));
    write(2, buffer, strlen(buffer));
    void (*real_free)(void*);
    real_free = dlsym(RTLD_NEXT, "free");
    real_free(ptr);
}




