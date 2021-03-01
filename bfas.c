// bfas assembler:
// Brainfuck assembler

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PUSH(data) append(output, data); \
                   break;


typedef char BFBYTE;

typedef enum {
	ptr_inc = '>',
	ptr_dec = '<',
	val_inc = '+',
	val_dec = '-',
	val_out = '.',
	val_in  = ',',
	forward = '[',
	backward = ']'
} instruction_t;

void append(char* string, BFBYTE byte) {
	int last_index = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i])
			last_index++;
	}
	string[last_index] = byte;
}

BFBYTE* compile(char* program) {
    BFBYTE* output;

    for (int i = 0; i < strlen(program); i++) {
        switch (program[i]) {
            case (ptr_inc) :
                PUSH(0x00)
            case (ptr_dec) :
                PUSH(0x01)
            case (val_inc) :
                PUSH(0x02)
            case (val_dec) :
                PUSH(0x03)
            case (val_out) :
                PUSH(0x04)
            case (val_in) :
                PUSH(0x05)
            case (forward) :
                PUSH(0x06)
            case (backward) :
                PUSH(0x07)
        }
    }

    return output;
}

int main(int argc, char** argv) {
	if (argc < 1) {
		printf("No input file specified\n");
		printf("$ bfas <file>");
		return 1;
	} else {
		BFBYTE* program;
		FILE* in = fopen(argv[1], "r");
		fscanf(in, "%s", program);
		BFBYTE* output = compile(program);
        FILE* out = fopen("a.bfb", "w+");
        fprintf(out, output);

        fclose(in);
        fclose(out);
		return 0;
	}
}