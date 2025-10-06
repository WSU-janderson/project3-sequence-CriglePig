#include "Sequence.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Creates an empty sequence (numElts == 0) or a sequence of numElts items
// indexed from 0 ... (numElts - 1).
Sequence::Sequence(size_t sz) {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;

    if (sz > 0) {
        auto* newNode = new SequenceNode();
        head = newNode;
        tail = newNode;
        nodeCount = 1;

        while (nodeCount < sz) {
            newNode = new SequenceNode();
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            nodeCount += 1;
        }
    }
}

// Creates a (deep) copy of sequence other
Sequence::Sequence(const Sequence& other) {
    SequenceNode* current = other.head;

    while (current) {
        push_back(current->item);
        current = current->next;
    }
}

// Destroys all items in the sequence and release the memory
// associated with the sequence
Sequence::~Sequence() {
    clear();
}

// The current sequence is released and replaced by a (deep) copy of sequence
// other. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& other) {
    head = other.head;
    tail = other.tail;
    nodeCount = other.nodeCount;

    clear();

    SequenceNode* current = other.head;

    while (current) {
        push_back(current->item);
        current = current->next;
    }

    return *this;
}

// The position satisfies ( position >= 0 && position <= last_index() ).
// The return value is a reference to the item at index position in the
// sequence. Throws an exception if the position is outside the bounds
// of the sequence
std::string& Sequence::operator[](size_t position) {
    if () {
        throw exception();
    }
}

// The value of item is append to the sequence.
void Sequence::push_back(std::string item) {

}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    if () {
        throw exception();
    }
}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    if () {
        throw exception();
    }
}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if () {
        throw exception();
    }
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if () {
        throw exception();
    }
}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {

}

// Return the number of elements in the sequence.
size_t Sequence::size() const {

}

// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
void Sequence::clear() {
    SequenceNode* current = head;

    while (current != nullptr) {
        SequenceNode* temp = current->next;
        delete current;
        current = temp;
    }

    head = nullptr;
}

// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {
    if () {
        throw exception();
    }
}

// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {
    if () {
        throw exception();
    }
}