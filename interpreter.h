#ifndef INTERPRETER
#define INTERPRETER
class Interpreter {
	public:
		Interpreter();
		char* run(char*);
	private:
		unsigned char mem[1000] = {(char)0};
		unsigned char* ptr;
		char* block(char*);
		char* findEnd(char*);
};
#endif