#include "array.h"
#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H
struct List {
    List*prev;
    Array val;
};

class Stack {
private:
    List*top;
    unsigned length;
public:
    Stack();
    void push(Array value);
    Array pop();

    Array &check(unsigned index);
    void delete_element(unsigned index);
    unsigned get_length();
    bool is_empty();
};


#endif //UNTITLED_STACK_H