/*
 * tournament_deme.hh
 */

#pragma once

#include "deme.hh"

class TournamentDeme : public Deme {
 public:
  // Generate a Deme of the specified size with all-random chromosomes.
  // Also receives a mutation rate in the range [0-1].
  TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate);

  // Clean up as necessary
  virtual ~TournamentDeme();

  // Implements Deme::compute_next_generation with tournament selection.
  virtual void compute_next_generation();

 protected:
  // Randomly select a chromosome in the population based on fitness
  // using tournament selection return a pointer to that chromosome.
  virtual Chromosome* select_parent();
};