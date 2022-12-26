#include <iostream>
#include "DynamicArray.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    DynamicArray<int> my_array(5);
    my_array.insert(1);
    my_array.insert(2);
    my_array.insert(3);
    my_array.insert(4);
    my_array.print();
    my_array.insert(5);
    my_array.print();
    my_array.insert(6);
    my_array.insert(7);
    my_array.insert(1);
    my_array.insert(2);
    my_array.print();
    my_array.insert(3);
    my_array.insert(4);
    my_array.print();
    return 0;
}
