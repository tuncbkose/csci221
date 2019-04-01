# README for Homework 7

### HTree

HTree class creates an object that has a key, a value and 2 pointers(left and right) that can point to other HTree objects and are nullptr by default. 

It has public methods get_key, get_value, get_child as getters, and path_to, which returns a list of directions from root to the leftmost HTree with a given key, or crashes no HTrees with the given key are connected to the root.

path_to method works by heavily utilizing a private method, find_key, which returns a boolean value whether an HTree with a given key is connected to the root or not. path_to uses this function to check if it contains the key, and if it is not on itself, to check whether it is on its left or right connections recursively.


### HForest

HForest class creates an object that stores a collection of independent HTrees in an std::vector as a heap using make_heap function. The constructor allows only for the creation of an empty HForest object, to which HTrees can be added later using the add_tree method. On a later thought, I could have allowed the constructor to take in an array of HTree pointers and add all to the HForest, but individual adding still seems a safer option.

HForest class contains three public methods, size() returns how many HTrees are in the HForest, add_tree adds another HTree and pop_tree removes the HTree with the largest value from the HForest and returns a pointer to it.
