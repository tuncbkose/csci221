/*
 * HForest: a class to represent a collection of HTrees.
 */

#include "hforest.hh"
#include <algorithm>
#include <cassert>

static bool cmp(HForest::tree_ptr_t p1, HForest::tree_ptr_t p2){
    return p1->get_value() < p2->get_value();
}


// Constructor
HForest::HForest(){
    sz_ = 0;
}

// Destructor
HForest::~HForest() = default;

int HForest::size() const {
    return sz_;
}

void HForest::add_tree(tree_ptr_t t){
    forest_.push_back(t);
    ++sz_;
    std::push_heap(forest_.begin(), forest_.end(), cmp);
}

HForest::tree_ptr_t HForest::pop_tree() {

    assert(sz_>0);

    tree_ptr_t rp = forest_.front();
    std::pop_heap(forest_.begin(), forest_.end(), cmp);
    --sz_;
    return rp;
}
