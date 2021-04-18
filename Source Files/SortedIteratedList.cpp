#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
    this->doubly_linked_list.capacity = INITIAL_CAPACITY;
    this->doubly_linked_list.size = 0;
    this->doubly_linked_list.first_empty = 0;
    this->doubly_linked_list.array = new Node[INITIAL_CAPACITY];
    this->doubly_linked_list.head = -1;
    this->doubly_linked_list.tail = -1;
    for(int i=0;i<INITIAL_CAPACITY-1;i++) {
        this->doubly_linked_list.array[i].next = i + 1;
        this->doubly_linked_list.array[i].previous = i - 1;
    }
    this->doubly_linked_list.array[INITIAL_CAPACITY-1].next = -1;
    this->doubly_linked_list.array[INITIAL_CAPACITY-1].previous = INITIAL_CAPACITY - 2;
    this->relation = r;
}

int SortedIteratedList::size() const {
    return this->doubly_linked_list.size;
}

bool SortedIteratedList::isEmpty() const {
	if(this->doubly_linked_list.size <= 0) return false;
	return true;
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
