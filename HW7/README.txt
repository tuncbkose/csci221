#README for Homework 7

###HTree

HTree class creates an object that has a key, a value and 2 pointers(left and right) that can point to other HTree objects and are nullptr by default. 

It has public methods get_key, get_value, get_child as getters, and path_to, which returns a list of directions from root to the leftmost HTree with a given key, or crashes no HTrees with the given key are connected to the root.

path_to method works by heavily utilizing a private method, find_key, which returns a boolean value whether an HTree with a given key is connected to the root or not. path_to uses this function to check if it contains the key, and if it is not on itself, to check whether it is on its left or right connections recursively.

In testing HTree, I realized that I had to create HTree with a shared_ptr so that I could use it in the construction of another HTree, but I would need to dereference that pointer every time I wanted to call methods to the object.
My solution was to create a pointer and immediately dereference it on another variable, but I am uncertain if this is good coding practice or not.


###HForest

HForest class creates an object that stores a collection of independent HTrees in an std::vector as a heap using make_heap function. The constructor allows only for the creation of an empty HForest object, to which HTrees can be added later using the add_tree method. On a later thought, I could have allowed the constructor to take in an array of HTree pointers and add all to the HForest, but individual adding still seems a safer option.

HForest class contains three public methods, size() returns how many HTrees are in the HForest, add_tree adds another HTree and pop_tree removes the HTree with the largest value from the HForest and returns a pointer to it.

The vector inside HForest contains HTrees as pairs of values and pointers, using std::pair. This allows the use of arithmetic operators for comparison while keeping the pointers within reach.

In using heap functions std::push_heap and std::pop_heap, I encountered a problem where trying to give a comparison of values as a third argument using HForest private method cmp gives a compilation error:
"/usr/include/c++/8/bits/predefined_ops.h:177:11: error: expression cannot be used as a function
  { return bool(_M_comp(*__it, __val)); }"

So far, I was unable to figure out why, and how to solve it, so the use of these heap functions in add_tree and pop_tree methods currently don't take a third argument.