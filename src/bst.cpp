#include "bst.h"
#include <iostream>
#include <stdlib.h>

void BinarySearchTree::insert_node(BiNode** link, unsigned long value)
{
    if (*link == nullptr) {
        *link = new BiNode(value);
        std::cout << "BinarySearchTree::insert_node(): Inserted node: "
                  << value << '\n';
    } else if (value < (*link)->value) {
        std::cout << "BinarySearchTree::insert_node(): Moving left: "
                  << value << '\n';
        insert_node(&((*link)->left), value);
    } else {
        std::cout << "BinarySearchTree::insert_node(): Moving right: "
                  << value << '\n';
        insert_node(&((*link)->right), value);
    }
}

void BinarySearchTree::insert_node_ptr(struct BiNode** link, struct BiNode* ptr)
{
    if (*link == nullptr) {
        (*link) = (struct BiNode*)malloc(sizeof(struct BiNode));
        (*(*link)).value = ptr->value;
        (*(*link)).index = ptr->index;
        (*(*link)).n_reserved = ptr->n_reserved;
        (*(*link)).left = nullptr;
        (*(*link)).right = nullptr;

        std::cout << "BinarySearchTree::insert_node(): inserting value = "
                  << ptr->value << '\n';
    } else if ((*ptr).value < (*(*link)).value) {

        std::cout << "BinarySearchTree::insert_node(): moving left value = "
                  << ptr->value << '\n';
        insert_node_ptr(&(*(*link)).left, ptr);
    } else {
        std::cout << "BinarySearchTree::insert_node(): moving right value = "
                  << ptr->value << '\n';
        insert_node_ptr(&(*(*link)).right, ptr);
    }
    return;
}

struct BiNode* BinarySearchTree::find_node(struct BiNode* link, unsigned long value)
{
    if (link == nullptr)
        return nullptr;
    else if ((*link).value == value)
        return link;
    else if (value >= link->value)
        return find_node(link->right, value);
    else {
        return find_node(link->left, value);
    }
}

struct BiNode* BinarySearchTree::delete_smallest_node(struct BiNode** link)
{
    if ((*(*link)).left != nullptr) {
        return delete_smallest_node(&((*(*link)).left));
    } else {
        struct BiNode* temp;
        temp = *link;
        (*link) = (*(*link)).right;
        return temp;
    }
}

void BinarySearchTree::delete_all(struct BiNode** link)
{
    if (*link == nullptr)
        return;

    delete_all(&(*(*link)).right);
    delete_all(&(*(*link)).left);
    std::cout << "BinarySearchTree::insert_node(): Freeing All Nodes value = "
              << (*(*link)).value << '\n';
    delete (*link);
    *link = nullptr;
    return;
}

void BinarySearchTree::delete_node(struct BiNode** link, unsigned long value)
{
    if ((*link) == nullptr)
        return;
    if (value < (*(*link)).value) {

        delete_node(&((*(*link)).left), value);
    } else if (value > (*(*link)).value) {
        delete_node(&((*(*link)).right), value);
    } else {
        struct BiNode* temp;
        temp = *link;

        if ((*(*link)).right == nullptr) {
            *link = (*(*link)).left;
        } else if ((*(*link)).left == nullptr) {
            *link = (*(*link)).right;
        } else {
            temp = delete_smallest_node(&((*(*link)).right));
            (*(*link)).value = temp->value;
        }
        free(temp);
    }
    return;
}

void BinarySearchTree::print_tree(struct BiNode* link, int level)
{
    int i;
    if (link == nullptr)
        return;

    print_tree((*link).right, level + 1);

    for (i = 0; i < level; ++i) {
        std::cout << "-";
    }
    std::cout << "(" << link->value << ")" << '\n';

    print_tree((*link).left, level + 1);

    return;
}

int BinarySearchTree::get_height(struct BiNode* link)
{
    if (link == nullptr)
        return 0;

    int u = get_height(link->left);
    int v = get_height(link->right);

    return 1 + std::max(u, v);
}

/*int main(int argc, char* argv[])*/
/*{*/
/*    BinarySearchTree bst;*/
/**/
/*    bst.root_ptr = nullptr;*/
/**/
/*    bst.insert_node(&(bst.root_ptr), 10);*/
/*    std::cout << "BinarySearchTree::get_height(): " << bst.get_height((bst.root_ptr))*/
/*              << '\n';*/
/*    //    bst.delete_node(&(bst.root_ptr), bst.root_ptr->value);*/
/*    //  bst.print_tree(bst.root_ptr, 2);*/
/*    struct BiNode binode;*/
/*    binode.value = 12;*/
/*    binode.n_reserved = 3;*/
/*    binode.index = 4;*/
/*    bst.insert_node_ptr(&(bst.root_ptr), &binode);*/
/*    bst.print_tree(bst.root_ptr, 2);*/
/*    return 0;*/
/*}*/
