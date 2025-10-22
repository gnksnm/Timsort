//
// Created by user on 21.10.2025.
//

#include "array.h"

Array::Array() {
    length = 64;
    data = new int[length];
}

Array::~Array() {
    delete[] data;
}

int Array::get_length() {
    return length;
}

int Array::binary_search(int searching) {
    int low=0;
    int hight=length-1;
    int l = (low+hight)/2;
    while (l!=searching) {
        if (l>searching) {
            hight=l;
        }
        if (l<searching) {
            low=l;
        }
        l = (low+hight)/2;
        if (low==hight) return -1;
    }
    return l;
}

void Array::binary_add_element() {

}

void Array::add_element(int index,int value) {
    int *arr= new int[length+1];
    for (int i = 0; i<index; i++) {
        arr[i]=data[i];
    }
    arr[index]=value;
    for (int i =index;i<length+1;i++) {
        arr[i]=data[i-1];
    }
    delete[] data;
    data=arr;

}
