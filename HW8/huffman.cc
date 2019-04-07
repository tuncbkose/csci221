/*
 * Huffman: a class to encode and decode symbols based on adaptive Huffman coding
 * https://en.wikipedia.org/wiki/Huffman_coding
 */
 
#include "huffman.hh"
#include <cassert>

Huffman::Huffman(){
    freqtable_ = std::vector(256, 0);
}

Huffman::~Huffman() = default; // Make sure okay later/

void Huffman::update_frequency_table(char c){
    ++freqtable_[c];
}

static HTree::tree_ptr_t create_huffman_tree(std::vector<int> freqtable){
    using forest_ptr_t = HForest::forest_ptr_t;
    using tree_ptr_t = HTree::tree_ptr_t;

    assert(freqtable.size() == 256);

    forest_ptr_t fp (new HForest());
    
    for (int a=0; a!=257; ++a){
        if (a != 256){ // So that EOF won't cause out of bounds in freqtable
            tree_ptr_t tp(new HTree(a, freqtable[a])); // Narrowing conversion here but should be ok
            fp->add_tree(tp);
        }
        else {
            tree_ptr_t tp(new HTree{a, 1});
            fp->add_tree(tp);
        }
    }

    while (fp->size() > 1){
        tree_ptr_t tree1 = fp->pop_tree();
        tree_ptr_t tree2 = fp->pop_tree();

        tree_ptr_t node_p(new HTree{fp->size() - 255, tree1->get_value() + tree2->get_value(), tree1, tree2});
        /* QUESTIONS FOR THE ABOVE:
           1- Does the key naming work? It is 255 because there are
              256 trees in total but 2 are popped out above and there
              is no -0 key.
           2- Does tree1 and tree2 being left or right matter?
              I think it does, not sure how though.
           3- This being a smart pointer, could it be deleted when I don't want it to?
        */

       fp->add_tree(node_p);
    }

    return fp->pop_tree();
}

Huffman::bits_t Huffman::encode(int symbol){
    
    HTree::tree_ptr_t huff_tree = create_huffman_tree(freqtable_);
    HTree::path_t path = huff_tree->path_to(symbol);
    bits_t bits;
    for (auto it = path.begin(); it != path.end(); ++it){
        if (*it == HTree::Direction::LEFT){
            bits.push_back(0);
        }
        else{
            bits.push_back(1);
        }
    }
    this->update_frequency_table(symbol);
    return bits;
}

int Huffman::decode(bool bit){
    
    if (!decode_current_node){
        HTree::tree_ptr_t huff_tree = create_huffman_tree(freqtable_);
        decode_current_node = huff_tree;
    }

    if (bit){
        decode_current_node = decode_current_node->get_child(HTree::Direction::RIGHT);
    }
    else{
        decode_current_node = decode_current_node->get_child(HTree::Direction::LEFT);
    }

    // Will be negative if intermediate node
    int key = decode_current_node->get_key();
    if (key > 0){
        this->update_frequency_table(key);
        decode_current_node = nullptr;
    }
    return key;
}