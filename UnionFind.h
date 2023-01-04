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
    UFNode<T>& insert(int key, T& obj);
    void unify(UFNode<T> &setBuyer, UFNode<T> &setBought);
    bool isPlayerExist(int key);
    UFNode<T> *getRoot(UFNode<T> *setA);
    UFNode<T> *find(int key);

private:
    void UnionBySize(UFNode<T> &biggerSet, UFNode<T> &smallerSet);
    void compress(UFNode<T> *node, UFNode<T> *root);

    UFNode<T> & find_internal(int key);
    std::unordered_map<int, std::shared_ptr<UFNode<T>>> m_hashTable;
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
void UnionFind<T>::UnionBySize(UFNode<T> &biggerSet, UFNode<T> &smallerSet) {
    smallerSet.parent = &biggerSet;
    biggerSet.height++;
}

template<class T>
UFNode<T>& UnionFind<T>::find_internal(int key) {
    std::shared_ptr<UFNode<T>> set = m_hashTable.find(key)->second;
    UFNode<T>* root = getRoot(set.get());

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
        blackBox(node->val, node->parent->val);
        UFNode<T>* tmp = node;
        node = node->parent;
        tmp->parent = root;
    }
}

template<class T>
UFNode<T>& UnionFind<T>::insert(int key, T& obj) {
    auto node = std::make_shared<UFNode<T>>(obj);
    std::pair<int, std::shared_ptr<UFNode<T>>> pa{key, node};
    m_hashTable.insert(pa);

    return *node;
}

template<class T>
bool UnionFind<T>::isPlayerExist(int key) {
    if(m_hashTable.find(key) == m_hashTable.end()) {
        return false;
    }
    return true;
}

template<class T>
UFNode<T> *UnionFind<T>::find(int key) {
    if(isPlayerExist(key)) {
        return &find_internal(key);
    }
    return nullptr;
}


#endif //WET2_UNIONFIND_H
