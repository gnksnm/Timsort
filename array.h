//
// Created by user on 21.10.2025.
//

#ifndef UNTITLED_ARRAY_H
#define UNTITLED_ARRAY_H


class Array {
private:
    int length;
    int *data;
    int binary_search(int searching);
public:
    Array();
    ~Array();
    int get_length();
    void revers();
    void add_element(int index, int value);
    void binary_add_element();
};


#endif //UNTITLED_ARRAY_H