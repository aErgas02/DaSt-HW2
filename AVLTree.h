#ifndef MAIN23A1_CPP_AVLTREE_H
#define MAIN23A1_CPP_AVLTREE_H

#include "Node.h"
#include "exceptions.h"

#define RIGHT 1
#define LEFT -1
#define BULLSEYE 0

template<class T>
class AVLTree {

private:
    Node<T> *root = nullptr;
    T m_max_val{};
    int (*compare)(T *, T *);
    int tree_size = 0;

protected:
    bool is_object_exists(Node<T> *pRoot, T obj);
    Node<T> *find_object(Node<T> *pRoot, T obj);
    Node<T> *insert(Node<T> *pRoot, T obj);
    Node<T> *delete_node(Node<T> *pRoot, T obj);
    Node<T> *update_tree(Node<T> *node);
    void recursive_delete(Node<T> *d_node);
    void update_max();
    int in_order_internal(Node<T> *pRoot, T *arr, int n, int index = 0);

public:
    const Node<T> *get_root() {
        return root;
    }
    Node<T> *delete_node(T obj);
    Node<T> *insert(T obj);
    bool object_exists(T obj);
    Node<T> *find_object(T obj);
    void update_tree_external(Node<T> *pRoot);
    explicit AVLTree(int (*compare)(T *, T *)) : compare(compare) {}
    ~AVLTree() {
        recursive_delete(this->root);
    }
    T get_max();
    int get_tree_size();
    void set_new_head(Node<T> * new_head, int size){
        this->root = new_head;
        this->tree_size = size;
        if (root != nullptr) {
            update_max();
        }
    }
    void in_order(T *arr, int n);
    int countNodes(const Node<T> * node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodes(node->left) + countNodes(node->right);
    }
};


template<class T>
void AVLTree<T>::recursive_delete(Node<T> *d_node) {
    if (d_node == nullptr) {
        return;
    }
    recursive_delete(d_node->left);
    recursive_delete(d_node->right);
    delete d_node;
}


template<class T>
bool AVLTree<T>::object_exists(T obj) {
    return is_object_exists(this->root, obj);
}

template<class T>
Node<T> *AVLTree<T>::insert(T obj) {
    root = insert(root, obj);
    update_max();
    tree_size++;
    return root;
}

template<class T>
Node<T> *AVLTree<T>::insert(Node<T> *pRoot, T obj) {
    if (pRoot == nullptr) {
        return new Node<T>(obj);
    }
    if (compare(&obj, &pRoot->val) == LEFT) {
        pRoot->left = insert(pRoot->left, obj);
        if (pRoot->left != nullptr) {
            pRoot->left->parent = pRoot;
        }
    } else if (compare(&obj, &pRoot->val) == RIGHT) {
        pRoot->right = insert(pRoot->right, obj);
        if (pRoot->right != nullptr) {
            pRoot->right->parent = pRoot;
        }
    } else {
        throw AlreadyExists{};
    }
    return update_tree(pRoot);
}

template<class T>
bool AVLTree<T>::is_object_exists(Node<T> *pRoot, T obj) {
    if (pRoot == nullptr) { return false; }

    int comparison = compare(&obj, &pRoot->val);

    // New object was found
    if (comparison == BULLSEYE) {
        return true;
    } else if (comparison == LEFT) {
        // Check left branch
        return is_object_exists(pRoot->left, obj);
    } else {
        // Check right branch
        return is_object_exists(pRoot->right, obj);
    }
}

template<class T>
Node<T> *AVLTree<T>::delete_node(Node<T> *pRoot, T obj) {

    if (pRoot->left == nullptr && pRoot->right == nullptr) {
        tree_size--;
        delete pRoot;
        return nullptr;
    }

    Node<T> *node_to_delete = nullptr;

    if (compare(&obj, &pRoot->val) == LEFT) {
        pRoot->left = delete_node(pRoot->left, obj);
        if (pRoot->left != nullptr) {
            pRoot->left->parent = pRoot;
        }
    } else if (compare(&obj, &pRoot->val) == RIGHT) {
        pRoot->right = delete_node(pRoot->right, obj);
        if (pRoot->right != nullptr) {
            pRoot->right->parent = pRoot;
        }
    } else {
        // In this case it's some root who has children
        if (pRoot->left != nullptr) {
            node_to_delete = pRoot->left->get_biggest_child();
            pRoot->val = node_to_delete->val;
            pRoot->left = delete_node(pRoot->left, node_to_delete->val);
            if (pRoot->left != nullptr) {
                pRoot->left->parent = pRoot;
            }
        } else {
            node_to_delete = pRoot->right->get_smallest_child();
            pRoot->val = node_to_delete->val;
            pRoot->right = delete_node(pRoot->right, node_to_delete->val);
            if (pRoot->right != nullptr) {
                pRoot->right->parent = pRoot;
            }
        }
    }

    return update_tree(pRoot);
}

template<class T>
Node<T> *AVLTree<T>::delete_node(T obj) {
    if (is_object_exists(root, obj)) {
        root = delete_node(root, obj);
        if (root) { update_max();} else m_max_val = nullptr;
        return root;
    }
    return nullptr;
}

template<class T>
Node<T> *AVLTree<T>::update_tree(Node<T> *node) {
    if (node) {
        // Go up through the tree until we reach the root and update each node
        update_height(node);
        update_balance_factor(node);
        auto res = perform_rotation(node);
        update_height(node->left);
        update_height(node->right);
        update_height(node);
        update_balance_factor(node);
        return res;
    }
    return nullptr;
}

template<class T>
Node<T> *AVLTree<T>::find_object(Node<T> *pRoot, T obj) {
    if (pRoot == nullptr) { return nullptr; }

    int comparison = compare(&obj, &pRoot->val);

    // New object was found
    if (comparison == BULLSEYE) {
        return pRoot;
    } else if (comparison == LEFT) {
        // Check left branch
        return find_object(pRoot->left, obj);
    } else {
        // Check right branch
        return find_object(pRoot->right, obj);
    }
}

template<class T>
Node<T> *AVLTree<T>::find_object(T obj) {
    return find_object(this->root, obj);
}

template<class T>
void AVLTree<T>::update_tree_external(Node<T> *pRoot) {
    update_tree(pRoot);
}

template<class T>
void AVLTree<T>::update_max() {
    m_max_val = root->get_biggest_child()->val;
}

template<class T>
T AVLTree<T>::get_max() {
    return this->m_max_val;
}

template<class T>
int AVLTree<T>::get_tree_size() {
    return tree_size;
}

template<class T>
void AVLTree<T>::in_order(T *arr, int n) {
    if (arr != nullptr)
        in_order_internal(root, arr, n);
}

template<class T>
int AVLTree<T>::in_order_internal(Node<T> *pRoot, T *arr, int n, int index) {
    if (pRoot == nullptr)
        return index;

    index = in_order_internal(pRoot->left, arr, n, index);
    if (index >= n) return index; /* check */
    arr[index++] = pRoot->val;

    return in_order_internal(pRoot->right, arr, n, index);
}

#endif //MAIN23A1_CPP_AVLTREE_H
