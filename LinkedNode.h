//
// Created by ariel on 1/4/2023.
//

#ifndef WET2_LINKEDNODE_H
#define WET2_LINKEDNODE_H
template<class T>
class LinkedNode{
private:
    LinkedNode* next;
    T val;
public:
    explicit LinkedNode(T obj) : next{nullptr}, val{obj} {}
    ~LinkedNode() = default;
    LinkedNode* get_next() {return next;}
    void set_next(LinkedNode* n) {next = n;}
    T* get_val() {return &val;}

};
#endif //WET2_LINKEDNODE_H