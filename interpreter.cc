#include <unistd.h>
#include <stdio.h>

#include "interpreter.h"

Interpreter::Interpreter() {
	this->ptr = &mem[4];
}
char* Interpreter::run(char* tape) {
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
				write(1,ptr,1);
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
char* Interpreter::findEnd(char* tape) {
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
char* Interpreter::block(char* tapePtr) {
	tapePtr ++;
	if((*tapePtr) == ']')
		return (tapePtr ++);
	char* begin = tapePtr;
	char* end = findEnd(begin);
	while ((*ptr) != 0) {
		if(this->run(tapePtr) != NULL) {
			tapePtr = begin;
		}
	}
	return end;
}
