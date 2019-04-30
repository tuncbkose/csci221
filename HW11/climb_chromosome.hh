/*
 * climb_chromosome.hh
 */

#pragma once

#include "chromosome.hh"

class ClimbChromosome : public Chromosome{
    protected:
        // Disable public copying of objects for polymorphism:
        ClimbChromosome(const ClimbChromosome&) = default;
        ClimbChromosome(ClimbChromosome&&) = default;
        ClimbChromosome& operator=(const ClimbChromosome&) = default;
        ClimbChromosome& operator=(ClimbChromosome&&) = default;

    public:
        // Creation method for new ClimbChromosome. Saves a copy of the cities and
        // generates a completely random permutation from a list of cities.
        ClimbChromosome(const Cities*);

        // Polymorphic creation method from an existing ClimbChromosome.
        // This method allocates memory for the newly created chromosome.
        // It is the caller's responsibility to free this memory.
        virtual ClimbChromosome* clone() const
        {
            return new ClimbChromosome(*this);
        }

        // Clean up as necessary
        virtual ~ClimbChromosome();

        // Perform a single mutation on this chromosome
        virtual void mutate();
};