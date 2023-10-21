#include <cstddef>
#include <iostream>
#include <mutex>
#include <pthread.h>
#include <atomic>

namespace cs540{


/*template<typename T>
void myDeleter(T *ptr){
	delete ptr;
	p = nullptr;
}*/

std::mutex mtx;
pthread_mutex_t lock;

class ControlBlock{
	public:

	std::atomic<int> refcount;
	//T* managedPtr;

	ControlBlock(){refcount=0; /*managedPtr = nullptr;*/}
	virtual ~ControlBlock(){}

	/*void deleter(){
		delete managedPtr;
		managedPtr = nullptr;
	}*/
	void increment(){ 
		//mtx.lock();
		if(this){
			//mtx.lock();
			refcount++;
			//mtx.unlock();
			//return refcount;
		}
		//mtx.unlock();
		//return 0;
	}
	void decrement(){
		//mtx.lock();
		if(this){
			//mtx.lock();
			refcount--;
			//mtx.lock();
			//pthread_mutex_lock(&lock);
			if(refcount ==0 && this != nullptr){
				delete this;
			}
			//pthread_mutex_unlock(&lock);
			//mtx.unlock();
			//return refcount;
		}
		//mtx.unlock();
		//return 0;
	}
};

template<typename T>
class ControlBlockDerived : public ControlBlock{
	public:

  T* managedPtr;

	ControlBlockDerived(T* ptr){ControlBlock(); managedPtr = ptr;}
	~ControlBlockDerived(){deleter();}

	void deleter(){
		delete managedPtr;
	}
};

template<typename T>
class SharedPtr{
	public:

	T* storedPtr;
	ControlBlock* helper;

	//Constructors
	SharedPtr(){ storedPtr = nullptr; helper = nullptr;}

	template<typename U> explicit SharedPtr(U *newptr){
		storedPtr = newptr;
		helper = new ControlBlockDerived<U>(newptr);
		helper->increment();
		//helper->deleter = ([](T* ptr) -> {delete ptr;});
		//helper->deleter = myDeleter;
		//helper->managedPtr = newptr;
	}

	/*void myDeleter(){
		delete storedPtr;
	}*/

	SharedPtr(const SharedPtr &p){
		pthread_mutex_lock(&lock);
		storedPtr = p.storedPtr;
		helper = p.helper;
		if(p!=nullptr){helper->increment();}
		pthread_mutex_unlock(&lock);
	}

	template<typename L>
	SharedPtr(const SharedPtr<L> &sp, T* p){
		pthread_mutex_lock(&lock);
		storedPtr = p;
		helper = sp.helper;
		helper->increment();
		pthread_mutex_unlock(&lock);
	}

	template<typename U>
	SharedPtr(const SharedPtr<U> &p){
		pthread_mutex_lock(&lock);
		storedPtr = static_cast<T*>(p.storedPtr);
		//helper = dynamic_cast<ControlBlock<T>* const>(p.helper);
		//helper = (ControlBlock<T>*) p.helper;
		//helper = dynamic_cast<T*> (p.helper);
		helper = p.helper;
		if(p!=nullptr){helper->increment();}
		pthread_mutex_unlock(&lock);
	}

	SharedPtr(SharedPtr &&p){
		pthread_mutex_lock(&lock);
		storedPtr = p.storedPtr;
		helper = p.helper;
		helper->increment();//INCREMENT THEN DECREMENT? MUTEX
		p.storedPtr = nullptr;
		p.helper = nullptr;
		if(helper!=nullptr){
		//pthread_mutex_lock(&lock);
		helper->decrement();
		//pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&lock);
		}
	}

	template<typename U>
	SharedPtr(SharedPtr<U> &&p){
		pthread_mutex_lock(&lock);
		storedPtr = static_cast<T*>(p.storedPtr);
		helper = p.helper;
		helper->increment();//INCREMENT THEN DECREMENT? MUTEX
		p.storedPtr = nullptr;
		p.helper = nullptr;
		if(helper!=nullptr){
		//pthread_mutex_lock(&lock);
		helper->decrement();
		//pthread_mutex_unlock(&lock);
		pthread_mutex_unlock(&lock);
		}
	}

	SharedPtr &operator=(const SharedPtr &p){
		pthread_mutex_lock(&lock);
		if(helper!=nullptr){
			//pthread_mutex_lock(&lock);
			helper->decrement();
			//pthread_mutex_unlock(&lock);
		}
		storedPtr = p.storedPtr;
		helper = p.helper;
		helper->increment();
		pthread_mutex_unlock(&lock);
		return *this;
	}

	template<typename U>
	SharedPtr<T> &operator=(const SharedPtr<U> &p){
		pthread_mutex_lock(&lock);
		if(helper!=nullptr){
			//pthread_mutex_lock(&lock);
			helper->decrement();
			//pthread_mutex_unlock(&lock);
		}
		storedPtr = p.storedPtr;
		helper = p.helper;
		helper->increment();
		pthread_mutex_unlock(&lock);
		return *this;
	}

	SharedPtr &operator=(SharedPtr &&p){
		pthread_mutex_lock(&lock);
		if(p!=nullptr){
			storedPtr = p.storedPtr;
			helper = p.helper;
		}
		p.storedPtr = nullptr;
		p.helper = nullptr;
		pthread_mutex_unlock(&lock);
		return *this;
	}

	template<typename U>
	SharedPtr &operator=(SharedPtr<U> &&p){
		pthread_mutex_lock(&lock);
		if(p!=nullptr){
			storedPtr = p.storedPtr;
			helper = p.helper;
		}
		p.storedPtr=nullptr;
		p.helper = nullptr;
		pthread_mutex_unlock(&lock);
		return *this;
	}

	~SharedPtr(){
		pthread_mutex_lock(&lock);
		if(helper!=nullptr){
		//pthread_mutex_lock(&lock);
		helper->decrement();
		//pthread_mutex_unlock(&lock);
		}
		pthread_mutex_unlock(&lock);
	}

	//Modifiers
	void reset(){
		pthread_mutex_lock(&lock);
		storedPtr = nullptr;
		if(helper!=nullptr){
			//pthread_mutex_lock(&lock);
			helper->decrement();
			//pthread_mutex_unlock(&lock);
			helper=nullptr;
		}
		pthread_mutex_unlock(&lock);
	}

	template<typename U> void reset(U *p){
		pthread_mutex_lock(&lock);
		storedPtr = p;
		if(helper!=nullptr){
			//pthread_mutex_lock(&lock);
			helper->decrement();
			//pthread_mutex_unlock(&lock);
		}
		helper = new ControlBlockDerived<U>(p);
		helper->increment();
		pthread_mutex_unlock(&lock);
	}

	//Observers
	T *get() const{
		return storedPtr;
	}

	T &operator*(){
		return (*storedPtr);
	}

	T *operator->(){
		return storedPtr;
	}

	explicit operator bool() const{
		if(storedPtr != nullptr){
			return true;
		}
		return false;
	}

};

//FREE FUNCTIONS
template<typename T1, typename T2>
bool operator==(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2){
	if(p1==nullptr && p2==nullptr){
		return true;
	}
	else if(p1.storedPtr == p2.storedPtr){
		return true;
	}
	return false;
}

template<typename T>
bool operator==(const SharedPtr<T> &p, std::nullptr_t n){
	if(!p){
		return true;
	}
	return false;
}

template<typename T>
bool operator==(std::nullptr_t n, const SharedPtr<T> &p){
	if(!p){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool operator!=(const SharedPtr<T1> &p1, const SharedPtr<T2> &p2){
	if(((p1.storedPtr == nullptr) && (p2.storedPtr!= nullptr)) || ((p2.storedPtr == nullptr) && (p1.storedPtr!=nullptr))){
		return true;
	}
	else if(p1.storedPtr != p2.storedPtr){
		return true;
	}
	return false;
}

template<typename T>
bool operator!=(const SharedPtr<T> &p, std::nullptr_t n){
	if(!p){
		return false;
	}
	return true;
}

template<typename T>
bool operator!=(std::nullptr_t n, const SharedPtr<T> &p){
	if(!p){
		return false;
	}
	return true;
}

template<typename T, typename U>
SharedPtr<T> static_pointer_cast(const SharedPtr<U> &sp){
	return SharedPtr<T>(sp, static_cast<T*>(sp.storedPtr));
}

template<typename T, typename U>
SharedPtr<T> dynamic_pointer_cast(const SharedPtr<U> &sp){
	return SharedPtr<T>(sp, dynamic_cast<T*>(sp.storedPtr));
}

}
