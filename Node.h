#ifndef MAIN23A1_CPP_NODE_H
#define MAIN23A1_CPP_NODE_H

#endif //MAIN23A1_CPP_NODE_H

template <class T>
struct Node {
public:
    T val;

    struct Node *left = nullptr;
    struct Node *right = nullptr;
    struct Node *parent = nullptr;

    int height = 0; // Added as leaf.
    int bf = 0;

    explicit Node(T val) : val(val)
    {}

    explicit Node(T val, Node *parent) : val(val), parent(parent)
    {}

    bool is_right_child();

    ~Node()= default;

    Node *get_biggest_child() {
        Node* node = this;
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    Node *get_smallest_child(){
        Node* node = this;
        while(node->left != nullptr)
            node = node->left;
        return node;
    }
};

template<class T>
bool Node<T>::is_right_child() {
    if (parent != nullptr) {
        return parent->right == this;
    }
    return false;
}

template<class T>
int get_height(Node<T> *node) {
    return (node == nullptr) ? -1 : node->height;
}

template<class T>
void update_height(Node<T> *node) {
    if (node == nullptr) return;
    int left_h = get_height(node->left);
    int right_h = get_height(node->right);
    node->height = ((left_h > right_h) ? left_h : right_h) + 1;
}

template<class T>
void update_balance_factor(Node<T> *node) {
    if (node == nullptr) return;
    node->bf = get_height(node->left) - get_height(node->right);
}

template<class T>
Node<T> *perform_rotation(Node<T> *node) {
    if (node->bf == 2) {
        return node->left->bf > -1 ? LL(node) : LR(node);
    } else if (node->bf == -2) {
        return node->right->bf < 1 ? RR(node) : RL(node);
    }
    return node;
}

template<class T>
Node<T> *LL(Node<T> *node) {
    Node<T> *new_root, *old_root, *p;


    // Hold the data
    old_root = node;
    new_root = old_root->left;
    p = old_root->parent;

    // Perform LL
    old_root->left = new_root->right;
    if (old_root->left != nullptr) {
        old_root->left->parent = old_root;
    }
    old_root->parent = new_root;

    new_root->right = old_root;
    new_root->parent = p;

    update_height(old_root);
    update_balance_factor(old_root);
    update_height(new_root);
    update_balance_factor(new_root);

    return new_root;
}

template<class T>
Node<T> *RR(Node<T> *node) {
    Node<T> *new_root, *old_root, *p;

    // Hold the data
    old_root = node;
    new_root = old_root->right;
    p = old_root->parent;

    // Perform RR
    old_root->right = new_root->left;
    if (old_root->right != nullptr) {
        old_root->right->parent = old_root;
    }
    old_root->parent = new_root;

    new_root->left = old_root;
    new_root->parent = p;

    update_height(old_root);
    update_balance_factor(old_root);
    update_height(new_root);
    update_balance_factor(new_root);

    return new_root;
}

template<class T>
Node<T> *LR(Node<T> *node) {
    Node<T> *left = node->left;

    // Rotate pointers with RR and LL
    node->left = RR(left);
    return (LL(node));
}

template<class T>
Node<T> *RL(Node<T> *node) {
    Node<T> *right = node->right;

    // Rotate pointers with RR and LL
    node->right = LL(right);
    return (RR(node));
}