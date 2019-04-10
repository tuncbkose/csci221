/*
 * Encoder
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
        std::cout<<"Compressing "<<argv[i]<<"\n";
        std::ifstream input (argv[i]);
        
        // if file can't be opened, move on to the next argument
        if (!input.is_open()){
            std::cout << "Unable to open " << argv[i] << ".\n";
        }

        else{
            Huffman encoder;
            char c;
            std::ofstream output;
            output.open(std::string(argv[i]) + ".comp", std::ios::binary);
            BitIO bitio(&output, nullptr);
            while(input.get(c)){
                /* for debugging
                std::cout << "Encoding " << c << ".\n";
                */
                Huffman::bits_t bits = encoder.encode(c);
                for (auto bit : bits){
                    bitio.output_bit(bit);
                }
            }
            // Encode EOF after all the characters.
            Huffman::bits_t bits = encoder.encode(Huffman::HEOF);
            /* for debugging
            std::cout << "Encoding EOF.\n";
            */
            for (auto bit : bits){
                bitio.output_bit(bit);
            }
        }
    }
    return 0;
}