// bfvm VM:
// Brainfuck virtual
// machine

#include <stdio.h>
#include <string.h>
#include <stdbool.h>


typedef char BFBYTE;
BFBYTE* VMbyte;

typedef enum {
	ptr_inc = 0x00,
	ptr_dec = 0x01,
	val_inc = 0x02,
	val_dec = 0x03,
	val_out = 0x04,
	val_in  = 0x05,
	forward = 0x06,
	backward = 0x07
} instruction_t;


void append(BFBYTE* string, BFBYTE byte) {
	int last_index = 0;
	for (int i = 0; i < strlen(string); i++) {
		if (string[i])
			last_index++;
	}
	string[last_index] = byte;
}

void eval(BFBYTE* program) {
	BFBYTE* record;
	BFBYTE instruction;
	bool running = true;

	int i, j;

	if (running)
	for (i = 0; i < strlen(program); i++) {
		switch (program[i]) {
			case (ptr_inc) :
				VMbyte++;
				break;
			case (ptr_dec) :
				VMbyte--;
				break;
			case (val_inc) :
				*(VMbyte)++;
				break;
			case (val_dec) :
				*(VMbyte)--;
				break;
			case (val_out) :
				printf("%c", VMbyte);
				break;
			case (val_in) :
				*VMbyte = getchar();
				break;
			case (forward) :
				for (j = i; j != backward; j++) {
					append(record, program[j]);
				}
				if (!*VMbyte)
					i = j;
				break;
			case (backward) :
				break;

			default :
				printf("BFVM OPCODE ERROR: Unknown instruction %x", program[i]);
				running = false;
				break;
		}
	}
}


int main(int argc, char** argv) {
	if (argc < 1) {
		printf("No input file specified\n");
		printf("$ bfvm <file>");
		return 1;
	} else {
		BFBYTE* program;
		FILE* fp = fopen(argv[1], "r");
		fscanf(fp, "%s", program);
		eval(program);
		return 0;
	}
}
