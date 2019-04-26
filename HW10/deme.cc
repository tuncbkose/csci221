/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */

#include "chromosome.hh"
#include "deme.hh"
#include <random>
#include <algorithm>
#include <iostream>

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
  for (unsigned i = 0; i != pop_size; i++){
    Chromosome* chr = new Chromosome(cities_ptr);
    pop_.push_back(chr);
  }
  mut_rate_ = mut_rate;
}

// Clean up as necessary
Deme::~Deme()
{
  for (auto i: pop_){
    delete i;
  }
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
  std::vector<Chromosome*> new_pop;
  for (int i = 0; i != (pop_.size())/2; i++){

    std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution (0, mut_rate_);

    Chromosome* par1 = this->select_parent();
    if (distribution(gen) < mut_rate_){
      par1->mutate();
    }
    Chromosome* par2 = this->select_parent();
    if (distribution(gen) < mut_rate_){
      par2->mutate();
    }
    std::pair<Chromosome*, Chromosome*> children = par1->recombine(par2);
    
    new_pop.push_back(children.first);
    new_pop.push_back(children.second);

  }
  // delete old pop_
  for (auto i: pop_){
    delete i;
  }
  pop_ = new_pop;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
  double best_fit = 0;
  Chromosome* best;
  for (auto i: pop_){
    if (i->get_fitness()>best_fit){
      best_fit = i->get_fitness();
      best = i;
    }
  }
  return best;
}

static bool fit_cmp(const Chromosome* ptr1, const Chromosome* ptr2){
  return ptr1->get_fitness() < ptr2->get_fitness();
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  double fit_total = 0;
  // I have heard that other people had some luck with sorting this,
  // but it didn't have an affect in my case.
  std::sort(pop_.begin(), pop_.end(), fit_cmp);
  for (auto i: pop_){
    fit_total += i->get_fitness();
  }
  std::random_device rd;  
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> distribution (0, fit_total);
  double part_sum = distribution(gen);

  Chromosome* parent = nullptr;
  for (auto i:pop_){
    part_sum += i->get_fitness();
    parent = i;
    if (part_sum >= fit_total){
      break;
    }
  }

  return parent;
}