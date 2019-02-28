#
# PROGRAM:    assign2
# PROGRAMMER: Alex Boyle
#             z1759628
#

# Compiler variables
CCFLAGS = -Wall

# Rule to link object code files to create executable file
main: main.cc
	g++ $(CCFLAGS) main.cc -o bf

clean:
	rm bf.exe