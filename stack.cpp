#include "stack.h"

Stack::Stack() {
    top = nullptr;
    length=0;
}

void Stack::push(Array value) {
    if (this->is_empty()) {
        top=new List;
        top->val=value;
    }
    else {
        List* a= new List;
        a->prev=top;
        a->val=value;
        top=a;
    }
    length++;
}

Array Stack::pop() {
    List*a =top->prev;
    Array v= top->val;
    delete top;
    top =a;
    length--;
    return v;
}

Array &Stack::check(unsigned index) {
    List*a=top;
    for (int i=0;i<index;i++) {
        a=a->prev;
    }
    return a->val;
}

void Stack::delete_element(unsigned index) {
    List* curr=top;
    List* prevv;
    for (int i=0;i<index;i++) {
        prevv=curr;
        curr=curr->prev;
    }
    prevv->prev=curr->prev;
    length--;
    delete curr;
}

unsigned Stack::get_length() {
    return length;
}


bool Stack::is_empty() {
    if (top==nullptr)return 1;
    else return 0;
}

