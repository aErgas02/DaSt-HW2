//
// Created by ariel on 1/4/2023.
//

#ifndef WET2_LINKEDLIST_H
#define WET2_LINKEDLIST_H
#include "LinkedNode.h"

template<class T>
class LinkedList{
private:
    LinkedNode<T>* first;
    LinkedNode<T>* last;
    int size = 0;

public:
    LinkedList() : first{nullptr}, last{nullptr} {}
    ~LinkedList(){
        LinkedNode<T>* cur = first, *temp;
        while(cur != last){
            temp = cur;
            cur = cur->get_next();
            delete temp;
        }
        delete cur;
    }
    LinkedList<T>& operator=(const LinkedList<T> & to_copy){
        if(this == &to_copy) return *this;

        LinkedNode<T>* cur = to_copy.first;
        while(cur != nullptr){
            insert(*cur->get_val());
            cur = cur->get_next();
        }
        size = to_copy.size;
        return *this;
    }

    void insert(T obj){
        auto new_node = new LinkedNode<T>(obj);
        if(first == nullptr){
            last = new_node;
        }
        new_node->set_next(first);
        first = new_node;
        size++;
    }

    T* find(int i, bool (*compare)(T*, int)){
        LinkedNode<T>* cur = first;

        while(cur != nullptr){
            if (compare(cur->get_val(), i)) {
                return cur->get_val();
            }
            cur = cur->get_next();
        }
        return nullptr;
    }

    LinkedNode<T>* get_first() {return first;}

};

#endif //WET2_LINKEDLIST_H
