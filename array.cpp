//
// Created by user on 21.10.2025.
//

#include "array.h"

#include <stdexcept>

Array::Array() {
    length = 0;
    data = new int[length];
}

Array::Array(const Array &other) {
    length = other.length;
    if (length > 0) {
        data = new int[length];
        for (unsigned i = 0; i < length; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr;
    }
}

Array::~Array() {
    delete[] data;
}

int Array::get_length() {
    return length;
}

void Array::revers() {
    int*a = new int[length];
    for (int i=0;i<length;i++) {
        a[i]=data[length-i-1];
    }
    data=a;
}

void Array::delete_first() {
    int* a = new int[length-1];
    for (int i =0; i<length-1;i++) {
        a[i]=data[i+1];
    }
    data=a;
    length--;
}

int Array::binary_search(int searching) {
    int low = 0;
    int high = length-1 ;
    if (data[high]<=searching) return high+1;
    if (data[low]>=searching)return low;
    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        if (mid==low) return mid+1;
        if (data[mid] == searching) return mid+1;
        else if (data[mid] < searching) low = mid;
        else high = mid;
    }
}

void Array::binary_add_element(int value) {
    unsigned index=binary_search(value);
    add_element(index,value);
}

int& Array::operator[](unsigned index) {
    if (index >= length)
        throw std::out_of_range("Index out of range!");
    return data[index];
}

Array & Array::operator=(const Array &other) {
    if (this == &other)
        return *this;

    delete[] data;
    length = other.length;
    if (length > 0) {
        data = new int[length];
        for (unsigned i = 0; i < length; ++i)
            data[i] = other.data[i];
    } else {
        data = nullptr;
    }
    return *this;
}

void Array::add_element(unsigned index, int value) {
    if (index > length) {
        throw std::out_of_range("Index out of range");
    }
    int* arr = new int[length + 1];

    for (unsigned i = 0; i < index; i++){
        arr[i] = data[i];
}
    arr[index] = value;

    for (unsigned i = index; i < length; i++) {
        arr[i + 1] = data[i];
    }
    delete[] data;
    data = arr;
    ++length;
}

void Array::push_element(int value) {
    this->add_element(length,value);
}
