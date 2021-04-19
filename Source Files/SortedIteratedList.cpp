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
	if(this->doubly_linked_list.size > 0) return false;
	return true;
}

ListIterator SortedIteratedList::first() const {
    ListIterator(*this).first();
    return ListIterator(*this);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
    return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	if(!poz.valid())
	    throw exception();
	if(poz.current_element == this->doubly_linked_list.head && poz.current_element == this->doubly_linked_list.tail){
	    TComp removed_element = this->doubly_linked_list.array[this->doubly_linked_list.head].element;
        this->doubly_linked_list.array[this->doubly_linked_list.head].next = -1;
        this->doubly_linked_list.array[this->doubly_linked_list.tail].previous = -1;
        this->doubly_linked_list.size--;
        return removed_element;
	}
	else if(poz.current_element == this->doubly_linked_list.head){
        TComp removed_element = this->doubly_linked_list.array[this->doubly_linked_list.head].element;
        int previous_head = this->doubly_linked_list.head;
        this->doubly_linked_list.head = this->doubly_linked_list.array[this->doubly_linked_list.head].next;
        this->doubly_linked_list.array[previous_head].next = this->doubly_linked_list.first_empty;
        this->doubly_linked_list.first_empty = previous_head;
        this->doubly_linked_list.size--;
        return removed_element;
	}
	else{
        auto temporary_iterator = ListIterator(*this);
        while(temporary_iterator.valid() && temporary_iterator.current_element != poz.current_element)
            temporary_iterator.next();
        if(!temporary_iterator.valid())
            throw exception();
        int element_to_be_removed = poz.current_element;
        TComp removed_element = this->doubly_linked_list.array[element_to_be_removed].element;
        temporary_iterator.next();
        int next_element = temporary_iterator.current_element;
        this->doubly_linked_list.array[next_element].previous = this->doubly_linked_list.array[element_to_be_removed].previous;
        this->doubly_linked_list.array[this->doubly_linked_list.array[element_to_be_removed].previous].next = this->doubly_linked_list.array[element_to_be_removed].next;
        return removed_element;
	}
}

void SortedIteratedList::resize() {
    this->doubly_linked_list.capacity*=2;
    auto resized_array = new Node[this->doubly_linked_list.capacity];
    for(int i=0;i<this->doubly_linked_list.size;i++)
        resized_array[i] = this->doubly_linked_list.array[i];

    delete[] this->doubly_linked_list.array;
    this->doubly_linked_list.array = resized_array;

    this->doubly_linked_list.array[this->doubly_linked_list.capacity - 1].next = this->doubly_linked_list.first_empty;
    for(int i=this->doubly_linked_list.capacity/2; i<this->doubly_linked_list.capacity-2; i++){
        this->doubly_linked_list.array[i].next = i + 1;
        this->doubly_linked_list.array[i].previous = i - 1;
    }
    this->doubly_linked_list.array[this->doubly_linked_list.capacity-1].next = -1;
    this->doubly_linked_list.array[this->doubly_linked_list.capacity-1].previous = this->doubly_linked_list.capacity - 2;
    this->doubly_linked_list.first_empty = this->doubly_linked_list.size;
}

ListIterator SortedIteratedList::search(TComp e) const{
    auto temporary_iterator = ListIterator(*this);
    while(temporary_iterator.valid() && this->doubly_linked_list.array[temporary_iterator.current_element].element != e)
        temporary_iterator.next();
    return temporary_iterator;
}

void SortedIteratedList::add(TComp e) {
	if(this->size() == this->doubly_linked_list.capacity-1)
	    this->resize();

	if(this->size() == 0){
	  this->doubly_linked_list.head = this->doubly_linked_list.first_empty;
	  this->doubly_linked_list.tail = this->doubly_linked_list.first_empty;
	  this->doubly_linked_list.first_empty = this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;
	  this->doubly_linked_list.array[this->doubly_linked_list.head].element = e;
	  this->doubly_linked_list.array[this->doubly_linked_list.head].next = -1;
	  this->doubly_linked_list.array[this->doubly_linked_list.head].previous = -1;
	} else{
        int current_position = this->doubly_linked_list.head;
        int next_position = this->doubly_linked_list.array[this->doubly_linked_list.head].next;
        while(!this->relation(e, this->doubly_linked_list.array[current_position].element) && next_position == -1){
            current_position = next_position;
            next_position = this->doubly_linked_list.array[current_position].next;
        }
        int new_position = this->doubly_linked_list.first_empty;
        this->doubly_linked_list.first_empty = this->doubly_linked_list.array[new_position].next;

        this->doubly_linked_list.array[new_position].element = e;
        this->doubly_linked_list.array[current_position].next = new_position;
        this->doubly_linked_list.array[new_position].previous = current_position;
    }
    this->doubly_linked_list.size++;
}

SortedIteratedList::~SortedIteratedList() {
	delete[] this->doubly_linked_list.array;
}
