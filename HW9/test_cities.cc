#include "cities.hh"
#include <iostream>
#include <fstream>

int main(){
    auto fin = std::ifstream("five.tsv");
    Cities cities;
    fin >> cities;
    std::cout<<cities;
    std::cout<<cities.total_path_distance({0, 1, 2, 3, 4}) << "\n";
    Cities new_cities = cities.reorder({1, 2, 0, 3, 4});
    std::cout<<new_cities << "\n";
    auto ordering = Cities::random_permutation(20);
    for (int i: ordering){
        std::cout<<i<<" ";
    }
    std::cout<<"\n";
    return 0;
}