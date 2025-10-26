#include <iostream>
#include <sstream>
#include "array.h"
#include "stack.h"
#include "windows.h"

unsigned evaluate_minrun(int n) {
    int r = 0;
    while ( n >= 64) {
        r|=(n&1);
        n>>=1;
    }
    return n+r;
}

void merge(Array& arr1,Array& arr2) { //arr1<arr2, выход слияния в arr1
    Array tmp = arr1;
    Array a;
    arr1=a;
    int min_gallop = 7;
    int tmp_streak = 0, stack_streak=0;//счётчики для перехода в галоп
    while (tmp.get_length()>0 && arr2.get_length()>0) {
        if (*(tmp.get_data()) < *(arr2.get_data())) {
            arr1.push_element(tmp[0]);
            tmp.delete_first();
            tmp_streak++;
            stack_streak=0;
        }
        else {
            arr1.push_element(arr2[0]);
            arr2.delete_first();
            stack_streak++;
            tmp_streak=0;
        }
    }
    if (tmp_streak >= min_gallop || stack_streak >= min_gallop) {
        int copied =0; //для проверки эффективности галопа
        if (tmp_streak >= min_gallop) {
            copied = tmp.exponential_search(arr2.get_length() > 0 ? arr2[0] : tmp[tmp.get_length()-1]);
            copied = std::min(copied, tmp.get_length());
            for (int i = 0; i < copied; ++i)
                arr1.push_element(tmp[i]);
            tmp.delete_first_n(copied);
        }
        else if (stack_streak >= min_gallop) {
            copied = arr2.exponential_search(tmp.get_length() > 0 ? tmp[0] : arr2[arr2.get_length()-1]);
            copied = std::min(copied, arr2.get_length());
            for (int i = 0; i < copied; ++i)
                arr1.push_element(arr2[i]);
            arr2.delete_first_n(copied);
        }
        if (copied < min_gallop) {
            min_gallop++;
        }
        else if (min_gallop > 1) {
            min_gallop--;
        }
        tmp_streak = 0;
        stack_streak = 0;
    }
    while (tmp.get_length() > 0) {
        arr1.push_element(tmp[0]);
        tmp.delete_first();
    }
    while (arr2.get_length() > 0) {
        arr1.push_element(arr2[0]);
        arr2.delete_first();
    }
}

Array do_run(Array &arr, unsigned minrun) {
    if (arr.get_length() == 0) return Array();
    bool is_up = true;
    if (arr.get_length() > 1 && arr[0] > arr[1]) is_up = false;
    Array run;
    run.push_element(arr[0]);
    unsigned i = 0;
    while (i + 1 < arr.get_length()) {
        if ((arr[i] <= arr[i+1]) == is_up) {
            i++;
            run.push_element(arr[i]);
        } else break;
    }
    if (!is_up) run.revers();
    while (run.get_length() < minrun && arr.get_length() > run.get_length()) {
        run.binary_add_element(arr[run.get_length()]);
    }
    for (unsigned j = 0; j < run.get_length(); j++) {
        arr.delete_first();
    }
    return run;
}

bool is_collapse(Stack stack) {
    unsigned n = stack.get_length();
    if (n >= 3) {
        unsigned A = stack.check(0).get_length();
        unsigned B = stack.check(1).get_length();
        unsigned C = stack.check(2).get_length();
        if (A <= B + C) return true;
    }
    if (n >= 2) {
        unsigned B = stack.check(0).get_length();
        unsigned C = stack.check(1).get_length();
        if (B <= C) return true;
    }
    return false;
}


int main() {
    SetConsoleOutputCP(CP_UTF8);
    Array a,d;//в этот массив закидывается введенная строка
    Array tmp;//временный массив для слияния
    Array* arr1ptr, *arr2ptr;
    int tmp_streak = 0, stack_streak=0;//счётчики для перехода в галоп
    unsigned index; //индекс большего из массивов в слиянии
    bool stability; //маркер для устойчивости сортировки
    unsigned min_gallop = 7;
    Stack stack;
    std:: string token;
    int minrun;
    bool collapse = 0;
    std::string input;//="42 7 19 85 3 66 12 91 54 28 37 73 5 61 8 47 90 14 33 76 21 59 88 11 64";
    std::cout<<"Введите элементы массива в строку через пробел:\n";
    std::getline(std::cin, input);
    std::stringstream ss(input);
    while (ss >> token) {
        a.push_element(stoi(token));

    }
    minrun=evaluate_minrun(a.get_length());
    while (a.get_length()!=0) {
        while (!collapse){
            Array run=do_run(a,minrun);
            stack.push(run);
            collapse=is_collapse(stack);

        }

        while (collapse) {
            unsigned ind1,ind2,del;
            if (stack.get_length()>2&&stack.check(2).get_length()<stack.check(0).get_length()) {
                ind1=1;
                ind2=2;
            }
            else {
                ind1=0;
                ind2=1;
            }
            Array&b=stack.check(ind1);
            Array&c=stack.check(ind2);
            if (b.get_length()<=c.get_length()) {
                arr1ptr = &b;
                arr2ptr = &c;
                del=ind2;
            }
            else {
                arr1ptr = &c;
                arr2ptr = &b;
                del=ind1;
            }
            merge(*arr1ptr,*arr2ptr);
            stack.delete_element(del);
            collapse=is_collapse(stack);
        }
    }
    while (stack.get_length()>1) {
        unsigned ind1,ind2;
        if (stack.get_length()>2&&stack.check(2).get_length()<stack.check(0).get_length()) {
            ind1=1;
            ind2=2;
        }
        else {
            ind1=0;
            ind2=1;
        }
        Array& b=stack.check(ind1);
        Array& c=stack.check(ind2);
        if (b.get_length()<=c.get_length()) {
            arr1ptr = &b;
            arr2ptr = &c;
            stack.delete_element(ind2);
        }
        else {
            arr1ptr = &c;
            arr2ptr = &b;
            stack.delete_element(ind1);
        }
        merge(*arr1ptr,*arr2ptr);
        collapse=is_collapse(stack);
    }
    std::cout<<"Отсортированный массив(для удобства разделен на строки по 20 эл-тов):\n";
    stack.check(0).print();


    return 0;
}