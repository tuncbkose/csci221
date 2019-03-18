/*
 * Tree: A simple recursive data structure to hold keys and values.
 */

#include "tree.hh"
#include <cassert>
#include <iostream>

tree_ptr_t  create_tree(const key_t& key,
                        const value_t& value,
                        tree_ptr_t left /*= nullptr*/,
                        tree_ptr_t right /*= nullptr*/)
{
    tree_ptr_t tp = new Tree({key, value, left, right});
    return tp;
}

void destroy_tree(tree_ptr_t tree)  // recursively deletes all trees associated with a root tree
{
    if (!tree){
        return;
    }
    destroy_tree(tree->left_);
    destroy_tree(tree->right_);
    delete tree;
}

const std::string null {NULL};

std::string path_to(tree_ptr_t tree, key_t key)
{
    std::string path {};

    if (tree == nullptr){                   // failed exit condition
        return null;
    }
    if (tree->key_ == key){                 // successful exit condition
        return path;
    }
    if (path_to(tree->left_, key) != null){
        path = "L" + path_to(tree->left_, key);
    }
    else if (path_to(tree->right_, key) != null){
        path = "R" + path_to(tree->right_, key);
    }
    assert(path.length() > 0);
    return path;
}

tree_ptr_t give_pointer(tree_ptr_t tree, std::string path)  // path input is expected to be 1 letter
{
    if (path == "L"){
        return tree->left_;
    }
    else if (path == "R"){
        return tree->right_;
    }
    else{       // determines invalid inputs
        return nullptr;
    }
}

tree_ptr_t node_at(tree_ptr_t tree, std::string path)     // crashes on invalid input, should return nullptr instead
{
    if (tree == nullptr){
        return nullptr;
    }
    else if (path.length() == 0){
        return tree;
    }
    else if (path.length() == 1){
        return give_pointer(tree, path);
    }
    else{
        std::string letter = path.substr(0,1);
        path = path.substr(1);
        return node_at(give_pointer(tree, letter), path); //when I tried using .begin() instead of .substr(0, 1) I got a conversion error. Could you explain what exact problem I was having there?
    }
}
