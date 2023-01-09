//
// Created by Meitar Basson on 09/01/2023.
//

#ifndef WET2_PAIR_H
#define WET2_PAIR_H

template<class T>
struct Pair {

private:
    int i = 0;
    T val;

public:
    Pair(int id, T val) : i(i), val(val) {}
    Pair()= default;

    int get_first() const {
        return this->i;
    }

    int get_second() const {
        return this->val;
    }

};

#endif //WET2_PAIR_H
