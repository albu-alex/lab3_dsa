#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>

using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list) : list(list){
	this->current_element = list.doubly_linked_list.head;
}
//Theta(1)

void ListIterator::first() {
    this->current_element = list.doubly_linked_list.head;
}
//Theta(1)

void ListIterator::next(){
	if(!this->valid())
	    throw exception();
    this->current_element = list.doubly_linked_list.array[this->current_element].next;
}
//Theta(1)

bool ListIterator::valid() const{
	if(this->current_element == -1) return false;
	return true;
}
//Theta(1)

TComp ListIterator::getCurrent() const{
	if(!this->valid())
	    throw exception();
	return this->list.doubly_linked_list.array[this->current_element].element;
}
//Theta(1)
