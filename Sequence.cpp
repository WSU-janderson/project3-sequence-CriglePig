/* Filename: Sequence.cpp
 * Author: Crystal Daniel
 * Project: Project 3 - Sequence
 * Due Date: 10/13/2025
 * Program Description: This program implements a doubly linked list data structure called Sequence, which stores
 * a series of strings in sequential order. The Sequence supports operations for insertion, deletion, traversal,
 * element access, and deep copying. It provides custom operator overloads and exception handling for invalid
 * access or modification attempts.
 */
#include "Sequence.h"
#include <cstdlib>
#include <iostream>

using namespace std;

/* Purpose: Constructs a sequence with sz items.
 * Parameters:
 *    sz – number of elements to initially create (default empty if 0)
 * Behavior:
 *    Creates a doubly linked list of sz empty strings.
 *    head points to the first node, tail points to the last node.
 */
Sequence::Sequence(size_t sz) {
    head = nullptr;
    tail = nullptr;
    nodeCount = 0;

    if (sz > 0) {
        auto* newNode = new SequenceNode("");
        head = newNode;
        tail = newNode;
        nodeCount = 1;

        while (nodeCount < sz) {
            newNode = new SequenceNode("");
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            nodeCount += 1;
        }
    }
}

/* Purpose: Copy constructor.
 * Parameters:
 *    other – another Sequence to copy
 * Behavior:
 *    Performs a deep copy of the other sequence, duplicating all nodes.
 */
Sequence::Sequence(const Sequence& other) : head(nullptr), tail(nullptr), nodeCount(0) {
    SequenceNode* current = other.head;

    while (current) {
        push_back(current->item);
        current = current->next;
    }
}

/* Purpose: Destructor.
 * Behavior:
 *    Deletes all nodes in the sequence and frees memory.
 */
Sequence::~Sequence() {
    clear();
}

/* Purpose: Prints the sequence to an output stream.
 * Parameters:
 *    os – output stream (e.g., cout)
 * Behavior:
 *    Outputs items in order, formatted as <item1, item2, ..., itemN>.
 */
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

/* Purpose: Stream insertion operator.
 * Parameters:
 *    os – output stream
 *    sequence – the Sequence to print
 * Returns:
 *    Reference to the output stream
 */
ostream& operator<<(ostream& os, const Sequence& sequence) {
    sequence.printSequence(os);
    return os;
}

/* Purpose: Assignment operator.
 * Parameters:
 *    other – Sequence to copy from
 * Returns:
 *    Reference to this sequence
 * Behavior:
 *    Clears current sequence and copies all nodes from other.
 *    Handles self-assignment correctly.
 */
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

/* Purpose: Access item at a given position.
 * Parameters:
 *    position – index of the desired element
 * Returns:
 *    Reference to the string at position
 * Throws:
 *    exception if position is out of bounds
 */
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

/* Purpose: Append an item to the end of the sequence.
 * Parameters:
 *    item – string to add
 */
void Sequence::push_back(const std::string &item) {
    auto* newNode = new SequenceNode();

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

/* Purpose: Remove the last item from the sequence.
 * Throws:
 *    exception if the sequence is empty
 */
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

/* Purpose: Insert an item at a specific position.
 * Parameters:
 *    position – index to insert at
 *    item – string to insert
 * Throws:
 *    exception if position is invalid
 */
void Sequence::insert(const size_t position, const std::string &item) {
    if (position > size()) {
        throw exception();
    }

    auto* newNode = new SequenceNode();
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

/* Purpose: Return the first element in the sequence.
 * Throws:
 *    exception if the sequence is empty
 */
std::string Sequence::front() const {
    if (empty()) {
        throw exception();
    }

    return head->item;
}

/* Purpose: Return the last element in the sequence.
 * Throws:
 *    exception if the sequence is empty
 */
std::string Sequence::back() const {
    if (empty()) {
        throw exception();
    }

    return tail->item;
}

/* Purpose: Check if the sequence has no elements.
 * Returns:
 *    true if sequence is empty, false otherwise
 */
bool Sequence::empty() const {
    return nodeCount == 0;
}

/* Purpose: Return the number of elements in the sequence.
 * Returns:
 *    the size of the sequence
 */
size_t Sequence::size() const {
    return nodeCount;
}

/* Purpose: Remove all elements from the sequence.
 * Behavior:
 *    Frees all node memory and resets the sequence to empty.
 */
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

/* Purpose: Remove a single element at a given position.
 * Parameters:
 *    position – index of element to remove
 * Throws:
 *    exception if position is invalid
 */
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

/* Purpose: Remove a range of elements.
 * Parameters:
 *    position – starting index
 *    count – number of elements to remove
 * Throws:
 *    exception if position/count is invalid
 */
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