#include "../headers/cpu.h"
/*
Manage loading of program
*/

#define segment_memory_size_index 20
#define segment_file_size_index 16
#define segment_va_index 8
#define segment_file_offset_index 4
#define segment_permissions 24
#define code_segment 1
#define section_type_index 4
#define section_size_index 20
#define section_file_offset_index 16
#define symbol_table 2
#define string_table 3
#define STACK_SIZE 20000

typedef char* ELF32;

void (*InitAddOn)(State* s); // initialize add-on function
void (*AddOn)(State* s); // add-on functionality

ELF32 LoadFile(char* filename)
{
    /*
    Load given file to memory
    filename - name of file (relative/full path)
    return: ptr to contents of file (in heap)
    */
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
    ELF32 file_contents = (ELF32)malloc(size);
    char* file_size[3];
    printf("File Size: %d\n", size);
    printf("File Descriptor: %d\n", fd);
    printf("Num of Bytes Read: %d\n", read(fd, file_contents, size));
    return file_contents;
}

void PrintHeader(int* header)
{
    /*
    Print Program Header from file program header table
    header - ptr to program header in file
    return: void
    */
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
    printf("Virtual Address: 0x%x\n", header[segment_va_index / 4]);
    printf("Physical Address: 0x%x\n", header[segment_va_index / 4 + 1]);
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

void LoadSegments(State* s, ELF32 file)
{
    /*
    Load memory segments from file program header
    s - ptr to State of current process
    file - ptr to contents of ELF
    return: void
    */
    char* memory;

    unsigned int size = 0, i;

    int e_phoff = ((int*)file)[7];

    short e_phentsize = ((short*)file)[21];
    short e_phnum = ((short*)file)[22];

    s->memory_segments = (Segment*)malloc(sizeof(Segment) * (e_phnum + 2) );
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
    int address = 0;
    for(i = 0; i < e_phnum; i++)
    {
        printf("Segment Number %d --\n", i);
        ptr = file + e_phoff + i * e_phentsize;
        address = *(ptr + segment_va_index/4) - s->base_address;
        memcpy1(s->memory + address, file + *(ptr + segment_file_offset_index/4), *(ptr + segment_file_size_index/4));
        PrintHeader(ptr);
        printf("\n");
        s->memory_segments[i].addr = address;
        s->memory_segments[i].permissions = ptr[segment_permissions / 4];
        s->memory_segments[i].size = ptr[segment_memory_size_index / 4];
    }
    //Stack Loading
    s->general_purpose[sp] = address + ptr[segment_memory_size_index / 4] + STACK_SIZE;
    s->general_purpose[s0] = s->general_purpose[sp];
    s->memory_segments[i].addr = s->general_purpose[sp] - STACK_SIZE;
    s->memory_segments[i].permissions = 0b111;
    s->memory_segments[i].size = STACK_SIZE;


    s->segment_count = e_phnum + 2;
}

void LoadSymtab(State* s, ELF32 file)
{
    /*
    Load program symbol table from ELF file to state for debugging purposes
    s - ptr to current State of process
    file - ptr to contents of ELF
    return: void
    */
    int e_shoff = ((int*)file)[8];
    short e_shentsize = ((short*)file)[23];
    short e_shnum = ((short*)file)[24];
    ELF32 section_header = file + e_shoff;
    unsigned int size = 0;
    for (int i = 0; i < e_shnum; i++)
    {
        if (section_header[i * e_shentsize + section_type_index] == symbol_table)
        {
            int *ptr = section_header + i * e_shentsize + section_size_index;
            size += *ptr;
        }
    }

    printf("Symbol Table size: %d\n", size);
    s->symtab = (char*)malloc(size);
    s->symtab_size = size;
    size = 0;
    for (int i = 0; i < e_shnum; i++)
    {
        if (section_header[i * e_shentsize + section_type_index] == symbol_table)
        {
            int* ptr_offset = section_header + i * e_shentsize + section_file_offset_index;
            unsigned int offset = *ptr_offset;
            printf("Symbol Table offset: 0x%x\n", offset);
            unsigned int* ptr_size = section_header + i * e_shentsize + section_size_index;
            memcpy1(s->symtab + size, file + offset, *ptr_size);
            size += *ptr_size;
        }
    }
}

void LoadStrtab(State* s, ELF32 file)
{
    /*
    Load program string table from ELF file to state for debugging purposes
    s - ptr to current State of process
    file - ptr to contents of ELF
    return: void
    */
    int e_shoff = ((int*)file)[8];
    short e_shentsize = ((short*)file)[23];
    short e_shnum = ((short*)file)[24];
    ELF32 section_header = file + e_shoff;
    unsigned int size = 0;
    for (int i = 0; i < e_shnum; i++)
    {
        if (section_header[i * e_shentsize + section_type_index] == string_table)
        {
            int *ptr = section_header + i * e_shentsize + section_size_index;
            size += *ptr;
        }
    }

    printf("String Table size: %d\n", size);
    s->strtab = (char*)malloc(size);
    s->strtab_size = size;
    size = 0;
    for (int i = 0; i < e_shnum; i++)
    {
        int* type_offset = section_header + i * e_shentsize + section_type_index;
        if (*type_offset == string_table)
        {
            int* ptr_offset = section_header + i * e_shentsize + section_file_offset_index;
            unsigned int offset = *ptr_offset;
            printf("String Table offset: 0x%x\n", offset);
            int* ptr_size = section_header + i * e_shentsize + section_size_index;
            memcpy1(s->strtab + size, file + offset, *ptr_size);
            size += section_header[i * e_shentsize + section_size_index];
        }
    }
}

void* LoadAddOn(char* dllname)
{
    /*
    Load Add On Program .so
    char* dllname - name of .so file
    return: void ptr to .so file
    */
    return dlopen(dllname, RTLD_LAZY | RTLD_GLOBAL);
}
/*
RTLD_GLOBAL
The object's symbols are made available for the relocation processing of any other object.
In addition, symbol lookup using dlopen(0, mode) and an associated dlsym() allows
objects loaded with this mode to be searched.
RTLD_LAZY
Relocations are performed at an implementation-dependent time, ranging from the time of the dlopen() call until the first reference to a given symbol occurs.
Specifying RTLD_LAZY should improve performance on implementations supporting dynamic symbol binding as a
process may not reference all of the functions in any given object.
And, for systems supporting dynamic symbol resolution for normal process execution,
this behaviour mimics the normal handling of process execution.
*/

void* Load(State* s, char* filename, char* addonname) {
    /*
    Load all memory from file to process, load add on functions
    s - current process state
    filename - ELF file name
    addonname - Add On file name
    */
    ELF32 file = LoadFile(filename);
    int e_entry = ((int*)file)[6];
    printf("Entry Point of File: 0x%x\n", e_entry);
    LoadSegments(s, file);

    s->pc = e_entry - s->base_address;
    LoadSymtab(s, file);
    LoadStrtab(s, file);
    printf("\n");
    char* error;
    void* dll = LoadAddOn(addonname);
    if (!dll) {
        fprintf(stderr, "%s\n", dlerror());
        exit(EXIT_FAILURE);
    }
    InitAddOn = dlsym(dll, "init_add_on");
    AddOn = dlsym(dll, "addon");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    return dll;

}
