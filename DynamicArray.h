//
// Created by ariel on 12/26/2022.
//

#ifndef WET2_DYNAMICARRAY_H
#define WET2_DYNAMICARRAY_H

template <class T>
DynamicArray{
private:
    T* arr;
    int size;
public:
    DynamicArray(){};
    DynamicArray(int i) : size(i){arr = new T()[size]};
    ~DynamicArray(){};
    void insert(T);
}

template <class T>
DynamicArray::insert(){

}




#endif //WET2_DYNAMICARRAY_H
