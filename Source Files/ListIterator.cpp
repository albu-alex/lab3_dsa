#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->current_element = 0;
}

void ListIterator::first(){
    this->current_element = 0;
}

void ListIterator::next(){
	this->current_element++;
}

bool ListIterator::valid() const{
	if(this->current_element >= this->list.doubly_linked_list.capacity) return false;
	return true;
}

TComp ListIterator::getCurrent() const{
	if(!this->valid())
	    throw exception();
	return this->list.doubly_linked_list[this->current_element];
}


