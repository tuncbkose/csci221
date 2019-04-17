/*
 * TSP.cc
 */

#include <fstream>
#include <iostream>
#include <string>
#include "cities.hh"

int main(int argc, char* argv[]){

    // Checking that there are 2 arguments
    if (argc != 2){
        std::cerr<<"Please give 1 input file.\n";
        return 1;
    }
    // Checking the file extension
    else if (std::string(argv[1]).substr(std::string(argv[1]).find_last_of(".")) != ".tsv"){
        std::cerr<<"Please input .tsv files.\n";
        return 2;
    }
    else{
        std::ifstream file (argv[1]);
        if (!file.is_open()){
            std::cerr << "Unable to open " << std::string(argv[1]) << ".\n";
            return 3;
        }
        else{
            Cities city;
            unsigned int shortest;
            // Input contents of file into a Cities object
            file>>city;
            for (int i = 0; i != 1000000; ++i){
                // Generate new permutation and calculate distance
                auto new_permutation = Cities::random_permutation(city.len());
                double distance = city.total_path_distance(new_permutation);
                // If it's the first iteration or if distance is the shortest yet
                if (i == 0 || distance < shortest){
                    // Update shortest distance and city object
                    shortest = distance;
                    city = city.reorder(new_permutation);
                    std::cout<<i<<"     "<<shortest<<"\n";
                }
            }

            // Output the shortest ordering into shortest.tsv
            std::ofstream output;
            output.open("shortest.tsv");
            output << city;
            output.close();
            file.close();
        }
    }
}