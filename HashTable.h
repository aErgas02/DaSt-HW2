//
// Created by ariel on 1/3/2023.
//

#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include "LinkedList.h"

template<class T>
class HashTable{
private:

    const int alpha = 1, init_size = 16;
    int counter = 0, size = init_size;

    LinkedList<T>* arr = nullptr;

    int hash_func(int id);
    void resize();

    bool (*compare)(T*, int);

public:
    explicit HashTable(bool (*compare_objs)(T*, int)) : compare(compare_objs) {arr = new LinkedList<T>[init_size];};
    ~HashTable(){delete[] arr;};

    void insert(int id, T obj);
    T* find(int id);

};

template<class T>
int HashTable<T>::hash_func(int id) {
    return id%size;
}

template<class T>
void HashTable<T>::resize() {
    auto new_arr = new LinkedList<T>[size*2];
    for(int i = 0; i < size; i++){
        new_arr[i] = arr[i];
    }
    size *= 2;
    delete[] arr;
    arr = new_arr;
}

template<class T>
void HashTable<T>::insert(int id, T obj) {
    int index = hash_func(id);
    if(index >= 0 && index <= size){
        arr[index].insert(obj);
        counter++;
    }
    if((counter/size) >= alpha){
        resize();
    }
}

template<class T> // maybe I should assume is exists already checked
T* HashTable<T>::find(int id){
    int index = hash_func(id);
    return arr[index].find(id, compare);
}

#endif //WET2_HASHTABLE_H
