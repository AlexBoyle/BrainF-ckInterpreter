#
# PROGRAM:    assign2
# PROGRAMMER: Alex Boyle
#             z1759628
#

# Compiler variables
CCFLAGS = -Wall -std=c++11

# Rule to link object code files to create executable file
main: main.cc
	g++ $(CCFLAGS) *.cc  -o bf

clean:
	rm bf.exe