#pragma once
#include <iostream>
#include <utility>

class SequenceNode {
    public: // to make it easier, we can make the data members public so we don't need getters and setters
    SequenceNode* next; // pointer to next Node. If node is the tail, next is nullptr
    SequenceNode* prev; // pointer to previous Node. If node is the head, prev is nullptr
    std::string item; // the element being stored in the node

    //default constructor, ensure next and prev are nullptr
    SequenceNode() : next(nullptr), prev(nullptr) {}

    /// parameterized constructor, next and prev are set to nullptr and the
    /// node's element is set to the given value
    explicit SequenceNode(std::string item) : next(nullptr), prev(nullptr), item(std::move(item)) {}
};

class Sequence {
    private:
    public:
    SequenceNode* head;
    SequenceNode* tail;
    size_t nodeCount;

    explicit Sequence(size_t sz);

    Sequence(const Sequence& other);

    ~Sequence();

    void printSequence(std::ostream& os) const;

    // Outputs all elements (ex: <4, 8, 15, 16, 23, 42>) as a string to the output
    // stream. This is *not* a method of the Sequence class, but instead it is a
    // friend function
    friend std::ostream& operator<<(std::ostream& os, const Sequence& sequence);

    Sequence &operator=(const Sequence& other);

    std::string &operator[](size_t position);

    void push_back(const std::string &item);

    void pop_back();

    void insert(size_t position, const std::string &item);

    [[nodiscard]] std::string front() const;

    [[nodiscard]] std::string back() const;

    [[nodiscard]] bool empty() const;

    [[nodiscard]] size_t size() const;

    void clear();

    void erase(size_t position);

    void erase(size_t position, size_t count);
};