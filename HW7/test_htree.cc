// test_htree.cc
#include "htree.hh"
#include <cassert>
#include <iostream>

int main()
{
    HTree::tree_ptr_t a (new HTree{1, 2});
    HTree x = *a;
    assert(x.get_key() == 1);
    assert(x.get_value() == 2);
    assert(x.get_child(HTree::Direction::LEFT) == nullptr);
    assert(x.get_child(HTree::Direction::RIGHT) == nullptr);

    HTree::tree_ptr_t b (new HTree(2, 4, a));
    HTree y = *b;
    
    assert(y.get_key() == 2);
    assert(y.get_value() == 4);
    assert(y.get_child(HTree::Direction::LEFT) == a);
    assert(y.get_child(HTree::Direction::RIGHT) == nullptr);

    HTree::path_t answer1 ({HTree::Direction::LEFT});
    assert(y.path_to(1) == answer1);

    return 0;
}