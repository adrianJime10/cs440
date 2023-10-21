#include <iostream>
#include <initializer_list>
#include <chrono>

namespace cs540{

class Array{
  public:

    size_t size;
    MyInt *arr;

    Array(std::initializer_list<MyInt> ilist){
      size = ilist.size();
      arr = new MyInt[size];
      int i = 0;
      for(auto it = ilist.begin(); it!=ilist.end(); it++){
        arr[i] = (*it);
        i++;
      }
    }

    Array(const Array &arr2){
      size = arr2.size;
      arr = new MyInt[size];

      for(size_t i = 0; i<arr2.size; i++){
        arr[i] = arr2.arr[i];
      }
    }

    Array(Array &&arr2){
      size = arr2.size;
      arr = arr2.arr;
      arr2.arr = nullptr;
    }

    Array& operator=(Array &&arr2){
      if(this == &arr2){
        return *this;
      }
      size = arr2.size;
      if(arr){
        delete[] arr;
      }
      arr = arr2.arr;
      arr2.arr = nullptr;
      return *this;
    }

    Array& operator=(const Array &arr2){
      if(this == &arr2){
        return *this;
      }
      size = arr2.size;
      if(arr){
        delete[] arr;
      }
      arr = new MyInt[size];

      for(size_t i=0; i<arr2.size; i++){
        arr[i] = arr2.arr[i];
      }
      return *this;
    }

    ~Array(){
      if(arr){
        delete[] arr;
      }
    }

    friend std::ostream& operator<<(std::ostream& os, const Array& MyArr);

    //Tester functions
    //Static makes functions 'independent of any particular object of the class'
    static void copyConstructorTest(Array &testArr){
      for(int i=0; i<1000000; i++){
        Array tester{testArr};
      }
    }

    static void copyAssignmentTest(Array &testArr){
      for(int i=0; i<1000000; i++){
        Array tester{1,2,3};
        tester = testArr;
      }
    }

    static void moveConstructorTest(Array &testArr){
      for(int i=0; i<1000000; i++){
        Array tester{std::move(testArr)};
      }
    }

    static void moveAssignmentTest(Array &testArr){
      for(int i=0; i<1000000; i++){
        Array tester{1,2,3};
        tester = std::move(testArr);
      }
    }

    static void move_performance_test(){
      std::cout << "--------------- TESTING IN PROGRESS -----------------" << std::endl;
      std::cout << "---> Testing copy constructor..." << std::endl;

      Array test{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};

      auto t1 = std::chrono::high_resolution_clock::now();
      copyConstructorTest(test);
      auto t2 = std::chrono::high_resolution_clock::now();

      auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
      std::cout << "Completed in " << duration << " microseconds" << std::endl;

      std::cout << "---> Testing copy assignment..." <<std::endl;

      t1 = std::chrono::high_resolution_clock::now();
      copyAssignmentTest(test);
      t2 = std::chrono::high_resolution_clock::now();

      duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
      std::cout << "Completed in " << duration << " microseconds" << std::endl;

      std::cout << "--> Testing move constructor..." << std::endl;

      t1 = std::chrono::high_resolution_clock::now();
      moveConstructorTest(test);
      t2 = std::chrono::high_resolution_clock::now();

      duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
      std::cout << "Completed in " << duration << " microseconds" << std::endl;

      std::cout << "---> Testing move assignment..." << std::endl;

      t1 = std::chrono::high_resolution_clock::now();
      moveAssignmentTest(test);
      t2 = std::chrono::high_resolution_clock::now();

      duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
      std::cout << "Completed in " << duration << " microseconds" << std::endl;
    }
};

std::ostream& operator<<(std::ostream& os, const Array& MyArr){
	for(size_t i = 0 ; i<MyArr.size-1;i++){
		os << MyArr.arr[i] << ", ";
	}
	os << MyArr.arr[MyArr.size-1];
	return os;
}

}
