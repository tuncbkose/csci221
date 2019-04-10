/*
 * Huffman: a class to encode and decode symbols based on adaptive Huffman coding
 * https://en.wikipedia.org/wiki/Huffman_coding
 */
 
#include "huffman.hh"
#include <cassert>

// Constructor
Huffman::Huffman(){
    // 256 ASCII characters + EOF
    freqtable_ = std::vector(257, 0);
}

// Destructor
Huffman::~Huffman() = default;

// Increments the frequency table member of the Huffman object
void Huffman::update_frequency_table(char c){
    ++freqtable_[c];
}

// Helper function that returns a huffman tree constructed based on
// the current frequency table.
static HTree::tree_ptr_t create_huffman_tree(std::vector<int> freqtable){
    using forest_ptr_t = HForest::forest_ptr_t;
    using tree_ptr_t = HTree::tree_ptr_t;

    assert(freqtable.size() == 257);

    // HForest object to contain all the trees for each character
    forest_ptr_t fp (new HForest());
    
    // Creates a tree for each character where key is character in int
    // and value is their frequency so far
    for (int a=0; a!=257; ++a){
        if (a != 256){ // So that EOF won't cause out of bounds in freqtable
            tree_ptr_t tp(new HTree(a, freqtable[a])); // Narrowing conversion here but should be ok
            fp->add_tree(tp);
        }
        else {
            tree_ptr_t tp(new HTree{a, 0});
            fp->add_tree(tp);
        }
    }

    // Combination of all trees into a single tree
    while (fp->size() > 1){
        // Pops two lowest-value trees and merges them with a negative
        // key and the sum of the child values
        tree_ptr_t tree1 = fp->pop_tree();
        tree_ptr_t tree2 = fp->pop_tree();

        tree_ptr_t node_p(new HTree{fp->size() - 255, tree1->get_value() + tree2->get_value(), tree1, tree2});

       fp->add_tree(node_p);
    }
    return fp->pop_tree();
}

// Returns the bits to encode a symbol, where 0 = LEFT and 1 = RIGHT
Huffman::bits_t Huffman::encode(int symbol){
    // Create the huffman tree from frequency table
    HTree::tree_ptr_t huff_tree = create_huffman_tree(freqtable_);
    // Find the path to the character being encoded
    HTree::path_t path = huff_tree->path_to(symbol);
    bits_t bits;
    // Convert directions to bits
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
    // decode_current_node is empty at start and right after a
    // character is encoded. Otherwise, it contains the intermediate
    // node that was reached in the previous decode call
    if (!decode_current_node){
        HTree::tree_ptr_t huff_tree = create_huffman_tree(freqtable_);
        decode_current_node = huff_tree;
    }

    // If 1, move right. If 0, move left.
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