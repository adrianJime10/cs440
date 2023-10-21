#include <iostream>

/*
 * Write a variadic template class named Emitter so that the below compiles and
 * outputs the correct output.  Other than adding Emitter and possibly helper
 * classes or functions, don't change any other code.
 *
 * Hint: Use recursive class templates.  Recurse either by nesting or in the
 * base class.
 */

// PUT Emitter here.  You are not allowed to modify or add to anything below.

template<typename T>
class Helper{
	public:
	T firstOne;
	Helper(T first) : firstOne(first){}
	
};

template<typename... args>
class Emitter{};

template<typename T, typename... args>
class Emitter<T, args...> : public Emitter<args...>{
	public:
	T firstOne;
	Emitter<args...> helpme;

	Emitter(){}

	Emitter(T first, args... argss) : firstOne(first), /*Emitter<args...>*/helpme(argss...){}
	/*Emitter(T first, args... argss){
		firstOne = [&, first](){};
		helpme(argss...);
	}*/

	friend std::ostream &operator<<(std::ostream &os, Emitter& a){
		//if(){
		//NEED TO RECURSE!!!!!!!!
		os << a.firstOne << " " << a.helpme.firstOne << " " << a.helpme.helpme.firstOne;
		//}
		return os /*<< a.firstOne << " " << a.helpme.firstOne*/;
	}
	Emitter print(Emitter& b){
		return b.helpme;
	}
};

class A {
    public:
        friend std::ostream &operator<<(std::ostream &os, const A &) {
            return os << "A";
        }
};

struct B {
    friend std::ostream &operator<<(std::ostream &os, const B &) {
        return os << "B";
    }
};

int
main() {

    int i = 111;
    double x = 3.14;
    A a;

    Emitter<int, double, A> emitter(i, x, a);

    // Below should output "111 3.14 A".
    std::cout << emitter << std::endl;

    // Variables should be "captured" by reference, so that when you change
    // the variable, the output changes.
    x = 0.567;
    // Should now output "111 0.567 A".
    std::cout << emitter << std::endl;

    // Should be able to handle any number and type of variables.
    double y = 0.1234;
    B b;
    Emitter<int, double, B, double> emitter2(i, x, b, y);
    // Should output "111 0.567 B 0.1234".
    std::cout << emitter2 << std::endl;
}
