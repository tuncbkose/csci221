/*
 * HForest: a class to represent a collection of HTrees.
 */

#pragma once

#include "htree.hh"
#include <vector>
#include <utility>

class HForest {
    public:
        using tree_ptr_t = HTree::tree_ptr_t;
        using forest_t = std::vector<tree_ptr_t>;
        using forest_ptr_t = std::shared_ptr<HForest>;

        // Constructor
        HForest();

        // Destructor
        ~HForest();

        // Returns how many trees are in the forest.
        int size() const;

        // Takes a pointer to an HTree and adds it to the forest.
        void add_tree(tree_ptr_t t);

        // Returns a pointer to the HTree with the highest value and removes it from the forest.
        tree_ptr_t pop_tree();

    private:
        int sz_;
        forest_t forest_;
};