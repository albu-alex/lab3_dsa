#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
	this->relation = r;
	this->doubly_linked_list.capacity = INITIAL_CAPACITY;
	this->doubly_linked_list.head = -1;
	this->doubly_linked_list.tail = -1;
	this->doubly_linked_list.elements = new TComp[INITIAL_CAPACITY];
	this->doubly_linked_list.next = new int[INITIAL_CAPACITY];
	for(int i=0;i<INITIAL_CAPACITY-1;i++)
	    this->doubly_linked_list.next[i] = i+1;
	this->doubly_linked_list.next[INITIAL_CAPACITY-1] = -1;
	this->doubly_linked_list.FirstEmpty = 1;
	this->_size=0;
}

int SortedIteratedList::size() const {
	return this->_size;
}

bool SortedIteratedList::isEmpty() const {
	//TODO - Implementation
	return false;
}

ListIterator SortedIteratedList::first() const {
	//TODO - Implementation
	return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	//TODO - Implementation
	return NULL_TCOMP;
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	//TODO - Implementation
	return NULL_TCOMP;
}

ListIterator SortedIteratedList::search(TComp e) const{
	//TODO - Implementation
	return ListIterator(*this);
}

void SortedIteratedList::add(TComp e) {
	//TODO - Implementation
}

SortedIteratedList::~SortedIteratedList() {
	//TODO - Implementation
}
