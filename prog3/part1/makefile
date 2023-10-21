#
# Specifiy the target
all:	list

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
list:	SharedPtr_test.cpp
	g++  SharedPtr_test.cpp -pthread -ggdb -o prog.exe

# Specify how the object files should be created from source files


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *.gch prog.exe
