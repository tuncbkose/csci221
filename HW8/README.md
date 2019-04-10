# README for Homework 8: Huffman Encoding
This homework was done by me(Tunc Kose) alone.

### Description
* **HTree** and **HForest** classes were taken from my submissions for Homework 6 and 7, with small modifications for bug fixes, and for pop_tree function in HForest to return the tree with the smallest value.
* **BitIO** class contains functions to read or write bits to streams.
* **Huffman** class contains functions create a Huffman tree, and encode/decodes according the tree and inputted bits.

### Compression Tests
|   File name   | Raw size (bytes) | Compressed size (bytes) | Decompression matches raw file? |
|:-------------:|:----------------:|:-----------------------:|:-------------------------------:|
|    Makefile   |        848       |           790           |               yes               |
| test_bitio.cc |       4070       |           2558          |               yes               |
|   huffman.cc  |       3303       |           2322          |               yes               |
|   huffman.hh  |       1294       |           1121          |               yes               |
|  MonaLisa.txt |       49343      |          15215          |               yes               |
