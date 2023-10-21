#include <typeindex>
#include <map>
#include <iostream>
#include <memory>

/*
 * Implement a TypeMap that allows different handlers to be registered
 * for different types.  The TypeMap can then be called with a value, and
 * asked to handle it.  This should cause dispatch to the registered
 * handler.
 *
 * Hint:  First create a map to map from type_info objects to handlers.
 * Store the handler in the map when it is registered.  When a value needs
 * to be handled, wrap it in a common Value base class, hiding the value
 * inside a derived class template.  Pass the Value to the handler.
 *
 * A suggested, but not required, definition of the base TypeHandler class is:
 *
 *     class TypeHandler {
 *         public:
 *             virtual void handle(std::shared_ptr<Value> v) = 0;
 *     };
 *
 * You will need to implement int_Handler and A_Handler.  Your implementations
 * will need to confirm that the correct handler was called with the correct
 * value, but can otherwise be very simple.
 *
 * You must be able to add new types without changing any existing code.  For
 * example, I must be able to write a B_handler to handle a class B without
 * changing any of the code that you write.  Failure to follow this requirement
 * will limit your maximum credit to 50%.
 */

struct A {
    double x, y;
};

struct TypeNotRegistered {};

//class TypeMap{};

class Value{
	Value(){};
};

template<typename T>
class ValueDerived: public Value{
	T val;

	ValueDerived(T valu): val(valu){};
};

class TypeHandler{
	public:
	virtual void handle(std::shared_ptr<Value> v)=0;
};

class int_Handler:public TypeHandler{
	public:
	
	void handle(std::shared_Ptr<Value> v){
		ValueDerived<int> neww(*v);
	}
};

class A_Handler:public TypeHandler{
	public:
	
	void handle(std::shared_Ptr<Value> v){
		ValueDerived<A> neww(*v);
	}
};

class TypeMap{
	public:

	std::map<std::type_index(), TypeHandler> mappy;

	template<typename T>
	void handle(T a){
		mappy[a].handle(std::make_shared<T> &a);
	}

	template<typename T, typename T2>
	void registr(std::type_index(typeid(T)) a, std::shared_ptr<T2> b){
		mappy.insert({a, b});
	}
};

// PUT YOUR CODE HERE.

int
main() {

    TypeMap tm;
    // Registers a handler for a type.
    tm.registr(typeid(int), std::make_shared<int_Handler>());
    tm.registr(typeid(A), std::make_shared<A_Handler>());

    // Calls the appropriate type handler with the given value.
    tm.handle(2); // Calls int_Handler.
    tm.handle(A{1.1, 2.2}); // Calls A_handler.
    try {
        tm.handle(1.1);
    } catch (const TypeNotRegistered &e) {
        std::cerr << "double not registered." << std::endl;
    }
}
