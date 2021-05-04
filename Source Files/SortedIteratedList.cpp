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
    this->doubly_linked_list.array[this->doubly_linked_list.first_empty].element = NULL_TCOMP;
    for(int i=0;i<INITIAL_CAPACITY-1;i++) {
        this->doubly_linked_list.array[i].next = i + 1;
        this->doubly_linked_list.array[i].previous = i - 1;
        this->doubly_linked_list.array[i].element = NULL_TCOMP;
    }
    this->doubly_linked_list.array[INITIAL_CAPACITY-1].next = -1;
    this->doubly_linked_list.array[INITIAL_CAPACITY-1].previous = INITIAL_CAPACITY - 2;
    this->doubly_linked_list.array[INITIAL_CAPACITY-1].element = NULL_TCOMP;
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
        this->doubly_linked_list.array[this->doubly_linked_list.head].previous = -1;
        this->doubly_linked_list.array[this->doubly_linked_list.tail].element = NULL_TCOMP;
        this->doubly_linked_list.size=0;
        this->doubly_linked_list.first_empty=0;
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
//        if(!temporary_iterator.valid())
//            throw exception();
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

    this->doubly_linked_list.first_empty = this->doubly_linked_list.size;
    resized_array[this->doubly_linked_list.first_empty].previous = -1;
    resized_array[this->doubly_linked_list.first_empty].next = this->doubly_linked_list.size+1;
    resized_array[this->doubly_linked_list.first_empty].element = NULL_TCOMP;

    for(int i=this->doubly_linked_list.size+1; i<this->doubly_linked_list.capacity-1; i++){
        resized_array[i].next = i + 1;
        resized_array[i].previous = i - 1;
        resized_array[i].element = NULL_TCOMP;
    }
    resized_array[this->doubly_linked_list.capacity-1].next = -1;
    resized_array[this->doubly_linked_list.capacity-1].previous = this->doubly_linked_list.capacity - 2;
    resized_array[this->doubly_linked_list.capacity-1].element = NULL_TCOMP;
    delete[] this->doubly_linked_list.array;
    this->doubly_linked_list.array = resized_array;
}

ListIterator SortedIteratedList::search(TComp e) const{
    auto temporary_iterator = ListIterator(*this);
    while(temporary_iterator.valid() && this->doubly_linked_list.array[temporary_iterator.current_element].element != e)
        temporary_iterator.next();
    return temporary_iterator;
}

int SortedIteratedList::allocate() {
    int new_element = doubly_linked_list.first_empty;
    if(new_element != -1){
        this->doubly_linked_list.first_empty = this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;
        if(this->doubly_linked_list.first_empty != -1){
            this->doubly_linked_list.array[this->doubly_linked_list.first_empty].previous = -1;
        }
        this->doubly_linked_list.array[new_element].next = -1;
        this->doubly_linked_list.array[new_element].previous = -1;
    }
    return new_element;
}

void SortedIteratedList::add(TComp e) {
    if(this->size() == this->doubly_linked_list.capacity)
        this->resize();

    if(this->size() == 0)
    {
        this->doubly_linked_list.size++;
        this->doubly_linked_list.head=this->doubly_linked_list.first_empty;
        this->doubly_linked_list.first_empty=this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;

        if(this->doubly_linked_list.first_empty != -1)
            this->doubly_linked_list.array[this->doubly_linked_list.first_empty].previous = -1;

        this->doubly_linked_list.array[this->doubly_linked_list.head].element = e;
        this->doubly_linked_list.array[this->doubly_linked_list.head].next = -1;
        this->doubly_linked_list.tail = this->doubly_linked_list.head;
    }
    else
    if(this->relation(e, this->doubly_linked_list.array[this->doubly_linked_list.head].element))
    {
        this->doubly_linked_list.size++;
        int new_head = this->doubly_linked_list.first_empty;
        this->doubly_linked_list.first_empty = this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;

        if(this->doubly_linked_list.first_empty != -1)
            this->doubly_linked_list.array[this->doubly_linked_list.first_empty].previous = -1;

        this->doubly_linked_list.array[new_head].next = this->doubly_linked_list.head;
        this->doubly_linked_list.array[new_head].previous = -1;
        this->doubly_linked_list.array[new_head].element = e;
        this->doubly_linked_list.array[this->doubly_linked_list.head].previous = new_head;
        this->doubly_linked_list.head = new_head;
    }
    else
    {
        int CurrentElement = this->doubly_linked_list.head;
        while(this->doubly_linked_list.array[CurrentElement].next != -1 && !this->relation(e, this->doubly_linked_list.array[this->doubly_linked_list.array[CurrentElement].next].element))
        {
            CurrentElement = this->doubly_linked_list.array[CurrentElement].next;
        }
        if(this->doubly_linked_list.array[CurrentElement].next == -1)
        {
            this->doubly_linked_list.size++;
            int new_element = this->doubly_linked_list.first_empty;

            this->doubly_linked_list.first_empty = this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;
            if(this->doubly_linked_list.first_empty != -1)
                this->doubly_linked_list.array[this->doubly_linked_list.first_empty].previous = -1;

            this->doubly_linked_list.array[this->doubly_linked_list.tail].next = new_element;
            int old_tail = this->doubly_linked_list.tail;
            this->doubly_linked_list.tail = new_element;
            this->doubly_linked_list.array[this->doubly_linked_list.tail].next = -1;
            this->doubly_linked_list.array[this->doubly_linked_list.tail].previous = old_tail;
            this->doubly_linked_list.array[this->doubly_linked_list.tail].element = e;
        }
        else
        if(this->doubly_linked_list.array[CurrentElement].next != -1 && this->relation(e, this->doubly_linked_list.array[this->doubly_linked_list.array[CurrentElement].next].element))
        {
            this->doubly_linked_list.size++;
            int new_element = this->doubly_linked_list.first_empty;

            this->doubly_linked_list.first_empty = this->doubly_linked_list.array[this->doubly_linked_list.first_empty].next;
            if(this->doubly_linked_list.first_empty != -1)
                this->doubly_linked_list.array[this->doubly_linked_list.first_empty].previous = -1;

            int NextElement = this->doubly_linked_list.array[CurrentElement].next;
            int PreviousElement = CurrentElement;
            this->doubly_linked_list.array[PreviousElement].next = new_element;
            this->doubly_linked_list.array[new_element].next = NextElement;
            this->doubly_linked_list.array[new_element].previous = PreviousElement;
            this->doubly_linked_list.array[new_element].element = e;
            this->doubly_linked_list.array[NextElement].previous = new_element;
        }
    }
}

SortedIteratedList::~SortedIteratedList() {
	delete[] this->doubly_linked_list.array;
}
