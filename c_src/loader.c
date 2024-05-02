#include "../headers/cpu.h"
#include <sys/stat.h>
#include <fcntl.h>

#define segment_memory_size_index 20
#define segment_file_size_index 16
#define segment_va_index 8
#define segment_file_offset_index 4
#define segment_permissions 24
#define code_segment 1

#define STACK_SIZE 10000

char* LoadFile(char* filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("Error reading file %s.", filename);
        exit(1);
    }

    off_t size = lseek(fd, 0, SEEK_END);
    if (size == -1) {
        perror("Failed to seek to end of file");
        close(fd);
        return 1;
    }
    close(fd);
    fd = open(filename, O_RDONLY);
    char* file_contents = (char*)malloc(size);
    char* file_contents2[3];
    printf("File Size: %d\n", size);
    printf("File Descriptor: %d\n", fd);
    printf("Num of Bytes Read: %d\n", read(fd, file_contents, size));
    return file_contents;
}

void LoadSegments(State* s, char* file)
{
    char* memory;

    unsigned int size = 0, i;

    int e_phoff = ((int*)file)[7];

    short e_phentsize = ((short*)file)[21];
    short e_phnum = ((short*)file)[22];

    s->memory_segments = (Segment*)malloc(sizeof(Segment) * (e_phnum - 1));

    // get program size
    printf("Program header entries count: %hi\n", e_phnum);
    printf("Program header entry size: %hi\n", e_phentsize);
    printf("Program header file offset: 0x%x\n", e_phoff);
    unsigned int* ptr = file + e_phoff + (e_phnum - 1) * e_phentsize;
    size = ptr[segment_memory_size_index / 4] + ptr[segment_va_index / 4];
    s->memory_size = size + STACK_SIZE;
    s->memory = (char*)calloc(s->memory_size, sizeof(char));
    printf("Virtual Memory Size: %d\n", s->memory_size);
    // get base address
    s->base_address = *(int *)(file + e_phoff + segment_va_index);

    printf("Base Address: 0x%x\n", s->base_address);

    // load_segments
    // skip riscv attributes
    printf("\nProgram Header Table:\n");
    int address;
    for(i = 0; i < e_phnum; i++)
    {
        printf("Segment Number %d --\n", i);
        ptr = file + e_phoff + i * e_phentsize;
        address = *(ptr + segment_va_index/4) - s->base_address;
        memcpy1(s->memory + address, file + *(ptr + segment_file_offset_index/4), *(ptr + segment_file_size_index/4));
        PrintHeader(ptr);
        printf("\n");
        s->memory_segments[i - 1].addr = address;
        s->memory_segments[i - 1].permissions = ptr[segment_permissions / 4];
        s->memory_segments[i - 1].size = ptr[segment_memory_size_index / 4];
    }
    s->general_purpose[sp] = address + ptr[segment_memory_size_index / 4];
    s->general_purpose[s0] = s->general_purpose[sp];
    s->memory_segments[i - 1].addr = s->general_purpose[sp];
    s->memory_segments[i - 1].permissions = 0x111;
    s->memory_segments[i - 1].size = STACK_SIZE;
    s->segment_count = e_phnum;
}

void Load(State* s, char* filename) {

    char* file = LoadFile(filename);
    int e_entry = ((int*)file)[6];
    printf("Entry Point of File: 0x%x\n", e_entry);
    LoadSegments(s, file);
    s->pc = e_entry - s->base_address;

}

void PrintHeader(int* header)
{
    int p_type = header[0];
    printf("Type: ");
    switch (p_type)
    {
    case 0:
        printf("PT_NULL");
        break;
    case 1:
        printf("PT_LOAD");
        break;
    case 2:
        printf("PT_DYNAMIC");
        break;
    case 3:
        printf("PT_INTERP");
        break;
    case 4:
        printf("PT_NOTE");
        break;
    case 5:
        printf("PT_SHLIB");
        break;
    case 6:
        printf("PT_PHDR");
        break;
    default:
        printf("PT_LOPROC/PT_HIPROC");
        break;

    }

    printf("\n");
    printf("Offset: %d\n", header[segment_file_offset_index / 4]);
    printf("Virtual Address: %d\n", header[segment_va_index / 4]);
    printf("Physical Address: %d\n", header[segment_va_index / 4 + 1]);
    printf("File Size: %d\n", header[segment_file_size_index / 4]);
    printf("Memory Size: %d\n", header[segment_memory_size_index / 4]);
    printf("Flags:");
    if ((header[segment_permissions / 4] >> R) & 1)
    {
        printf("R");
    }
    else
    {
        printf(" ");
    }
    if ((header[segment_permissions / 4] >> W) & 1)
    {
        printf("W");
    }
    else
    {
        printf(" ");
    }
    if ((header[segment_permissions / 4] >> X) & 1)
    {
        printf("X");
    }
    else
    {
        printf(" ");
    }
    printf("\n");
    printf("Alignment: %d\n", header[segment_permissions / 4 + 1]);
}
