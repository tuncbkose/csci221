/*
 * HForest: a class to represent a collection of HTrees.
 */

/*
 * Forest is a vector that stores pairs of key to a tree and its pointer.
 */

#include "hforest.hh"
#include <algorithm>

// helper function for heap methods
// returns if tree1 is bigger than tree2
static bool cmp(HForest::tree_ptr_t p1, HForest::tree_ptr_t p2){
    return p1->get_value() > p2->get_value();
}


// Constructor
HForest::HForest() = default;

// Destructor
HForest::~HForest() = default;

int HForest::size() const {
    return forest_.size();
}

// Adds a tree to the forest vector and includes it in the heap
void HForest::add_tree(tree_ptr_t t){
    forest_.push_back(t);
    std::push_heap(forest_.begin(), forest_.end(), cmp);
}

// Removes the lowest-value tree from the heap and the forest vector
HForest::tree_ptr_t HForest::pop_tree() {
    tree_ptr_t rp = forest_.front();
    std::pop_heap(forest_.begin(), forest_.end(), cmp);
    forest_.pop_back();
    return rp;
}