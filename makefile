all: cpu.o

C_SRCS = ./c_src
C_FILES = $(wildcard $(C_SRCS)/add-ons/*.c $(C_SRCS)/Interrupts/*.c $(C_SRCS)/standard_extension/*.c $(C_SRCS)/*.c)
cpu.o: $(C_FILES)
	gcc -m32 $^ -o $@ -lm
memcheck.so: $(C_SRCS)/tools/memcheck.c
	gcc -m32 -shared -o memcheck.so -fPIC $(C_SRCS)/tools/memcheck.c $(C_SRCS)/add-ons/str.c $(C_SRCS)/add-ons/types.c

clean:
	rm -rf cpu.o

.PHONY: clean
