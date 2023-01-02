#include <iostream>

#include "DynamicArray.h"

int main() {
    DynamicArray<int> arr(3);

    arr[0] = 1;
    arr.print_arr();
    arr[1] = 2;
    arr.print_arr();
    arr[2] = 3;
    arr.print_arr();
    arr[3] = 4;
    arr.print_arr();
    arr[4] = 5;
    arr.print_arr();
    arr[5] = 6;
    arr.print_arr();
    arr[6] = 7;
    arr.print_arr();
    arr[7] = 8;
    arr.print_arr();

    return 0;
}
