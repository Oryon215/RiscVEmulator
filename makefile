all:  cpu.o
C_SRCS = ./c_src
cpu.o: $(C_SRCS)/cpu.c $(C_SRCS)/rv32i.c $(C_SRCS)/test_cpu.c $(C_SRCS)/str.c $(C_SRCS)/types.c 
	gcc -m32 $^ -o $@
