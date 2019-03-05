#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "interpreter.h"

void interpert();
void runFile(char*);
void stradd(char* tape, int* len, char chr) {
	tape[*len] = chr;
	(*len) ++;
	tape[*len] = '\0';
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		for (int i = 1; i < argc; i ++) {
			if (argv[i] != NULL) {
				//Assume its a file
				runFile(argv[i]);
			}
		}
	}
	else {
		runCommandLineTool();
	}
}

/**
* void runFile(char* path)
*	Reads in a file at path to use as a brainf*ck tape
*
*	path: Path to file being interpreted
*
*	ToDo: dont open file twice
*/
void runFile(char* path) {
	Interpreter* interpreter = new Interpreter();
	char buff[2];
	buff[1] = '\0';
	FILE *fp;
	fp = fopen(path, "r+");
	fseek (fp, 0, SEEK_END);
	int length = ftell (fp);
	fclose(fp);
	int len = 0;
	char* tape = new char[length];
	fp = fopen(path, "r+");
	while(fgets(buff, 2, fp) != 0){// Print one char at a time
		stradd(tape, &len, buff[0]);
	}
	fclose(fp);
	interpreter->run(tape);
}

/**
* void runCommandLineTool()
*	runs tapes received from stdin as brainf*ck
*/
void runCommandLineTool() {
	Interpreter* interpreter = new Interpreter();
	char buf[2] = {'\0', '\0'};
	char tape[1000] = {'\0'};
	int len = 0;
	while(true) {
		write(1,"\nbrainf*ck> ",13); 
		while(read(0, buf, 1) != 0){
			if(buf[0] == '\n') 
				break;
			stradd(tape, &len, buf[0]);
		}
		stradd(tape, &len, '\0');
		interpreter->run(tape);
		tape[0] = '\0';
		len = 0;
	}
	exit(0);
}
