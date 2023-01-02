//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include "UFNode.h"
#include <unordered_map>
#include <utility>
template <class T>
class UnionFind {

public:
    void (* blackBox)(T&, T&);
    void insert(int key, T obj);
    void unify(UFNode<T> &setBuyer, UFNode<T> &setBought);
    bool isPlayerExist(int key);
    UFNode<T> & find(int key);

private:
    void UnionBySize(UFNode<T> &biggerSet, UFNode<T> &smallerSet);
    void compress(UFNode<T> *node, UFNode<T> *root);

    UFNode<T> * getRoot(UFNode<T> *setA);
    UFNode<T> & getBiggerSet(UFNode<T> &setA, UFNode<T> &setB);

    std::unordered_map<int, UFNode<T>> m_hashTable;
};

template<class T>
void UnionFind<T>::unify(UFNode<T> &setBuyer, UFNode<T> &setBought) {
    if(setBuyer.height >= setBought.height) {
        UnionBySize(setBuyer, setBought);
    } else {
        UnionBySize(setBought, setBuyer);
        setBought.parent = &setBuyer;
    }
}

template<class T>
UFNode<T> &UnionFind<T>::getBiggerSet(UFNode<T> &setA, UFNode<T> &setB) {
    if(setA.height >= setB.height)
        return setA;
    return setB;
}

template<class T>
void UnionFind<T>::UnionBySize(UFNode<T> &biggerSet, UFNode<T> &smallerSet) {
    smallerSet.parent = &biggerSet;
}

template<class T>
UFNode<T>& UnionFind<T>::find(int key) {
    UFNode<T> set = m_hashTable[key];
    UFNode<T>* root = getRoot(&set);

    return *root;
}

template<class T>
UFNode<T> *UnionFind<T>::getRoot(UFNode<T> *setA) {
    UFNode<T>* root = setA;
    while(root != setA->parent) {
        root = setA->parent;
    }
    compress(setA, root);
    return root;
}

template<class T>
void UnionFind<T>::compress(UFNode<T> *node, UFNode<T> *root) {
    while(node->parent != root) {
        blackBox(node, node->parent);
        UFNode<T>* tmp = node;
        node = node->parent;
        tmp->parent = root;
    }
}

template<class T>
void UnionFind<T>::insert(int key, T obj) {
    UFNode<T> node{obj};
    std::pair<int, UFNode<T>> pa{key, node};
    m_hashTable.insert(pa);
}

template<class T>
bool UnionFind<T>::isPlayerExist(int key) {
    if(m_hashTable.find(key) == m_hashTable.end()) {
        return false;
    }
    return true;
}


#endif //WET2_UNIONFIND_H
