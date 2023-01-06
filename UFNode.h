#ifndef WET2_UFNODE_H
#define WET2_UFNODE_H

template <class T>
struct UFNode {
public:

    T val;
    UFNode<T> *parent;
    int height = 0;

    UFNode() = default;
    explicit UFNode(const T& val) :
            val(val),
            parent(this)
    {}
};

#endif //WET2_UFNODE_H
