/*
 * Cities.cc
 */

#include <string> // for std::string
#include <iostream> // for >> and << operator methods
#include <cassert> // for assert
#include <cmath> // for hypot
#include <algorithm> // for std::find
#include <random>
#include "cities.hh"

// Constructor
Cities::Cities() = default;

//Destructor
Cities::~Cities() = default;

// Adds a given coordinate to city_list_
void Cities::add_city(const coord_t city){
    city_list_.push_back(city);
}

// Given a permutation, return a new Cities object where the order of the
// cities reflects the original order of this class after reordering with
// the given ordering. So for example, the ordering { 1, 0 } simply swaps
// the first two elements (coordinates) in the new Cities object.
Cities Cities::reorder(const permutation_t& ordering) const{
    Cities new_city;
    for (int i:ordering){
        new_city.add_city(city_list_[i]);
    }
    return new_city;
}

// Returns the distance between two given coordinates.
double Cities::distance(const coord_t city1, const coord_t city2) const{
    // first has x coordinates, second has y
    return std::hypot(city1.first - city2.first, city1.second - city2.second);
}

// For a given permutation of the cities in this object,
// compute how long (distance) it would take to traverse all the cities in the
// order of the permutation, and then returning to the first city.
// The distance between any two cities is computed as the Euclidean 
// distance on a plane between their coordinates.
double Cities::total_path_distance(const permutation_t& ordering) const{
    // Assert that the ordering takes into account every city
    assert(ordering.size() == city_list_.size() && ordering.size()>1);

    double total_distance = 0;
    unsigned int index = 0;
    do{ // do while loop because at least 1 iteration is needed.

        // get the next city and the one after that,
        // calculate the distance between them and add to total
        coord_t city1 = city_list_[ordering[index]];
        coord_t city2 = city_list_[ordering[index+1]];
        total_distance += distance(city1, city2);
        index++;
    }while (index != ordering.size()-1); // Stop at second last element

    // add the distance from last city to first
    coord_t city_0 = city_list_[ordering[0]];
    coord_t city_max = city_list_[ordering[ordering.size()-1]];
    total_distance += distance(city_0, city_max);
    return total_distance;
}

// Inputs the contents of a input stream into a Cities object,
// expecting an x value and a y value seperated by a space per line.
std::istream& operator>> (std::istream& file, Cities& cities){
    std::string line;
    while (getline(file, line)){
        // find the separation between x and y values
        auto space = line.find(" ");
        if (space == line.size()-1){
            std::cerr << "Invalid input at line: " << line << "\n";
            break;
        }
        // Make substrings of x and y, convert them into integers and
        // combine the two into a pair
        Cities::coord_t coord = std::pair(std::stoi(line.substr(0, space)), std::stoi(line.substr(space+1, std::string::npos)));
        cities.city_list_.push_back(coord);
    }
    return file;
}

// Outputs the coordinates contained in a Cities object to the given stream
// in the form of x-value + space + y-value.
std::ostream& operator<< (std::ostream& stream, Cities& cities){
    for (auto city :cities.city_list_){
        stream << city.first << " " << city.second << "\n";
    }
    return stream;
}

// Generates and returns a new permutation of all the numbers 
// from 0 to len-1 (with no skipped or repeated indices).
Cities::permutation_t Cities::random_permutation(unsigned len){
    // generate random seed
    permutation_t ordering;
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(0, len-1);
    while (ordering.size() < len){
        auto random = distribution(generator);
        // ensure the random number isn't already in the list
        // if it isn't, std::find will return an iterator to 1 after last.
        if (std::find(ordering.cbegin(), ordering.cend(), random) == ordering.cend()){
            ordering.push_back(random);
        }
    }
    return ordering;
}

// Returns the size of city_list_.
int Cities::len() const{
    return city_list_.size();
}