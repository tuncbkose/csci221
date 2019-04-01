/*
 * HForest: a class to represent a collection of HTrees.
 */

/*
 * Forest is a vector that stores pairs of key to a tree and its pointer.
 */

#include "hforest.hh"
#include <algorithm>
#include <cassert>

// Constructor
HForest::HForest(){
    sz_ = 0;
}

// Destructor
HForest::~HForest() = default;

int HForest::size() const {
    return sz_;
}

HForest::pair_t HForest::make_pair(tree_ptr_t t){
    return {t->get_value(), t};
}

bool HForest::cmp(pair_t p1, pair_t p2){
    return p1.first < p2.first;
}

void HForest::add_tree(tree_ptr_t t){
    forest_.push_back(make_pair(t));
    ++sz_;
    std::push_heap(forest_.begin(), forest_.end()); // For some reason, when I added the third argument "cmp(forest_.front(), forest_.back())" here, it didn't compile
}

HForest::tree_ptr_t HForest::pop_tree() {

    assert(sz_>0);

    tree_ptr_t rp = forest_.front().second; // Extract pointer from pair
    std::pop_heap(forest_.begin(), forest_.end()); // same problem as push_heap function in add_tree
    --sz_;
    return rp;
}