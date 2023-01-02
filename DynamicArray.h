//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_DYNAMICARRAY_H
#define WET2_DYNAMICARRAY_H

#include "Array.h"

template<typename T>
class DynamicArray {

public:
        explicit DynamicArray(int size) :
                m_size(size),
                m_array(Array<T>(size))
        {}

        void expandArray() {
            auto temp = Array<T>(m_currentSize * 2);
            copyArray(temp);
            delete m_array.getPtr();

            m_size = temp.getSize();
            m_array = temp;
        }

        T &operator[](int i) {
            m_currentSize++;
            if(needToExpand()) {
                expandArray();
            }
            return m_array.operator[](i);
        }

        void print_arr() {
            for(int i = 0; i < m_size / 2 + 1 ; i++) {
                printf("%d ", m_array[i]);
            }
            printf("\n");
        }

private:

    void copyArray(Array<T> intoArray) {
        for(int i = 0; i < m_size / 2 + 1 ; i++) {
            intoArray[i] = m_array[i];
        }
    }

    bool needToExpand() {
        return m_currentSize * 2 >= m_size;
    }

    Array<T> m_array;
    int m_size;
    int m_currentSize = 0;
};


#endif //WET2_DYNAMICARRAY_H
