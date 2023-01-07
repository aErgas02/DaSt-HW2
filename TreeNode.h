#ifndef MAIN23A1_CPP_NODE_H
#define MAIN23A1_CPP_NODE_H

template <class T>
struct TreeNode {
public:
    T val;

    struct TreeNode *left = nullptr;
    struct TreeNode *right = nullptr;
    struct TreeNode *parent = nullptr;

    int height = 0; // Added as leaf.
    int bf = 0;
    int w = 0;

    explicit TreeNode(T val) : val(val)
    {}

    explicit TreeNode(T val, TreeNode *parent) : val(val), parent(parent)
    {}

    TreeNode *get_biggest_child() {
        TreeNode* node = this;
        while (node->right != nullptr)
            node = node->right;
        return node;
    }

    TreeNode *get_smallest_child(){
        TreeNode* node = this;
        while(node->left != nullptr)
            node = node->left;
        return node;
    }
};

template<class T>
int get_height(TreeNode<T> *node) {
    return (node == nullptr) ? -1 : node->height;
}

template<class T>
void update_height(TreeNode<T> *node) {
    if (node == nullptr) return;
    int left_h = get_height(node->left);
    int right_h = get_height(node->right);
    node->height = ((left_h > right_h) ? left_h : right_h) + 1;
}

template<class T>
void update_balance_factor(TreeNode<T> *node) {
    if (node == nullptr) return;
    node->bf = get_height(node->left) - get_height(node->right);
}

template<class T>
void update_w(TreeNode<T> * node){
    if(node == nullptr) return;
    else if(node->left != nullptr && node->right != nullptr) { node->w = node->left->w + node->right->w + 1;}
    else if(node->left != nullptr) { node->w = node->left->w + 1;}
    else if(node->right != nullptr) { node->w = node->right->w + 1;}
    else { node->w = 1;}
}

template<class T>
int get_w(TreeNode<T> *node){
    if(node == nullptr) return 0;
    return node->w;
}

template<class T>
TreeNode<T> *perform_rotation(TreeNode<T> *node) {
    if (node->bf == 2) {
        return node->left->bf > -1 ? LL(node) : LR(node);
    } else if (node->bf == -2) {
        return node->right->bf < 1 ? RR(node) : RL(node);
    }
    return node;
}

template<class T>
TreeNode<T> *LL(TreeNode<T> *node) {
    TreeNode<T> *new_root, *old_root, *p;


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
    update_w(old_root);

    update_height(new_root);
    update_balance_factor(new_root);
    update_w(new_root);

    return new_root;
}

template<class T>
TreeNode<T> *RR(TreeNode<T> *node) {
    TreeNode<T> *new_root, *old_root, *p;

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
    update_w(old_root);

    update_height(new_root);
    update_balance_factor(new_root);
    update_w(new_root);

    return new_root;
}

template<class T>
TreeNode<T> *LR(TreeNode<T> *node) {
    TreeNode<T> *left = node->left;

    // Rotate pointers with RR and LL
    node->left = RR(left);
    return (LL(node));
}

template<class T>
TreeNode<T> *RL(TreeNode<T> *node) {
    TreeNode<T> *right = node->right;

    // Rotate pointers with RR and LL
    node->right = LL(right);
    return (RR(node));
}

#endif //MAIN23A1_CPP_NODE_H