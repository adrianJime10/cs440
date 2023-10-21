#ifndef CS540_LIST_HPP
#define CS540_LIST_HPP



#include <assert.h>
#include <utility>
#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
/*
Hints: 
1) Doubly linked is easier to implement. 
2) Delegate logic to helper classes if possible
*/

template <typename T>
class List {
    private:
 	// Add necessary helper classes
	class Node{
		public:
		Node(T val){
			//value = new T();
			*value = val;
		};
		Node(){};
		Node(const List<T>::Node &nod){
			next = nod.next;
			prev = nod.prev;
			*value = *(nod.value);
		};
		~Node(){
			delete value;
		};
		Node& operator=(List<T>::Node nod){
			value = nod.value;
			next = nod.next;
			prev = nod.prev;
		}

		/*bool operator!=(List<T>::Node nod){
			if(*value == *(nod.value){

			}
		}*/

		T* value;
		Node *next;
		Node *prev;
		
	};
    public:
        class Iterator {
// Add the necessary methods here for loop
		public:
			List<T>::Node* m_node;
			Iterator(){};
			//Iterator(List<T>::Node* itt){m_node = itt;};
			Iterator(Node* nod) : m_node(nod){}
			//Iterator(std::initializer_list<T> ilist){
			//	m_node = ilist.begin();
			//}
			Iterator& operator++(){
				m_node = m_node->next;
				return *this;
			}
			Iterator operator++(int){
				Iterator temp;
				temp.m_node=m_node;
				m_node = m_node->next;
				return temp;
			}
			
			bool operator!=(List<T>::Iterator it2){
				if(m_node==it2.m_node){
					return false;
				}
				return true;
			}
			T operator*(){
				return *(m_node->value);
			}
			//Node m_node= *iter;
        };
    public:

	Node *head;
	
        List() : head(head)  {}
	Node m_head = *head;
        auto begin() { return Iterator{head->next}; }
        auto end() { return Iterator{head}; }
        auto insert(const Iterator &it, const T &val) {
		List::Node* temp = new List::Node(val);
        	List::Node* tempL = it.m_node->prev;
		it.m_node->prev = temp;
		tempL->next = temp;
		temp->prev = tempL;
		temp->next = it.m_node;
		return List<T>::Iterator(temp);
        }
        void push_front(const T &val) {
        	List::Node* temp = new List::Node(val);
		if(head->next !=head){  
			List::Node* tempL = head->next;
			head->next  = temp;
			temp->prev = head;
			temp->next = tempL;
			tempL->prev = temp;
		}else{
			head->next = temp;
			head->prev = temp;
			temp->next=head;
			temp->prev=head;
		}
        }
        void push_back(const T &val) {
        	List<T>::Node* temp = new List::Node(val);
		if(head->next !=head){
			List<T>::Node* tempL = head->prev;
			head->prev = temp;
			temp->next = head;
			temp->prev = tempL;
			tempL->next = temp;
		}else{
			head->prev = temp;
			head->next = temp;
			temp->next = head;
			temp->prev = head;
		}
        }
        void erase(const Iterator &it) {
        	assert(it.m_node != &m_head);
        	Node* tempO = it.m_node->next;
		Node* tempT = it.m_node->prev;
		tempT->next = tempO;
		tempO->prev = tempT;
		delete it.m_node;
        }
};



#endif
