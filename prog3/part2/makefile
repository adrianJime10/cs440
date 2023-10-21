#
# Specifiy the target
all:	list

# Specify the object files that the target depends on
# Also specify the object files needed to create the executable
list:	Array_test.o MyInt.o
	g++  Array_test.o MyInt.o -ggdb -o prog.exe

Array_test.o: Array_test.cpp
	g++ -c Array_test.cpp

MyInt.o: MyInt.cpp
	g++ -c MyInt.cpp

# Specify how the object files should be created from source files


# Specify the object files and executables that are generated
# and need to be removed to re-compile the whole thing
clean:
	rm -f *.o *.gch prog.exe
