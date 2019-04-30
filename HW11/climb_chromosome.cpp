/*
 * Implementation for ClimbChromosome class
 */

#include <cassert>
#include <algorithm>
#include <initializer_list>
		

#include "climb_chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
ClimbChromosome::ClimbChromosome(const Cities* cities_ptr)
    : Chromosome(cities_ptr)
{
    assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
ClimbChromosome::~ClimbChromosome()
{
    assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
// fitness_1, 2 and 3 represent the fitnesses of "this", cc2, and cc3.
// cc2 is a clone of "this", but with p1 and p2 indices swapped.
// cc3 is a clone of "this", but with p1 and p3 indices swapped.
// The method mutates "this" into the fittest of the three.
void
ClimbChromosome::mutate()
{
    double fitness_1 = this->get_fitness();
    static std::uniform_int_distribution<int> dist(0, order_.size() - 1);

    unsigned int p1 = dist(generator_);
    unsigned int p2 = p1 - 1;
    // Ensuring that p2 != -1
    if (p1 == 0){
        p2 = order_.size()-1;
    }

    ClimbChromosome* cc2 = this->clone();
    // This assertion also ensures that cc3 will be valid at creation.
    assert(cc2->is_valid());
    std::swap(cc2->order_[p1], cc2->order_[p2]);
    assert(cc2->is_valid());
    double fitness_2 = cc2->get_fitness();

    ClimbChromosome* cc3 = this->clone();
    unsigned int p3 = p1 + 1;
    // Ensuring that p3 is not out of bounds.
    if (p1 == order_.size()-1){
        p3 = 0;
    }
    std::swap(cc3->order_[p1], cc3->order_[p3]);
    assert(cc3->is_valid());
    double fitness_3 = cc3->get_fitness();

    if (fitness_3 > fitness_2 && fitness_3 > fitness_1){
        this->order_ = cc3->order_;
    }
    else if (fitness_2 > fitness_1){
        this->order_ = cc2->order_;
    }
    
    delete cc2;
    delete cc3;
}