/*
 * Decoder
 */

#include <iostream>
#include <fstream>
#include <string>

#include "huffman.hh"
#include "bitio.hh"

int main(int argc, char* argv[]){

    // Checking that there are more than 1 arguments
    if (argc < 2){
        std::cerr<<"At least 1 file argument is needed to compress file.\n";
        return 1;
    }

    for (int i=1; i !=argc; ++i){
        std::cout<<"Decompressing "<<argv[i]<<"\n";
        std::ifstream input (argv[i], std::ios::binary);
        
        // if file can't be opened, move on to the next argument
        if (!input.is_open()){
            std::cout << "Unable to open " << argv[i] << ".\n";
        }

        else{
            Huffman decoder;
            int symbol = -1;
            std::ofstream output;
            output.open(std::string(argv[i]) + ".plaintext");
            BitIO bitio(nullptr, &input);
            while (true) {
                // ASCII symbols will have positive values
                while (symbol < 0) {
                    symbol = decoder.decode(bitio.input_bit());
                }
                /* for debugging
                std::cout<< "Decoding " << symbol << ".\n";
                */
                if (symbol == Huffman::HEOF) {
                    break;
                } 
                else {
                    output.put(symbol);
                    symbol = -1;
                    }
            }
        }
    }
    return 0;
}