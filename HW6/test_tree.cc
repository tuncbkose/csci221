// test_tree.cc
#include "tree.hh"
#include <iostream>
#include <cassert>

int main()
{
    tree_ptr_t inner_tree = create_tree(0, 1);
    assert(inner_tree->left_ == nullptr);
    assert(inner_tree->right_ == nullptr);

    std::cout << "Path to 0 is " << path_to(inner_tree, 0) << "\n";

    tree_ptr_t outer_tree = create_tree(1, 1, inner_tree);

    std::cout << "Path to 1 is " << path_to(outer_tree, 1) << " and path to 0 is " << path_to(outer_tree, 0) << "\n";

    //std::cout << "Invalid path " << path_to(outer_tree, 2) << "\n"; // results in "Segmentation fault (core dumped)" as expected

    std::cout << "The node at '' has the value of " << node_at(outer_tree, "")->key_ << "\n";
    std::cout << "The node at 'L' has the value of " << node_at(outer_tree, "L")->key_ << "\n";
    //std::cout << "The node at 'R' has the value of " << node_at(outer_tree, "R")->key_ << "\n"; // results in "Segmentation fault (core dumped)" as expected

    tree_ptr_t outermost_tree = create_tree(2, 1, outer_tree);
    std::cout << "Path to 0 is " << path_to(outermost_tree, 0) << "\n";
    std::cout << "The node at 'RL' has the value of " << node_at(outermost_tree, "RL") << "\n";

    destroy_tree(outermost_tree);

    std::cout << "Everything seems fine\n";
}