//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_ARRAY_H
#define WET2_ARRAY_H

template <typename T>
class Array {
public:
    explicit Array(int size) :
        m_size(size),
        m_ptr{new T[size]} {}

        ~Array() {
        delete[] m_ptr;
    }

    T *get() {
        return m_ptr;
    }

    const T &operator[](int i) const {
        return m_ptr[i];
    }

    T &operator[](int i){
        return m_ptr[i];
    }

    int getSize() {
        return m_size;
    }

    T *getPtr() {
        return m_ptr;
    }

private:
    int m_size;
    T *m_ptr;
};


#endif //WET2_ARRAY_H
