// test_htree.cc
#include "htree.hh"
#include <cassert>

int main()
{
    HTree::tree_ptr_t a (new HTree{1, 2});
    assert(a->get_key() == 1);
    assert(a->get_value() == 2);
    assert(a->get_child(HTree::Direction::LEFT) == nullptr);
    assert(a->get_child(HTree::Direction::RIGHT) == nullptr);

    HTree::tree_ptr_t b (new HTree(2, 4, a));    
    assert(b->get_key() == 2);
    assert(b->get_value() == 4);
    assert(b->get_child(HTree::Direction::LEFT) == a);
    assert(b->get_child(HTree::Direction::RIGHT) == nullptr);

    HTree::path_t answer1 ({HTree::Direction::LEFT});
    assert(b->path_to(1) == answer1);

    return 0;
}