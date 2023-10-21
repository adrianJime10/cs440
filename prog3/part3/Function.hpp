#include <iostream>
#include <memory>

namespace cs540{

  class BadFunctionCall : public std::exception{
    const char* what() const throw(){
      return "Error: Bad Function Call Thrown";
    }
  };

  template<typename T>
  class Function{

  };

  template<typename ResultType, typename ... ArgumentTypes>
  class Function<ResultType(ArgumentTypes...)>{
  public:

    class Callable{
    public:
      virtual ~Callable() = default;
      virtual ResultType Invoke(ArgumentTypes...) = 0;
    };

    template<typename T>
    class CallableDerived : public Callable{
    public:
      T typ;

      CallableDerived(const T& a) : typ(a){}
      ~CallableDerived() override = default;
      ResultType Invoke(ArgumentTypes... args) override{
        return typ(args...);
      }
    };

    //std::unique_ptr<Callable> callable;
    Callable* callable;

    Function(){
      callable = nullptr;
    }

    template<typename FunctionType>
    Function(FunctionType func){
      //callable = std::make_unique<CallableDerived<FunctionType>>(func);
	callable = new CallableDerived<FunctionType>(func);
    }

    Function(const Function &otherFunc){
      if(callable!=nullptr){
        //callable.release();
      }
      callable = otherFunc.callable;
    }

    Function& operator=(const Function &otherFunc){
      if(&otherFunc==this){
        return *this;
      }
      if(callable!=nullptr){
        //callable.release();
      }
      callable = otherFunc.callable;
      return *this;
    }

    ~Function(){
      //if(callable!=nullptr){
        //callable.release();
	//delete callable;
      //}
    }

    ResultType operator()(ArgumentTypes... arguments){
      if(callable!=nullptr){
        return callable->Invoke(arguments...);
      }
      throw BadFunctionCall();
    }

    explicit operator bool() const{
      if(callable!=nullptr){
        return true;
      }
      return false;
    }
  };

template<typename ResultType, typename... ArgumentTypes>
bool operator==(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t){
  return !f;
}

template<typename ResultType, typename... ArgumentTypes>
bool operator==(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f){
  return !f;
}

template<typename ResultType, typename... ArgumentTypes>
bool operator!=(const Function<ResultType(ArgumentTypes...)> &f, std::nullptr_t){
  return bool(f);
}

template<typename ResultType, typename... ArgumentTypes>
bool operator!=(std::nullptr_t, const Function<ResultType(ArgumentTypes...)> &f){
  return bool(f);
}

}
