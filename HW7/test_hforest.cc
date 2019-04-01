// test_hforest.cc

#include "hforest.hh"
#include <cassert>

int main(){

    HTree::tree_ptr_t tree1 (new HTree(0, 100));
    HTree::tree_ptr_t tree2 (new HTree(1, 50));
    HTree::tree_ptr_t tree3 (new HTree(2, 25));

    HForest* forest1p = new HForest();
    HForest forest1 = *forest1p;
    assert(forest1.size() == 0);
    forest1.add_tree(tree1);
    assert(forest1.size() == 1);
    forest1.add_tree(tree2);
    assert(forest1.size() == 2);
    forest1.add_tree(tree3);
    assert(forest1.size() == 3);
    HTree::tree_ptr_t tp = forest1.pop_tree();
    assert(forest1.size() == 2);
    assert((*tp).get_value()==100);
    delete forest1p;
    return 0;
}