/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>


// Representation of an ordering of cities
class Cities {
 public:
  // Constructor
  Cities();

  // Destructor
  ~Cities();

  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  // Generates and returns a new permutation of all the numbers 
  // from 0 to len-1 (with no skipped or repeated indices).
  static permutation_t random_permutation(unsigned len);

  // Returns the size of city_list_.
  int len() const;

 private:
  std::vector<coord_t> city_list_;
  double distance(const coord_t city1, const coord_t city2) const;
  void add_city(const coord_t);

  friend std::ostream& operator<< (std::ostream&, Cities&);

  // Inputs the contents of a input stream into a Cities object,
  // expecting an x value and a y value seperated by a space per line.
  friend std::istream& operator>> (std::istream&, Cities&);
};