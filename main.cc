#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
using namespace std;
unsigned char mem[1000] = {0};
unsigned char* ptr = &mem[500];
void interpert();
void runFile(char*);
char* run(char* tape);
char* block(char*);
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
		interpert();
	}
}
void runFile(char* file) {
	char buff[2];
	buff[1] = '\0';
	FILE *fp;
	fp = fopen(file, "r+");
	fseek (fp, 0, SEEK_END);
	int length = ftell (fp);
	fclose(fp);
	int len = 0;
	char* tape = new char[length];
	fp = fopen(file, "r+");
	while(fgets(buff, 2, fp) != 0){// Print one char at a time
		stradd(tape, &len, buff[0]);
	}
	cerr << '\n';
	fclose(fp);
	run(tape);
}
void interpert() {
	char buf[2] = {'\0', '\0'};
	char tape[1000] = {'\0'};
	int len = 0;
	while(true) {
		cerr <<"\nbrainf*ck> "; 
		while(read(0, buf, 1) != 0){
			if(buf[0] == '\n') 
				break;
			stradd(tape, &len, buf[0]);
		}
		stradd(tape, &len, '\0');
		run(tape);
		tape[0] = '\0';
		len = 0;
	}
	exit(0);
}
char* run(char* tape) {
	char* tapePtr = tape;
	while ((*tapePtr) != '\0') {
		switch((*tapePtr)) {
			case '+':
				(*ptr)++;
				break;
			case '-':
				(*ptr)--;
				break;
			case '<':
				ptr --;
				break;
			case '>':
				ptr ++;
				break;
			case '.':
				cerr << (char)(*ptr);
				break;
			case ',':
				read(STDIN_FILENO, ptr, 1);
				break;
			case '[':
				tapePtr = block(tapePtr);
				break;
			case ']':
				return tapePtr;
				break;
		}
		tapePtr ++;
	}
	return NULL;
}
char* findEnd(char* tape) {
	char* tapePtr = tape;
	int count = 1;
	while ((*tapePtr) != '\0') {
		if((*tapePtr) == '[') {
			count ++;
		}
		else if ((*tapePtr) == ']') {
			count --;
			if(count == 0) {
				return tapePtr;
			}
		}
		tapePtr ++;
	}
	return NULL;
}
char* block(char* tapePtr) {
	tapePtr ++;
	if((*tapePtr) == ']')
		return (tapePtr ++);
	char* begin = tapePtr;
	char* end = findEnd(begin);
	while ((*ptr) != 0) {
		if(run(tapePtr) != NULL) {
			tapePtr = begin;
		}
	}
	return end;
}
