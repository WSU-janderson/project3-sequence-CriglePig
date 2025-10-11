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
Sequence::Sequence(const Sequence& other) : head(nullptr), tail(nullptr), nodeCount(0) {
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

void Sequence::printSequence(ostream& os) const {
    SequenceNode* current = head;

    os << "<";

    // loop until current equals the node at position
    while (current != nullptr) {
        os << current->item;

        if (current->next != nullptr) {
            os << ", ";
        }

        current = current->next;
    }

    os << ">";
}

ostream& operator<<(ostream& os, const Sequence& sequence) {
    sequence.printSequence(os);
    return os;
}

// The current sequence is released and replaced by a (deep) copy of sequence
// other. A reference to the copied sequence is returned (return *this;).
Sequence& Sequence::operator=(const Sequence& other) {
    // self-assignment guard
    if (this == &other) {
        return *this;
    }

    clear(); // delete current nodes

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
    if (position >= size()) {
        throw exception();
    }

    SequenceNode* current = head;

    // loop until current equals the node at position
    for (size_t currPos = 0; currPos < position; currPos++) {
        current = current->next;
    }

    return current->item;
}

// The value of item is appended to the sequence.
void Sequence::push_back(std::string item) {
    SequenceNode* newNode = new SequenceNode();

    newNode->item = item;
    newNode->next = nullptr;
    newNode->prev = tail;

    if (head == nullptr) { // list is empty
        head = newNode;
        tail = newNode;
    } else { // link the new node at the end
        tail->next = newNode;
        tail = newNode;
    }

    nodeCount++;
}

// The item at the end of the sequence is deleted and size of the sequence is
// reduced by one. If sequence was empty, throws an exception
void Sequence::pop_back() {
    if (empty()) {
        throw exception();
    }

    SequenceNode* temp = tail;

    if (head == tail) { // only one node in the list
        head = nullptr;
        tail = nullptr;
    } else { // more than one node
        tail = tail->prev;
        tail->next = nullptr;
    }

    delete temp;
    nodeCount--;
}

// The position satisfies ( position >= 0 && position <= last_index() ). The
// value of item is inserted at position and the size of sequence is increased
// by one. Throws an exceptionif the position is outside the bounds of the
// sequence
void Sequence::insert(size_t position, std::string item) {
    if (position > size()) {
        throw exception();
    }

    SequenceNode* newNode = new SequenceNode();
    newNode->item = item;

    if (size() == 0) { // empty list
        newNode->prev = nullptr;
        newNode->next = nullptr;
        head = newNode;
        tail = newNode;
    } else if (position == 0) { // insert at the front
        newNode->prev = nullptr;
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    } else if (position == size()) { // insert at the end
        newNode->next = nullptr;
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    } else { // insert in the middle
        SequenceNode* current = head;

        // loop until current equals the node at position
        for (size_t currPos = 0; currPos < position; currPos++) {
            current = current->next;
        }

        SequenceNode* before = current->prev;
        SequenceNode* after = current;

        newNode->next = after;
        newNode->prev = before;

        before->next = newNode;
        after->prev = newNode;
    }

    nodeCount++;
}

// Returns the first element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::front() const {
    if (empty()) {
        throw exception();
    }

    return head->item;
}

// Return the last element in the sequence. If the sequence is empty, throw an
// exception.
std::string Sequence::back() const {
    if (empty()) {
        throw exception();
    }

    return tail->item;
}

// Return true if the sequence has no elements, otherwise false.
bool Sequence::empty() const {
    return nodeCount == 0;
}

// Return the number of elements in the sequence.
size_t Sequence::size() const {
    return nodeCount;
}

// All items in the sequence are deleted and the memory associated with the
// sequence is released, resetting the sequence to an empty state that can have
// items re-inserted.
void Sequence::clear() {
    SequenceNode* current = head;

    while (current) {
        SequenceNode* temp = current->next;
        delete current;
        current = temp;
    }

    head = nullptr;
    tail = nullptr;
    nodeCount = 0;
}

// The item at position is removed from the sequence, and the memory
// is released. If called with an invalid position throws an exception.
void Sequence::erase(size_t position) {
    // if position is invalid, throw exception
    if (position >= size()) {
        throw exception();
    }

    SequenceNode* temp; // temporary node

    // if position is head, erase head and return
    if (position == 0) {
        temp = head;
        head = head->next;

        delete temp;
        nodeCount--;

        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }

        return;
    }

    // if position is tail, erase tail and return
    if (position == size() - 1) {
        temp = tail;
        tail = tail->prev;

        delete temp;
        nodeCount--;

        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr; // now empty list
        }

        return;
    }

    // setup local variables for loop to find node at position
    SequenceNode* current = head;

    // loop until current equals the node at position
    for (size_t currPos = 0; currPos < position; currPos++) {
        current = current->next;
    }

    // the nodes before and after the deleted node
    SequenceNode* before = current->prev;
    SequenceNode* after = current->next;

    // connect the before and after nodes
    before->next = after;
    after->prev = before;

    // erase current
    delete current;
    nodeCount--;
}

// The items in the sequence at ( position ... (position + count - 1) ) are
// deleted and their memory released. If called with invalid position and/or
// count throws an exception.
void Sequence::erase(size_t position, size_t count) {
    if (position >= size() || count == 0 || position + count > size()) {
        throw exception();
    }

    // get first node to be deleted
    SequenceNode* first = head;
    for (size_t i = 0; i < position; ++i) {
        first = first->next;
    }

    // get last node to be deleted
    SequenceNode* last = first;
    for (size_t i = 1; i < count; ++i) {
        last = last->next;
    }

    // initialize the nodes before and after the first and last nodes to be deleted
    SequenceNode* before = first->prev;
    SequenceNode* after = last->next;

    // delete nodes between first and last
    SequenceNode* current = first;
    while (current != after) {
        SequenceNode* nextNode = current->next;
        delete current;
        nodeCount--;
        current = nextNode;
    }

    // reconnect adjacent nodes
    if (before) {
        before->next = after;
    } else {
        head = after;  // deletion from head
    }

    if (after) {
        after->prev = before;
    } else {
        tail = before;  // deletion up to tail
    }
}