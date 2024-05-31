#include "../../headers/cpu.h"
#include <sys/mman.h>
/*
Manage syscall hooks
*/


int FixFlags(int flags)
{
    /*
    match flags in mmap function to flag conventions in ELF format
    flags - mmap flag parameter
    return: fixed flags
    */
    int new_flags = 0;
    if (flags & 1)
    {
        new_flags |= (1 << R);
    }
    if ((flags >> 1) & 1)
    {
        new_flags |= (1 << W);
    }
    if ((flags >> 2) & 1)
    {
        new_flags |= (1 << X);
    }
    return new_flags;

}

void ReallocMemory(State* s, unsigned int new_size)
{
    /*
    allocate new memory size to process
    s - current state
    new_size - new memory size
    return: void
    */
    char* new_memory = malloc(new_size);
    memcpy1(new_memory, s->memory, s->memory_size);
    free(s->memory);
    s->memory = new_memory;
    int temp = s->memory_size;
    s->memory_size = new_size;
}

void* AddMemory(State* s, char* st)
{
    /*
    add memory to process memory
    s - current state
    st - new added memory
    return: void ptr of new memory index
    */
    ReallocMemory(s, s->memory_size + strlen(st));
    s->memory_segments[s->segment_count - 2].size += strlen(st);
    int index = s->memory_segments[s->segment_count - 2].addr + s->memory_segments[s->segment_count - 2].size - strlen(st);
    memcpy1(s->memory + index, st, strlen(st));
    return (void*)index;
}

void* MMAP(State* s,  unsigned int addr, size_t length, int protect, int flags, int filedes, off_t offset)
{
    /*
    MMAP - memory map hook
    s - the current state of the CPU
    addr - the address where the mapping starts
    length - the length of the mapping
    protect - memory protection flags
    flags - mapping flags
    filedes - file descriptor
    offset - offset in the file
    return: pointer to the mapped area on success, (void*)-1 on failure
    */
    if (flags & MAP_FIXED)
    {
        return (void*)-1; //only anonymous mapping is allowed currently.
    }
    if (filedes == -1)
    {
        unsigned int start_ptr = s->memory_size;
        ReallocMemory(s, s->memory_size + length);
        Segment* temp = (Segment*)malloc(sizeof(Segment) * (s->segment_count + 1));
        memcpy1((unsigned char*)temp, (unsigned char*)s->memory_segments, sizeof(Segment) * s->segment_count);
        temp[s->segment_count].addr = start_ptr;
        temp[s->segment_count].permissions = FixFlags(flags);
        temp[s->segment_count].size = length;
        s->segment_count++;
        free(s->memory_segments);
        s->memory_segments = temp;
        return (void*)(s->memory + start_ptr);
    }
    return (void*)(-1);

}
int BRK(State* s, unsigned int addr)
{
    /*
    BRK - changes the end of the data segment to the specified address
    s - the current state of the CPU
    addr - the address to set as the end of the data segment
    return: 0 on success, -1 on failure
    */
    int stack_index = s->segment_count - 1;
    int difference = addr - s->memory_segments[stack_index].addr;
    if (difference < 0)
    {
        return -1;
    }
    char* temp = malloc(s->memory_size + difference);
    int i;
    for (i = 0; i < stack_index; i++)
    {
        memcpy1(temp + s->memory_segments[i].addr, s->memory + s->memory_segments[i].addr, s->memory_segments[i].size);
    }
    s->memory_segments[i].addr += difference;
    memcpy1(temp + s->memory_segments[i].addr, s->memory + s->memory_segments[i].addr - difference, s->memory_segments[i].size);
    free(s->memory);
    s->memory = temp;

}

int MUNMAP(State* s, unsigned int addr, size_t length)
{
    /*
    MUNMAP - unmaps a mapped area of memory
    s - the current state of the CPU
    addr - the address to start unmapping
    length - the length of the memory to unmap
    return: 0 on success, -1 on failure
    */
    size_t size = s->memory_size - length;
    char* tmp = malloc(size);
    if (!in_range(s->base_address, addr, s->memory_size + s->base_address))
    {
        return -1;
    }
    int i;
    for (i = 0; i < s->segment_count; i++)
    {
        if (s->memory_segments[i].addr == addr)
        {
            memcpy1(tmp, s->memory, addr - s->base_address);
            memcpy1(tmp + addr - s->base_address, s->memory + addr + s->memory_segments[i].size, size - (addr - s->base_address));
            return 0;
        }
    }
    return -1;
}

void* MREMAP(State** s, void* old_address, size_t old_size, size_t new_size, int flags, void* new_address)
{

}

