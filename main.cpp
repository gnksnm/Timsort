#include <iostream>
#include <sstream>
#include "array.h"
#include "stack.h"

unsigned evaluate_minrun(int n) {
    int r = 0;
    while ( n >= 64) {
        r|=(n&1);
        n>>=1;
    }
    return n+r;
}
Array do_run(Array arr, unsigned minrun) {

    bool is_up;
    unsigned i=0;
    Array run;
    if (arr[0]<arr[1]) {
        is_up=1;
    }
    else is_up=0;
    bool real=is_up;
    run.push_element(arr[i]);
    while (is_up==real&&(arr.get_length()-i-1)>1) {
        i++;
        run.push_element(arr[i]);
        if (arr[i]<arr[i+1]) {
            real=1;
        }
        else if (arr[i]==arr[i+1]) {
            real=is_up;
        }
        else real=0;
    }
    if (arr.get_length()-i-1==1) {
        run.push_element(arr[++i]);
    }
    else i++;
    if (!(is_up)) {
        run.revers();
    }
    while (run.get_length()<minrun&&arr.get_length()-i>0) {
        run.binary_add_element(arr[i]);
        i++;
    }

    return run;
}
bool is_collapse(Stack stack) {
    unsigned n = stack.get_length();
    if (n >= 3) {
        unsigned A = stack.check(n-3).get_length();
        unsigned B = stack.check(n-2).get_length();
        unsigned C = stack.check(n-1).get_length();
        if (A <= B + C) return true;
    }
    if (n >= 2) {
        unsigned B = stack.check(n-2).get_length();
        unsigned C = stack.check(n-1).get_length();
        if (B <= C) return true;
    }
    return false;
}


int main() {
    Array a;//в этот массив закидывается введенная строка
    Array tmp;//временный массив для слияния
    int tmp_streak = 0, stack_streak=0;//счётчики для перехода в галоп
    unsigned index; //индекс большего из массивов в слиянии
    bool stability; //маркер для устойчивости сортировки
    unsigned min_gallop=7;
    Stack stack;
    std:: string token;
    int minrun;
    bool collapse=0;
    std::string sss="-404 -665 622 -902 351 836 723 -337 708 891 589 872 -755 424 322 -126 -239 -337 -596 263 -76 453 -947 927 211 146 -33 653 -911 -219 689 765 -307 974 -449 502 288 -598 12 -116 -327 955 -254 187 -978 -799 -312 432 -933 -982 -479 -95 27 605 -518 -497 -168 172 -327 -121 445 -505 -722 -689 825 295 541 -309 802 -776 813 -584 -275 768 516 358 320 942 -840 538 530 -46 -927 81 609 641 518 -935 730 686 38 -900 367 142 414 -159 116 262 -137 458 665 67 -773 -463 924 77 -298 -721 -819 -109 894 -7 344 -959 -313 -273 738 672 -786 -991 -629 342 -524 -775 883 944 -996 -842 -703 -153 -529 -994 -537 216 417 -926 470 -13 -234 -443 141 -630 944 -787 622 -960 -162 170 832 -354 -207 315 -785 -353 256 912 -492 505 749 -420 132 57 -741 -579 842 -975 -584 -343 -670 75 -295 -997 -168 -774 -628 646 552 -805 -491 -566";
    std::stringstream ss(sss);
    while (ss>>token) {
        a.push_element(stoi(token));
    }
    a.print();
    std::cout<<"\n\n";

    minrun=evaluate_minrun(a.get_length());
    while (a.get_length()!=0) {
        while (!collapse){
            Array run=do_run(a,minrun);
            for (int i=0;i<run.get_length();i++) {   //КАК-ТО НАДО ПОМЕНЯТЬ, ЧТОБЫ ЭТО БЫЛО ВНУТРИ ФУНКЦИИ do_run
                a.delete_first();
            }
            run.print();
            std::cout<<"\n\n";
            stack.push(run);
            collapse=is_collapse(stack);
        }
        while (collapse){

            if (stack.get_length()>=3&&stack.check(2).get_length()<stack.check(0).get_length()) { //Слить 2 и 1 по индексу
                std::cout<<"1";
                if (stack.check(2).get_length()>=stack.check(1).get_length()) {
                    tmp=stack.check(1);
                    stack.delete_element(1);
                    index=1;
                    stability=1;//если истина - элементы tmp были после элементов stack[index]
                }
                else {
                    tmp=stack.check(2);
                    stack.delete_element(2);
                    index=1;
                    stability=0;//если ложь - элементы tmp были до элементов stack[index]
                }
                //tmp.print();
            }
            else {  //Слить  1 и 0 по индексу
                if (stack.check(1).get_length()>=stack.check(0).get_length()) {
                    tmp=stack.check(0);
                    stack.delete_element(0);
                    index=0;
                    stability=1;
                }
                else {
                    tmp=stack.check(1);
                    stack.delete_element(1);
                    index=0;
                    stability=0;
                }
            }

            //слияние tmp и stack[index] в out
            while (tmp.get_length()>0 && stack.check(index).get_length()>0) {

                Array out;//массив на выход
                if (tmp[0]>stack.check(index)[0]) {
                    tmp_streak++;
                    stack_streak=0;
                    out.push_element(stack.check(index)[0]);
                    stack.check(index).delete_first();
                    std::cout<<stack.check(index).get_length();
                }
                else if (tmp[0]<stack.check(index)[0]) {
                    stack_streak++;
                    tmp_streak=0;
                    out.push_element(tmp[0]);
                    tmp.delete_first();
                }
                else if (tmp[0]==stack.check(index)[0]) {
                    if (stability){
                        out.push_element(stack.check(index)[0]);
                        stack.check(index).delete_first();
                    }
                    else {
                        out.push_element(tmp[0]);
                        tmp.delete_first();
                    }
                }
                if (tmp_streak==min_gallop) {
                    int id=tmp.exponential_search(stack.check(index)[0]);
                    for (int i=0;i<id;i++) {
                        out.push_element(tmp[0]);
                        tmp.delete_first();
                    }
                    tmp_streak=0;
                }
                if (stack_streak==min_gallop) {
                    int id=stack.check(index).exponential_search(tmp[0]);
                    for (int i=0;i<id;i++) {
                        out.push_element(stack.check(index)[0]);
                        stack.check(index).delete_first();
                    }
                    stack_streak=0;
                }
                if (tmp.get_length()==0) {
                    while (stack.check(index).get_length()!=0) {
                        out.push_element(stack.check(index)[0]);
                        stack.check(index).delete_first();
                    }
                }
                if (stack.check(index).get_length()==0) {
                    while (tmp.get_length()!=0) {
                        out.push_element((tmp[0]));
                        tmp.delete_first();
                    }
                }
                stack.push(out);
                //stack.check(0).print();
            }
            collapse=is_collapse(stack);
        }
    }
    stack.check(0).print();


    return 0;
}