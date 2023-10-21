#include <initializer_list>
#include <utility>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <stdexcept>

namespace cs540{

template <typename T>
class Node{
	public:
	Node(T, int);
	Node(int);
	Node(const Node<T> &);
	~Node(){delete next; delete prev;}

	int lev;
	Node<T> **next;
	Node<T> **prev;
	T* value;
	bool sent = false;
};

template <typename T>
Node<T>::Node(const Node<T> &other){
	*value = other->value;
	lev=other.lev;
	sent = other.sent;
	next = new Node<T>*[lev+1];
	prev = new Node<T>*[lev+1];
	memset(next, 0, sizeof(Node<T>*)*(lev+1));
	memset(prev, 0, sizeof(Node<T>*)*(lev+1));
}

template <typename T>
Node<T>::Node(const T val, int level){
	value = const_cast<T*>(&val);
	lev=level;
	next = new Node<T>*[level+1];
	prev = new Node<T>*[level+1];
	memset(next, 0, sizeof(Node<T>*)*(level+1));
	memset(prev, 0, sizeof(Node<T>*)*(level+1));
}

template <typename T>
Node<T>::Node(int level){
	lev=level;
	next = new Node<T>*[level+1];
	prev = new Node<T>*[level+1];
	memset(next, 0, sizeof(Node<T>*)*(level+1));
	memset(prev, 0, sizeof(Node<T>*)*(level+1));
}

template <typename T1, typename T2>
class Map{
	public:
	class Iterator{
		public:
		Node<std::pair<const T1,T2>> *it;

		Iterator(){}
		Iterator(const Iterator &iter){
			it = iter.it;
		}
		~Iterator(){/*delete it;*/}
		//Iterator& operator=(const Iterator &);
		Iterator &operator++();

		Iterator &operator=(const Iterator&);
	
		Iterator operator++(int);
	
		Iterator& operator--();
	
		Iterator operator--(int);
	
		std::pair<const T1,T2> &operator*() const;

		bool operator==(const typename Map<T1,T2>::Iterator &i2);

		bool operator!=(const typename Map<T1,T2>::Iterator &i2);

		bool operator==(const typename Map<T1,T2>::ConstIterator &i2);

		bool operator!=(const typename Map<T1,T2>::ConstIterator &i2);
	
		std::pair<const T1,T2> *operator->() const;
	
	};

	class ConstIterator{
		public:
		Node<std::pair<const T1,T2>> *it;
	
		ConstIterator(){}
		ConstIterator(const ConstIterator &iter){
			it = iter.it;
		}
		~ConstIterator(){/*delete it;*/}
		//Iterator& operator=(const Iterator &);
		ConstIterator &operator++();
	
		ConstIterator operator++(int);
	
		ConstIterator& operator--();
		
		ConstIterator operator--(int);
		
		const std::pair<const T1,T2> &operator*() const;
	
		const std::pair<const T1,T2> *operator->() const;

		bool operator==(const typename Map<T1,T2>::ConstIterator &i2);

		bool operator!=(const typename Map<T1,T2>::ConstIterator &i2);

		bool operator==(const typename Map<T1,T2>::Iterator &i2);
	
		bool operator!=(const typename Map<T1,T2>::Iterator &i2);
	};

	class ReverseIterator{
		public:
		Node<std::pair<const T1,T2>> *it;
	
		ReverseIterator(){}
		ReverseIterator(const ReverseIterator &iter){
			it=iter.it;
		};
		~ReverseIterator(){/*delete it;*/}
		//Iterator& operator=(const Iterator &);
		ReverseIterator &operator++();
	
		ReverseIterator operator++(int);
	
		ReverseIterator& operator--();
	
		ReverseIterator operator--(int);
	
		const std::pair<const T1,T2> &operator*() const;
	
		const std::pair<const T1,T2> *operator->() const;

		bool operator==(const typename Map<T1,T2>::ReverseIterator &i2);

		bool operator!=(const typename Map<T1,T2>::ReverseIterator &i2);

	};

	Map();
	Map(const Map &);
	Map(std::initializer_list<std::pair<const T1, T2>>);
	~Map(){delete sentinel;}
	Node<std::pair<const T1,T2>>* sentinel;
	Node<std::pair<const T1,T2>>* header;
	int maxlvl=0;
	float frac =.5;
	int currlvl=0;

	Iterator begin();
	Iterator end();
	Iterator find(const T1 &);
	void erase(Iterator pos);
	T2 &at(const T1 &);
	size_t size() const;
	T2 &operator[](const T1 &);
	int rnglevel();
	void erase(const T1 &);
	std::pair<Iterator, bool> insert(const std::pair<const T1, T2> &);
	bool empty() const;
	template<typename IT_T>
	void insert( IT_T iter_begin, IT_T iter_end);
	bool operator==(const Map &);
	bool operator!=(const Map &);
	bool operator<(const Map &);
	ConstIterator begin() const;
	ConstIterator end() const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	void clear();
};

template <typename T1, typename T2>
Map<T1,T2>::Map(const Map &other){
	sentinel = new Node<std::pair<const T1,T2>>(0);
	sentinel->next[0]=sentinel;
	sentinel->prev[0]=sentinel;
	sentinel->sent = true;
	for(auto it = other.sentinel->next[0]; it!=other.sentinel; it=it->next[0]){
		insert(*(it->value));
	}
	
}

template <typename T1, typename T2>
Map<T1,T2>::Map(){
	//std::cout << "im here\n";
	sentinel = new Node<std::pair<const T1,T2>>(0);
	sentinel->next[0]=sentinel;
	sentinel->prev[0]=sentinel;
	sentinel->sent = true;
	//std::cout << "now im here\n";
}

template<typename T1, typename T2>
typename Map<T1,T2>::Iterator Map<T1,T2>::begin(){
	Iterator resultIt;
	resultIt.it = sentinel->next[0];
	return resultIt;
}

template<typename T1, typename T2>
typename Map<T1,T2>::Iterator Map<T1,T2>::end(){
	Iterator resultIt;
	resultIt.it = sentinel;
	return resultIt;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator Map<T1,T2>::begin() const{
	ConstIterator resultIt;
	resultIt.it = sentinel->next[0];
	return resultIt;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator Map<T1,T2>::end() const{
	ConstIterator resultIt;
	resultIt.it = sentinel;
	return resultIt;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator Map<T1,T2>::rend(){
	ReverseIterator resultIt;
	resultIt.it = sentinel;
	return resultIt;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator Map<T1,T2>::rbegin(){
	ReverseIterator resultIt;
	resultIt.it = sentinel->prev[0];
	return resultIt;
}

template<typename T1, typename T2>
void Map<T1,T2>::clear(){
	Node<std::pair<const T1,T2>> *current = sentinel;
	current = current->next[0];
	while(current!=sentinel){
		current->prev[0]->next[0]=current->next[0];
		current->next[0]->prev[0] = current->prev[0];
		auto temp = current->next[0];
		delete current;
		current = temp;
	}
	return;
}

template<typename T1, typename T2>
void Map<T1,T2>::erase(const T1 &key){
	Node<std::pair<const T1,T2>> *current = sentinel;
	Node<std::pair<const T1,T2>> *update[maxlvl+1];
	memset(update, 0, sizeof(Node<std::pair<const T1,T2>>*)*(maxlvl+1));
	//std::cout << "\n eyyyy " << current->next[0]->value->first;
	//std::cout << "\n eyyyy " << current->next[0]->next[0]->value->first;
	if(!empty()){
		//std::cout << "\nhi\n";
		for(int i=currlvl;i>-1;i--){
			while((current->next[i]->sent == false) && (current->next[i]->value->first < key)){
				/*if(current->next[i]->value->first == element.first){
					return;
				}*/
				//std::cout << "insert 3\n";
				current = current->next[i];
				if(current->next[i]->sent == true){
					update[i] = current;
					break;
				}
			update[i] = current;
			}
		}
		current = current->next[0];
		//std::cout << current->value->first << "hithererere\n";
		if(current->sent == false && current->value->first == key){
			for(int i=0;i<=maxlvl;i++){
				update[i]->next[i]=current->next[i];
				current->next[i]->prev[i] = update[i];
				delete current;
			}
			return;
		}else{
			throw std::out_of_range("Out of range error\n");
		}
	}
}

template<typename T1, typename T2>
void Map<T1,T2>::erase(Iterator pos){
	Node<std::pair<const T1,T2>> *current = sentinel;
	Node<std::pair<const T1,T2>> *update[maxlvl+1];
	memset(update, 0, sizeof(Node<std::pair<const T1,T2>>*)*(maxlvl+1));
	//std::cout << "\n eyyyy " << current->next[0]->value->first;
	//std::cout << "ooooooooooo\n";
	//std::cout << "\n eyyyy " << pos.it->value->first;
	if(!empty()){
		//std::cout << "\nhi\n";
		for(int i=currlvl;i>-1;i--){
			while((current->next[i]->sent == false) && (current->next[i] !=pos.it)){
				/*if(current->next[i]->value->first == element.first){
					return;
				}*/
				//std::cout << "insert 3\n";
				current = current->next[i];
				if(current->next[i]->sent == true){
					//std::cout << "woah\n";
					update[i] = current;
					break;
				}
			update[i] = current;
			}
		}
		current = current->next[0];
		//std::cout << current->value->first << "hithererere\n";
		if(current->sent == false && current == pos.it){
			for(int i=0;i<=maxlvl;i++){
				update[i]->next[i]=current->next[i];
				current->next[i]->prev[i] = update[i];
				delete current;
			}
			return;
		}else{
			throw std::out_of_range("Out of range error\n");
		}
	}
}

template<typename T1, typename T2>
typename Map<T1,T2>::Iterator Map<T1,T2>::find(const T1 &key){
	Node<std::pair<const T1,T2>> *current = sentinel;
	for(int i=currlvl;i>-1;i--){
		if(current->next[i]->sent==false){
			//std::cout << "yea\n";
			//std::cout << (current->next[i]->value->first) << "\n";
			if(current->next[i]->value->first == key){
				Iterator resultIt;
				resultIt.it = current->next[i]; 
				return resultIt;
			}
			while((current->next[i]->sent == false) && (current->next[i]->value->first < key)){
				//std::cout << "insert 3\n";
				current = current->next[i];
				if(current->next[i]->sent == true){
					break;
				}
				if(current->value->first == key){
					Iterator resultIt;
					resultIt.it = current; 
					//std::cout << "Here1\n";
					return resultIt;
				}
			}
			if(current->next[i]->value->first == key){
				Iterator resultIt;
				resultIt.it = current->next[i]; 
				//std::cout << resultIt.it->value->first << " Here2\n";
				//std::cout << resultIt.it << " : " << current->next[i];
				//std::cout << (resultIt.it == current->next[i]);
				return resultIt;
			}
		}
	}
	return end();
	//return;
}

template<typename T1, typename T2>
T2& Map<T1,T2>::at(const T1 &key){
	try{
	Node<std::pair<const T1,T2>> *current = sentinel;
	for(int i=currlvl;i>-1;i--){
		if(current->next[i]->sent==false){
			//std::cout << "yea\n";
			//std::cout << (current->next[i]->value->first) << "\n";
			if(current->next[i]->value->first == key){
				return current->next[i]->value->second;
			}
			while((current->next[i]->sent == false) && (current->next[i]->value->first < key)){
				//std::cout << "insert 3\n";
				current = current->next[i];
				if(current->next[i]->sent == true){
					break;
				}
				if(current->value->first == key){
					return current->next[i]->value->second;
				}
			}
			if(current->next[i]->value->first == key){
				return current->next[i]->value->second;
			}
		}
	}
	}catch(std::out_of_range){
		std::cerr << "Out of Range error\n";
	}
	//return;
}

template <typename T1, typename T2>
Map<T1,T2>::Map(std::initializer_list<std::pair<const T1, T2>> ilist){
	//std::cout <<"wait;\n";
	int count = 0;
	sentinel = new Node<std::pair<const T1,T2>>(0);
	sentinel->next[0]=sentinel;
	sentinel->prev[0]=sentinel;
	sentinel->sent = true;
	for(auto it=ilist.begin(); it!=ilist.end();it++){
		count ++;
		//std::cout << count << "\n";
		insert(*it);
		//std::cout<<sentinel->next[0]->value->first << "ayayayayayay\n";
	}
}

/*template <typename T1, typename T2>
Map<T1,T2>::~Map(){
}*/

template <typename T1, typename T2>
T2& Map<T1,T2>::operator[](const T1 &element){
	for(auto it = sentinel->next[0]; it!=sentinel; it = it->next[0]){
		if(it->value->first == element){
			return it->value->second;
		}
	}
	T2 t2;
	std::pair<const T1, T2> result (element,t2);
	std::pair<Iterator, bool> p1(insert(result));
	for(auto it = sentinel->next[0]; it!=sentinel; it = it->next[0]){
		if(it->value->first == element){
			return it->value->second;
		}
	}
	return p1.first.it->value->second;
}

template <typename T1, typename T2>
size_t Map<T1,T2>::size() const{
	size_t count=0;
	for(auto it = sentinel->next[0]; it!=sentinel; it= it->next[0]){
		count++;
	}
	return count;
}

template <typename T1, typename T2>
bool Map<T1,T2>::empty() const{
	if(sentinel->next[0] == sentinel){
		return true;
	}
	return false;
}

template <typename T1, typename T2>
std::pair<typename Map<T1,T2>::Iterator, bool> Map<T1,T2>::insert(const std::pair<const T1,T2> &element){
	//std::cout << "insert 1\n";
	//std::cout << "eyyyyyyy" << sentinel->next[0]->value->first << " :ya\n";
	Node<std::pair<const T1,T2>> *current = sentinel;
	Node<std::pair<const T1,T2>> *update[maxlvl+1];
	memset(update, 0, sizeof(Node<std::pair<const T1,T2>>*)*(maxlvl+1));
	//std::cout << "insert 2\n";
	Iterator iter;
	//bool check = current->next[0]->value->first < element.first;
	//std::cout << "insert 3\n";
	update[0]=sentinel;

	/*if(!empty()){
	for(size_t i=0;i<size();i++){
		std::cout << "insert 3\n";
		if(current->next[0]->sent == false){
			if(element.first == current->next[0]->value->first){
				return;
			}
		}
	}
	}*/
	if((current->next[0]->sent==true)){
		int rnglvl = rnglevel();
		update[0] = sentinel->next[0];
		//std::cout << "insert 3\n";
		if(rnglvl > currlvl){
			for(int i= currlvl+1;i<rnglvl+1;i++){
				update[i] = sentinel->next[0];
			}
			Node<std::pair<const T1,T2>> **newNext = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			Node<std::pair<const T1,T2>> **newPrev = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			for(int i=0;i<currlvl+1;i++){
				newNext[i]=sentinel->next[i];
			}
			for(int i=0;i<currlvl+1;i++){
				newPrev[i]=sentinel->prev[i];
				//std::cout << currlvl << "\n";
			}
			delete[] sentinel->next;
			sentinel->next = newNext;
			delete[] sentinel->prev;
			sentinel->prev = newPrev;
			currlvl=rnglvl;
		}
		//std::cout << "insert 3\n";
		Node<std::pair<const T1, T2>>* newNode = new Node<std::pair<const T1, T2>>(/*element,*/rnglvl);
		//std::cout << "insert 3\n";
		//std::pair<T1,T2> cop (element);
		newNode->value = const_cast<std::pair<const T1,T2>*>(&element);//?????????????????
		for(int i=0;i<=rnglvl;i++){
			newNode->next[i] = update[i]->next[i];
			update[i]->next[i] = newNode;
			//std::cout << "insert 3\n";
			newNode->next[i]->prev[i] = newNode;
			//std::cout << "insert 4\n";
			newNode->prev[i]=update[i];
		}
		iter.it = newNode;
		std::pair<Iterator, bool> p2(iter, true);
		return p2;
	}else{

	//std::cout << "insert 5\n";

	for(int i=currlvl;i>-1;i--){
		while((current->next[i]->sent == false) && (current->next[i]->value->first < element.first)){
			if(current->next[i]->value->first == element.first){
				iter.it = current->next[i];
				std::pair<Iterator, bool> p2(iter,false);
				return p2;
			}
			//std::cout << "insert 3\n";
			current = current->next[i];
			if(current->next[i]->sent == true){
				//std::cout << "hmmmm\n";
				update[i] = current;
				break;
			}
		update[i] = current;
		}
	}
	//std::cout << "insert 6\n";
	//current = current->next[0];
	if(current == sentinel){
		int rnglvl = rnglevel();
		if(rnglvl > currlvl){
			for(int i= currlvl+1;i<rnglvl+1;i++){
				update[i] = sentinel->next[0];
			}
			Node<std::pair<const T1,T2>> **newNext = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			Node<std::pair<const T1,T2>> **newPrev = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			for(int i=0;i<currlvl+1;i++){
				newNext[i]=current->next[i];
			}
			for(int i=0;i<currlvl+1;i++){
				newPrev[i]=current->prev[i];
				//std::cout << currlvl << "\n";
			}
			delete[] current->next;
			current->next = newNext;
			delete[] current->prev;
			current->prev = newPrev;
			currlvl=rnglvl;
		}
		Node<std::pair<const T1, T2>>* newNode = new Node<std::pair<const T1, T2>>(/*element,*/rnglvl);
		newNode->value = const_cast<std::pair<const T1,T2>*>(&element);
		//std::pair<T1,T2> cop (element);
		//newNode->value = (&cop);//?????????????????
		//newNode->value.second = element.second;
		//std::cout << "rnglvl" << rnglvl << "\n";
		//std::cout << "currlvl" << currlvl << "\n";
		//std::cout << newNode->value->first << "first\n";
		//std::cout << element.first << "first\n";
		/*for(int i=0;i<=20;i++){
			std::cout << i <<"\n";
			update[i]->next[i];
		}*/
		for(int i=0;i<=rnglvl;i++){
			//std::cout << "insert here\n";
			newNode->next[i] = update[i]->next[i];
			update[i]->next[i] = newNode;
			newNode->next[i]->prev[i] = newNode;
			newNode->prev[i]=update[i];
		}
		iter.it = newNode;
		std::pair<Iterator, bool> p2(iter, true);
		return p2;
	}else if(current->next[0] == sentinel || !(current->value->first == element.first)){
		int rnglvl = rnglevel();
		if(rnglvl > currlvl){
			for(int i= currlvl+1;i<rnglvl+1;i++){
				update[i] = sentinel->next[0];
			}
			Node<std::pair<const T1,T2>> **newNext = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			Node<std::pair<const T1,T2>> **newPrev = new Node<std::pair<const T1,T2>>*[rnglvl+1];
			for(int i=0;i<currlvl+1;i++){
				newNext[i]=current->next[i];
			}
			for(int i=0;i<currlvl+1;i++){
				newPrev[i]=current->prev[i];
				//std::cout << currlvl << "\n";
			}
			delete[] current->next;
			current->next = newNext;
			delete[] current->prev;
			current->prev = newPrev;
			currlvl=rnglvl;
		}
		Node<std::pair<const T1, T2>>* newNode = new Node<std::pair<const T1, T2>>(/*element,*/rnglvl);
		//std::pair<T1,T2> cop (element);
		newNode->value = const_cast<std::pair<const T1,T2>*>(&element);
		//newNode->value = (&cop);//?????????????????
		//newNode->value.second = element.second;
		//std::cout << "rnglvl" << rnglvl << "\n";
		//std::cout << "currlvl" << currlvl << "\n";
		//std::cout << newNode->value->first << newNode->value->second << " second\n";
		//std::cout << element.first << element.second << " second\n";
		/*for(int i=0;i<=20;i++){
			std::cout << i <<"\n";
			update[i]->next[i];
		}*/
		for(int i=0;i<=rnglvl;i++){
			//std::cout << "insert there\n";
			newNode->next[i] = update[i]->next[i];
			update[i]->next[i] = newNode;
			newNode->next[i]->prev[i] = newNode;
			newNode->prev[i]=update[i];
		}
		iter.it = current;
		std::pair<Iterator, bool> p2(iter,true);	
		return p2;
	}
}	
		iter.it = current;
		std::pair<Iterator, bool> p2(iter,true);	
		return p2;
}

template<typename T1, typename T2>
template<typename IT_T>
void Map<T1,T2>::insert( IT_T iter_begin, IT_T iter_end){
	for(auto iter = iter_begin; iter!= iter_end; iter++){
		insert(*iter);
	}
}

template <typename T1, typename T2>
int Map<T1,T2>::rnglevel(){
	float random = (float)rand()/RAND_MAX;
	int rlvl = 0;
	while(random < frac && rlvl < maxlvl){
		rlvl++;
		random = (float)rand()/RAND_MAX;
	}
	return rlvl;
}

template <typename T1, typename T2>
bool Map<T1,T2>::operator==(const Map &m2){
	if(size()==m2.size()){
		auto it1=begin();
		auto it2=m2.begin();
		for(; it1!= end(); (it1.it =it1.it->next[0]) && (it2.it=it2.it->next[0])){
			//std::cout << "Original first: " << it1.it->value->first << " second: " << it1.it->value->second << "\n";
			//std::cout << "Copy first: " << it2.it->value->first << " second: " << it2.it->value->second << "\n";
			if(!(it1.it->value == it2.it->value)){
				return false;
			}
		}
		return true;
	}else{
		return false;
	}
}

template <typename T1, typename T2>
bool Map<T1,T2>::operator<(const Map &m2){
	auto it1=begin();
	auto it2=m2.begin();
	for(; it1!= end() && it2!=m2.end(); (it1.it =it1.it->next[0]) && (it2.it=it2.it->next[0])){
		
		//std::cout << "Original first: " << it1.it->value->first << " second: " << it1.it->value->second << "\n";
		//std::cout << "Copy first: " << it2.it->value->first << " second: " << it2.it->value->second << "\n";
		if((it1.it->value < it2.it->value)){
			return true;
		}else if(it1.it->value > it2.it->value){
			return false;
		}
	}
	return false;
}

template <typename T1, typename T2>
bool Map<T1,T2>::operator!=(const Map &m2){
	return !(*this==m2);
}

template<typename T1,typename T2>
typename Map<T1,T2>::Iterator& Map<T1,T2>::Iterator::operator=(const Map<T1,T2>::Iterator &iter){
	it = iter.it;
	return *this;
}

template<typename T1,typename T2>
typename Map<T1,T2>::Iterator& Map<T1,T2>::Iterator::operator++(){
	if(it){
		it = it->next[0];
	}
	return *this;
}

template<typename T1,typename T2>
typename Map<T1,T2>::Iterator Map<T1,T2>::Iterator::operator++(int){
	Iterator temp;
	temp.it = it;
	if(it){
		it = it->next[0];
	}
	return temp;
}

template<typename T1,typename T2>
typename Map<T1,T2>::Iterator& Map<T1,T2>::Iterator::operator--(){
	if(it){
		it = it->prev[0];
	}
	return *this;
}

template<typename T1, typename T2>
typename Map<T1,T2>::Iterator Map<T1,T2>::Iterator::operator--(int){
	Iterator temp;
	temp.it = it;
	if(it){
		it = it->prev[0];
	}
	return temp;
}

template<typename T1,typename T2>
std::pair<const T1,T2>& Map<T1,T2>::Iterator::operator*() const{
	return *(it->value);
}

template<typename T1, typename T2>
std::pair<const T1,T2>* Map<T1,T2>::Iterator::operator->() const{
	return it->value;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator& Map<T1,T2>::ConstIterator::operator++(){
	if(it){
		it = it->next[0];
	}
	return *this;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator Map<T1,T2>::ConstIterator::operator++(int){
	ConstIterator temp;
	temp.it = it;
	if(it){
		it = it->next[0];
	}
	return temp;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator& Map<T1,T2>::ConstIterator::operator--(){
	if(it){
		it = it->prev[0];
	}
	return *this;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ConstIterator Map<T1,T2>::ConstIterator::operator--(int){
	ConstIterator temp;
	temp.it = it;
	if(it){
		it = it->prev[0];
	}
	return temp;
}

template<typename T1, typename T2>
const std::pair<const T1,T2>& Map<T1,T2>::ConstIterator::operator*() const{
	return *(it->value);
}

template<typename T1, typename T2>
const std::pair<const T1,T2>* Map<T1,T2>::ConstIterator::operator->() const{
	return it->value;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator& Map<T1,T2>::ReverseIterator::operator++(){
	if(it){
		it = it->prev[0];
	}
	return *this;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator Map<T1,T2>::ReverseIterator::operator++(int){
	ReverseIterator temp;
	temp.it = it;
	if(it){
		it = it->prev[0];
	}
	return temp;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator& Map<T1,T2>::ReverseIterator::operator--(){
	if(it){
		it = it->next[0];
	}
	return *this;
}

template<typename T1, typename T2>
typename Map<T1,T2>::ReverseIterator Map<T1,T2>::ReverseIterator::operator--(int){
	ReverseIterator temp;
	temp.it=it;
	if(it){
		it = it->next[0];
	}
	return temp;
}

template<typename T1, typename T2>
const std::pair<const T1,T2>& Map<T1,T2>::ReverseIterator::operator*() const{
	return *(it->value);
}

template<typename T1, typename T2>
const std::pair<const T1,T2>* Map<T1,T2>::ReverseIterator::operator->() const{
	return it->value;
}

template<typename T1, typename T2>
bool Map<T1,T2>::Iterator::operator==(const typename Map<T1,T2>::Iterator &i2){
	if(it == i2.it){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool Map<T1,T2>::Iterator::operator!=(const typename Map<T1,T2>::Iterator &i2){
	if(it == i2.it){
		return false;
	}
	return true;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ConstIterator::operator==(const typename Map<T1,T2>::ConstIterator &i2){
	if(it == i2.it){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ConstIterator::operator!=(const typename Map<T1,T2>::ConstIterator &i2){
	if(it == i2.it){
		return false;
	}
	return true;
}

template<typename T1, typename T2>
bool Map<T1,T2>::Iterator::operator==(const typename Map<T1,T2>::ConstIterator &i2){
	if(it == i2.it){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool Map<T1,T2>::Iterator::operator!=(const typename Map<T1,T2>::ConstIterator &i2){
	if(it == i2.it){
		return false;
	}
	return true;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ConstIterator::operator==(const typename Map<T1,T2>::Iterator &i2){
	if(it == i2.it){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ConstIterator::operator!=(const typename Map<T1,T2>::Iterator &i2){
	if(it == i2.it){
		return false;
	}
	return true;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ReverseIterator::operator==(const typename Map<T1,T2>::ReverseIterator &i2){
	if(it == i2.it){
		return true;
	}
	return false;
}

template<typename T1, typename T2>
bool Map<T1,T2>::ReverseIterator::operator!=(const typename Map<T1,T2>::ReverseIterator &i2){
	if(it == i2.it){
		return false;
	}
	return true;
}

}
