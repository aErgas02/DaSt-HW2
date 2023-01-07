#ifndef MAIN23A1_CPP_AVLTREE_H
#define MAIN23A1_CPP_AVLTREE_H

#include "TreeNode.h"
#include "exceptions.h"

#define RIGHT 1
#define LEFT -1
#define BULLSEYE 0

template<class T>
class AVLTree {

private:
    TreeNode<T> *root = nullptr;
    T m_max_val{};
    int (*compare)(T *, T *);
    int tree_size = 0;

protected:
    bool is_object_exists(TreeNode<T> *pRoot, T obj);
    TreeNode<T> *find_object(TreeNode<T> *pRoot, T obj);
    TreeNode<T> *insert(TreeNode<T> *pRoot, T obj);
    TreeNode<T> *delete_node(TreeNode<T> *pRoot, T obj);
    TreeNode<T> *update_tree(TreeNode<T> *node);
    void recursive_delete(TreeNode<T> *d_node);
    void update_max();
    int in_order_internal(TreeNode<T> *pRoot, T *arr, int n, int index = 0);
    TreeNode<T> *select_internal(int k, TreeNode<T> *pRoot);

public:
    const TreeNode<T> *get_root() const {
        return root;
    }
    TreeNode<T> *delete_node(T obj);
    TreeNode<T> *insert(T obj);
    TreeNode<T> *find_object(T obj);
    TreeNode<T> *select(int k);
    bool object_exists(T obj);

    void update_tree_external(TreeNode<T> *pRoot);
    explicit AVLTree(int (*compare)(T *, T *)) : compare(compare) {}
    ~AVLTree() {
        recursive_delete(this->root);
    }
    int get_size(){ return this->tree_size;}
};


template<class T>
void AVLTree<T>::recursive_delete(TreeNode<T> *d_node) {
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
TreeNode<T> *AVLTree<T>::insert(T obj) {
    root = insert(root, obj);
    update_max();
    tree_size++;
    return root;
}

template<class T>
TreeNode<T> *AVLTree<T>::insert(TreeNode<T> *pRoot, T obj) {
    if (pRoot == nullptr) {
        return new TreeNode<T>(obj);
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
bool AVLTree<T>::is_object_exists(TreeNode<T> *pRoot, T obj) {
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
TreeNode<T> *AVLTree<T>::delete_node(TreeNode<T> *pRoot, T obj) {

    if (pRoot->left == nullptr && pRoot->right == nullptr) {
        tree_size--;
        delete pRoot;
        return nullptr;
    }

    TreeNode<T> *node_to_delete = nullptr;

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
TreeNode<T> *AVLTree<T>::delete_node(T obj) {
    if (is_object_exists(root, obj)) {
        root = delete_node(root, obj);
        if (root) { update_max();} else m_max_val = nullptr;
        return root;
    }
    return nullptr;
}

template<class T>
TreeNode<T> *AVLTree<T>::update_tree(TreeNode<T> *node) {
    if (node) {
        // Go up through the tree until we reach the root and update each node
        update_height(node);
        update_balance_factor(node);
        update_w(node);
        auto res = perform_rotation(node);
        update_height(node->left);
        update_height(node->right);
        update_height(node);
        update_balance_factor(node);
        update_w(node->left);
        update_w(node->right);
        update_w(node);
        return res;
    }
    return nullptr;
}

template<class T>
TreeNode<T> *AVLTree<T>::find_object(TreeNode<T> *pRoot, T obj) {
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
TreeNode<T> *AVLTree<T>::find_object(T obj) {
    return find_object(this->root, obj);
}

template<class T>
void AVLTree<T>::update_tree_external(TreeNode<T> *pRoot) {
    update_tree(pRoot);
}

template<class T>
void AVLTree<T>::update_max() {
    m_max_val = root->get_biggest_child()->val;
}

template<class T>
int AVLTree<T>::in_order_internal(TreeNode<T> *pRoot, T *arr, int n, int index) {
    if (pRoot == nullptr)
        return index;

    index = in_order_internal(pRoot->left, arr, n, index);
    if (index >= n) return index; /* check */
    arr[index++] = pRoot->val;

    return in_order_internal(pRoot->right, arr, n, index);
}

template<class T>
TreeNode<T> *AVLTree<T>::select(int k){
    if(k < 0 || k >= this->tree_size || this->tree_size == 0) return nullptr; //might not be necessary
    return select_internal(k + 1, this->root);
}

template<class T>
TreeNode<T> *AVLTree<T>::select_internal(int k, TreeNode<T> *pRoot){
    if(pRoot == nullptr) return nullptr;

    int nodes_in_left = get_w(pRoot->left);

    if(nodes_in_left == k - 1) return pRoot; //exactly found the k-th node

    else if(nodes_in_left > k-1) {
        return select_internal(k, pRoot->left);
    } else {
        return select_internal(k - nodes_in_left - 1, pRoot->right);
    }
}


#endif //MAIN23A1_CPP_AVLTREE_H
