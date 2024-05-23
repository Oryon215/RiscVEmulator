all: cpu.o

C_SRCS = ./c_src
C_FILES = $(wildcard $(C_SRCS)/add-ons/*.c $(C_SRCS)/Interrupts/*.c $(C_SRCS)/standard_extension/*.c $(C_SRCS)/*.c)
cpu.o: $(C_FILES)
	gcc -m32 $^ -o $@ -lm

clean:
	rm -rf cpu.o

.PHONY: clean
