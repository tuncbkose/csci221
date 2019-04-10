# README for Homework 8: Huffman Encoding
This homework was done by me (Tunc Kose) alone.

### Description
___
* **HTree** and **HForest** classes were taken from my submissions for Homework 6 and 7, with small modifications for bug fixes, and for pop_tree function in HForest to return the tree with the smallest value.
* **BitIO** class contains functions to read or write bits to streams.
    * BitIO constructs an object with a pointer to either an input or an output stream, with the other being nullptr.
    * In addition to the pointers, it contains data members _bit_index_, which stores the next index of a byte to be writen to/read from, and <i>buffer_</i>, which contains the byte being written/read.
    * Of the two member functions, <i>output_bit</i> takes in a bit as an argument, writes the bit to the <i>buffer_</i> and increments the <i>bit_index</i>. If the <i>buffer_</i> is filled, _output_bit_ also writes the <i>buffer_</i> to the output stream. If the BitIO object were to be destructed before the next byte is completed, the destructor ensures that the byte is written.
    * The other member function, _input_bit_ first checks if there are bits left to be read. If not, the _bit_index_ is reset, and a byte is read from the input stream and stored in <i>buffer_</i>. Then, in all its calls, the function increments the _bit_index_ and returns the next bit to be read from <i>buffer_</i> as a boolean.
* **Huffman** class contains functions create a Huffman tree, and encode/decodes according the tree and inputted bits.
    * Huffman constructs an object with a frequency table, a vector of 257 0s, for 256 ASCII characters + end of file.
    * Huffman also includes a helper function _create_huffman_tree_, which returns a Huffman tree constructed according to the current frequency table of the object.
    * The _encode_ function takes in an ASCII character as an integer, constructs a Huffman tree, increments the frequency table and returns the path to the character from the root as a sequence of bits, 0 for left and 1 for right.
    * The _decode_ function, at the start of decoding a character, constructs a huffman tree and moves from the root according to the inputted bit. If the movement is towards an intermediate node(if the node has a negative key), a pointer to the node is stored for the next call of the function. If the key is positive, the function updates the frequency table, empties the saved intermediate node and returns the character(as an int).
* **Encoder** and **Decoder** takes in at least 1 additional argument from the command line. For each argument, they open the file and move on to the next if they can't.
    * Encoder reads each character from the file, determines the encoding of the character through _Huffman::encode_ and writes these bits using _BitIO::output_bit_. At the end of all characters, it also encodes the end-of-file representation manually to a new file, named "input file".comp.
    * Decoder reads the next bit with _BitIO::input_bit_ and calls _Huffman::decode_ repeatedly until it reaches an ASCII character. If the character is end-of-file, it stops, else it writes the character to a new file, named "compressed file".plaintext.

### Compression Tests
___
|   File name   | Raw size (bytes) | Compressed size (bytes) | Decompression matches raw file? |
|:-------------:|:----------------:|:-----------------------:|:-------------------------------:|
|    Makefile   |        848       |           790           |               yes               |
| test_bitio.cc |       4070       |           2558          |               yes               |
|   huffman.cc  |       3303       |           2322          |               yes               |
|   huffman.hh  |       1294       |           1121          |               yes               |
|  MonaLisa.txt |       49343      |          15215          |               yes               |
