#include <iostream>
#include "UnionFind.h"
#include "Array.h"

void blackbox() {
    printf("Hello world");
}
int main() {

    UnionFind<int> a = UnionFind<int>();
    auto *b = new UFNode<int>(3);
    auto *c = new UFNode<int>(5);
    a.blackBox = blackbox;

    a.insert(1,b->val);
    a.insert(2, c->val);

    a.unify(*b, *c);
    a.find(2);

    return 0;
}
