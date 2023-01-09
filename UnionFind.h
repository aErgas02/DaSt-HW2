//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_UNIONFIND_H
#define WET2_UNIONFIND_H

#include "UFNode.h"
#include <unordered_map>
#include <utility>
#include <memory>

template <class T>
class UnionFind {

public:
    void (* blackBox)(UFNode<T>&, UFNode<T>&);
    UFNode<T>& insert(int key, T& obj);
    void unify(UFNode<T> *setBuyer, UFNode<T> *setBought);
    bool isObjectExist(int key);
    UFNode<T> *getRoot(UFNode<T> *setA);
    UFNode<T> *find(int key);

private:
    void unionBySize(UFNode<T> *biggerSet, UFNode<T> *smallerSet);
    void compress(UFNode<T> *node, UFNode<T> *root);

    UFNode<T> & find_internal(int key);
    std::unordered_map<int, std::shared_ptr<UFNode<T>>> m_hashTable;
};

template<class T>
void UnionFind<T>::unify(UFNode<T> *setBuyer, UFNode<T> *setBought) {
    if(setBought == nullptr || setBuyer == nullptr) {
        return; // TODO: isn't supposed to get here
    } else if(setBuyer->height >= setBought->height) {
        unionBySize(setBuyer, setBought);
    } else {
        unionBySize(setBought, setBuyer);
        setBought->parent = setBuyer; // we created two pointers pointing to each other
    }
}

template<class T>
void UnionFind<T>::unionBySize(UFNode<T> *biggerSet, UFNode<T> *smallerSet) {
    smallerSet->parent = biggerSet;
    biggerSet->height++; // why grow by 1?
}

template<class T>
UFNode<T>& UnionFind<T>::find_internal(int key) {
    UFNode<T>* set = m_hashTable.find(key)->second.get(); // what does it do
    UFNode<T>* root = getRoot(set);
//    compress(set, root);
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
    blackBox(*node, *root);
    node->parent = root;
}

template<class T>
UFNode<T>& UnionFind<T>::insert(int key, T& obj) {
    auto node = std::make_shared<UFNode<T>>(obj);
    std::pair<int, std::shared_ptr<UFNode<T>>> pa{key, node};
    m_hashTable.insert(pa);

    return *node;
}

template<class T>
bool UnionFind<T>::isObjectExist(int key) {
    if(m_hashTable.find(key) == m_hashTable.end()) {
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


#endif //WET2_UNIONFIND_H
