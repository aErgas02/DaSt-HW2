//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include "UFNode.h"
#include <memory>
#include "HashTable.h"

template <class T>
class UnionFind {

public:
    UFNode<T>& insert(int key, T& obj);
    void unify(UFNode<T> &biggerSet, UFNode<T>&smallerSet);
    bool isObjectExist(int key);
    UFNode<T> *getRoot(UFNode<T> *setA);
    UFNode<T> *find(int key);

    UnionFind(void (* func)(UFNode<T>&, UFNode<T>&), bool (*compare_objs)(std::shared_ptr<UFNode<T>>* playerNode, int id));
    void (* blackBox)(UFNode<T>&, UFNode<T>&);

private:
    void compress(UFNode<T> *node, UFNode<T> *root);

    UFNode<T> & find_internal(int key);
    HashTable<std::shared_ptr<UFNode<T>>> m_hashTable;
};

template<class T>
void UnionFind<T>::unify(UFNode<T> &biggerSet, UFNode<T>&smallerSet) {
    smallerSet.parent = &biggerSet;
    biggerSet.height += smallerSet.height;
}

template<class T>
UFNode<T>& UnionFind<T>::find_internal(int key) {
    UFNode<T>* set = m_hashTable.find(key)->get(); // what does it do
    UFNode<T>* root = getRoot(set);
    compress(set, root);
    return *root;
}

template<class T>
UFNode<T> *UnionFind<T>::getRoot(UFNode<T> *setA) {
    UFNode<T>* root = setA;
    while(root != root->parent) {
        root = root->parent;
    }
    return root;
}

template<class T>
void UnionFind<T>::compress(UFNode<T> *node, UFNode<T> *root) {
    if(node->parent == root) return;
    compress(node->parent, root);
    blackBox(*node, *node->parent);
    node->parent = root;
}

template<class T>
UFNode<T>& UnionFind<T>::insert(int key, T& obj) {
    auto node = std::make_shared<UFNode<T>>(obj);
    std::pair<int, std::shared_ptr<UFNode<T>>> pa{key, node};
    m_hashTable.insert(key, node);
    return *node;
}

template<class T>
bool UnionFind<T>::isObjectExist(int key) {
    if(m_hashTable.find(key) == nullptr) {
        return false;
    }
    return true;
}

template<class T>
UFNode<T> *UnionFind<T>::find(int key) {
    if(isObjectExist(key)) {
        return &find_internal(key);
    }
    return nullptr;
}

template<class T>
UnionFind<T>::UnionFind(void (*func)(UFNode<T> &, UFNode<T> &),
                        bool (*compare_objs)(std::shared_ptr<UFNode<T>>* playerNode, int id)) :
    blackBox{func},
    m_hashTable{compare_objs}
{}


#endif //WET2_UNIONFIND_H
