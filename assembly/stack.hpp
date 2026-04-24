//
// File: stack.hpp
//
// Programmer: Bryan Thomas
// Date:        Spring 2026
//
//
// Do not change the names of the classes or methods.  Otherwise, instructor
//  tests will not work.
//
#ifndef CS2_STACK_HPP_
#define CS2_STACK_HPP_

#include <new>
#include <cassert>
#include "../string/string.hpp"

template<typename T> 
class Node {
public:
    Node(const T& item, Node<T>* next = nullptr) : data(item), next(next) {}
	T data;
	Node<T>* next; 
};


// CLASS INV:
//
template <typename T>
class stack {
public:
              stack     ();
              stack     (const stack<T>&);
              ~stack    ();
    void      swap      (stack<T>&);
    stack<T>& operator= (stack<T>);
    
	bool      empty     () const;
	bool      full      () const;
	T         top       () const;
	T         pop       ();
	void      push      (const T&);

private:
	Node<T>   *tos;
};

template<typename T>
stack<T>::stack() : tos(nullptr) {}

template<typename T>
stack<T>::stack(const stack<T>& other) : tos(nullptr) {
	Node<T>* current = other.tos;
	Node<T>* prev = nullptr;
	while (current) {
		Node<T>* newNode = new Node<T>(current->data);
		if (!tos) {
			tos = newNode;
		} else {
			prev->next = newNode;
		}
		prev = newNode;
		current = current->next;
	}
}

template<typename T>
stack<T>::~stack() {
	while (tos) {
		Node<T>* temp = tos;
		tos = tos->next;
		delete temp;
	}
}

template<typename T>
void stack<T>::swap(stack<T>& rhs) {
	Node<T>* temp = tos;
	tos = rhs.tos;
	rhs.tos = temp;
}

template<typename T>
stack<T>& stack<T>::operator=(stack<T> rhs) {
	swap(rhs);
	return *this;
}

template<typename T>
bool stack<T>::empty() const {
	return tos == nullptr;
}

template<typename T>
bool stack<T>::full() const {
	Node<T>* next = new Node<T>(T());
	if (next) {
		delete next;
		return false;
	}
	return true;
}

template<typename T>
T stack<T>::top() const {
	assert(!empty());
	return tos->data;
}

template<typename T>
T stack<T>::pop() {
	assert(!empty());
	Node<T>* temp = tos;
	T data = temp->data;
	tos = tos->next;
	delete temp;
	return data;
}

template<typename T>
void stack<T>::push(const T& item) {
	Node<T>* newNode = new Node<T>(item, tos);
	tos = newNode;
}





#endif