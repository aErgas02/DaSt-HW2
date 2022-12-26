//
// Created by ariel on 12/26/2022.
//

#ifndef WET2_DYNAMICARRAY_H
#define WET2_DYNAMICARRAY_H

template <class T>
class DynamicArray{
private:
    T* arr = nullptr;
    enum {N = 11};
    int size = N, cur = 0;

    void increase();

public:
    DynamicArray() {arr = new T[N]();};
    explicit DynamicArray(int i) : size(i) {
        if(i <= 0) size = N;
        arr = new T[size]();
    };
    ~DynamicArray(){delete[] arr;};
    void insert(T);
    void print();
};

template <class T>
void DynamicArray<T>::insert(T obj){
    arr[cur] = obj;
    cur++;
    if(cur == size){
        this->increase();
    }
}

template <class T>
void DynamicArray<T>::increase(){
    T* new_arr = new T[size*2]();
    for(int i = 0; i < size; i++){
        new_arr[i] = arr[i];
    }
    delete[] arr;
    arr = new_arr;
    size *= 2;
}

template <class T>
void DynamicArray<T>::print(){
    for(int i = 0; i < size; i++){
        std::cout << arr[i]<<" ";
    }
    std::cout << std::endl;
}


#endif //WET2_DYNAMICARRAY_H
