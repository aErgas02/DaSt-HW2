//
// Created by Meitar Basson on 02/01/2023.
//

#ifndef WET2_UFNODE_H
#define WET2_UFNODE_H

template <class T>
struct UFNode {
public:
    T val;

    UFNode() = default;
    UFNode<T> *parent;
    int height = 0;

    explicit UFNode(const T& val) :
            val(val),
            parent(this)
    {}

    void updateSheker() {
    }
};

#endif //WET2_UFNODE_H
