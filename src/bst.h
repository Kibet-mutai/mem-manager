#ifndef BST_H
#define BST_H

// Node
struct BiNode {
    unsigned long value; // linear address
    unsigned long index; // index into bitmap [0, nbits-1]
    unsigned long n_reserved; // number of bits reserved

    struct BiNode* left;
    struct BiNode* right;
    BiNode(unsigned long val)
        : value(val)
        , left(nullptr)
        , right(nullptr)
    {
    }
    BiNode() { }
    ~BiNode() { }
};

class BinarySearchTree {
public:
    struct BiNode* root_ptr;
    BinarySearchTree()
        : root_ptr(nullptr)
    {
    }
    void insert_node(struct BiNode** link, unsigned long value);
    void insert_node_ptr(struct BiNode** link, struct BiNode* ptr);

    struct BiNode* find_node(struct BiNode* link, unsigned long value);
    struct BiNode* delete_smallest_node(struct BiNode** link);
    void delete_node(struct BiNode** link, unsigned long value);
    void delete_all(struct BiNode** link);

    void print_tree(struct BiNode* link, int level);
    int get_height(struct BiNode* link);
    ~BinarySearchTree() { delete_all(&(root_ptr)); }
};

#endif // BST_H
