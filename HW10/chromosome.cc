/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <vector>
#include <utility> // for std::swap
#include <cmath>

#include "chromosome.hh"
#include "cities.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(random_permutation(cities_ptr->size())),
    generator_(rand())
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
void
Chromosome::mutate()
{
  int size = cities_ptr_->size();
  // I thought the distribution would be exclusive at the end,
  // but I ran into multiple errors of it not being so,
  // so I substracted -1.
  std::uniform_int_distribution distribution (0, size-1);
  int pos1 = distribution(generator_);
  int pos2 = distribution(generator_);
  std::swap(order_[pos1], order_[pos2]);

  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  std::uniform_int_distribution distribution (0, (int)cities_ptr_->size()-1);
  int begin = distribution(generator_);
  int end = distribution(generator_);

  if (begin > end){ // ensure b is smaller
    std::swap(begin, end);
  }

  Chromosome* child1 = create_crossover_child(this, other, begin, end);
  Chromosome* child2 = create_crossover_child(other, this, begin, end);
  return std::pair(child1, child2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < p1->order_.size() && j < p2->order_.size(); ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < p2->order_.size());
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
double
Chromosome::get_fitness() const
{
  // I tried squareing the denominator to favor fitness
  // because my tsp didn't go below 18 thousand with challenge.tsv
  // but it didn't help.
  return 1/std::pow(cities_ptr_->total_path_distance(order_), 2);
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  std::vector<bool> vec (cities_ptr_->size(), 0);
  for (int i : order_){
    // at.() function prevents changes being made out-of-bounds
    vec.at(i) = 1;
  }
  if (std::find(vec.cbegin(), vec.cend(), 0) == vec.cend()){
    return true;
  }
  return false;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool
Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
  auto iterator = order_.begin();
  if (std::find(iterator + begin, iterator + end, value) == iterator + end){
    return false;
  }
  return true;
}
