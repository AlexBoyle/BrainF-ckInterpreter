#ifndef INTERPRETER
#define INTERPRETER
class Interpreter {
	public:
	
		/**
		* Interpreter();
		*	Creates an instace of Interpreter and sets the inital position of
		*	the pointer
		*/
		Interpreter();
		
		/**
		* char* run(char*);
		*	Runs through a c_string tape and interprets it as brainf*ck
		*
		*	char*: pointer to the first char of the c_string tape
		*
		*	returns:
		*		NULL when this function reaches the end of the givin tape
				Pointer to the current position when the pointers value is ']'
		*/
		char* run(char*);
	private:
		
		// Memory cells
		unsigned char mem[1000] = {(char)0};
		
		// brainf*ck pointer
		unsigned char* ptr;
		
		/**
		*
		*
		*/
		char* block(char*);
		
		/**
		*
		*
		*/
		char* findEnd(char*);
};
#endif