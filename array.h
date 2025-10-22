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
    Array(const Array& other);
    ~Array();
    int get_length();
    void revers();
    void delete_first();
    void add_element(unsigned index, int value);
    void push_element(int value);
    void binary_add_element(int value);
    int& operator[](unsigned index);
    Array&operator=(const Array& other);
};


#endif //UNTITLED_ARRAY_H