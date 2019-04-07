/*
 * HTree: a class to represent a tree node with two values: a key
 * and a value.
 */

#include "htree.hh"
#include <cassert>

HTree::HTree(int a /*key*/,
            uint64_t b /*value*/,
            tree_ptr_t c /*left = nullptr*/,
            tree_ptr_t d /*right = nullptr*/){
    key_ = a;
    value_ = b;
    left_ = c;
    right_ = d;
}

HTree::HTree(){             // default constructor
    key_ = 0;
    value_ = 0;
    left_ = nullptr;
    right_ = nullptr;
}

HTree::~HTree() = default;            // Delete


int HTree::get_key() const{    // Return key in current node
    return key_;
}
uint64_t HTree::get_value() const{ // Return value in current node
    return value_;
}      

// Return the child of this node indicated by dir.
// If the child is nullptr (current node is a leaf), returns nullptr.
HTree::tree_ptr_t HTree::get_child(Direction dir) const{
    if (dir == Direction::LEFT){
        return left_;
    }
    else{
        return right_;
    }
}

bool HTree::find_key(int key) const{ // Call only if the current tree doesn't have the key
    
    return (key_ == key
        || (left_  && (*left_).find_key(key))
        || (right_ && (*right_).find_key(key)));
}


// Return a list of directions from root to a node of a given key.
// Crashes (with an assert) if key not contained in this tree
HTree::path_t HTree::path_to(int key) const{ // I might be able to do this simpler if I'm allowed to add to HTree::Directions

    assert((*this).find_key(key));

    if (key_ == key) {
        path_t list;
        return list;
    } 
    else if (left_ && (*left_).find_key(key)) {
        path_t list = (*left_).path_to(key);
        list.push_front(Direction::LEFT);
        return list;
    } 
    else {
        path_t list = (*right_).path_to(key);
        list.push_front(Direction::RIGHT);
        return list;
    }
}