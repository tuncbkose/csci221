/*
 * Implementation for TournamentDeme class
 */

#include "tournament_deme.hh"

#include <cmath>
#include <random>
#include <algorithm>
#include <cassert>

TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
    : Deme(cities_ptr, pop_size, mut_rate)
{}

TournamentDeme::~TournamentDeme(){
}

Chromosome*
TournamentDeme::select_parent(){

    // Determine the magnitune of the tournament by finding
    // the biggest power of 2 under population size.
    int power = 0;
    int size = pop_.size();
    while (size % 2 == 0){
        power++;
        size /= 2;
    }

    // Random selection of the parents, by shuffling the population
    // and selecting the first p many, where p is the biggest power of 2 under pop size.
    static std::random_device rd;
    static std::mt19937 g(rd());
    auto pop_copy = pop_;
    std::shuffle(pop_copy.begin(), pop_copy.end(), g);
    std::vector<Chromosome*> tournament(pop_copy.begin(), pop_copy.begin() + std::pow(2, power));

    // The while-loop below implements a tournament selection.
    // For each for-loop, i and i+1 represents the next 2 chromosome*'s.
    // first_is_better represents if i is more fit than i+1.
    // The erase method erases one of the pair based on first_is_better.
    // At the end of the for-loop, one of the 2 chromosome* is deleted,
    // hence iteration moves onto the next pair.
    // The while-loop ends when only 1 chromosome* is remaining.
    while(tournament.size() > 1){
        int iterations = tournament.size()/2;
        for (int i = 0; i != iterations; i++){
            bool first_is_better = tournament[i]->get_fitness() > tournament[i+1]->get_fitness();
            tournament.erase(tournament.begin() + i + first_is_better);
        }
    }
    
    // The remaining chromosome is returned.
    return tournament[0];
}

// The method below is identical to the Deme version
// I put it here so that when it is called somewhere else, it will
// definitely use the TournamentDeme::select_parent method.
void TournamentDeme::compute_next_generation()
{
  auto newpop = pop_;
  assert(pop_.size() % 2 == 0 && "Even population size required!");

  for (unsigned i = 0; i < pop_.size(); ) {
    auto p1 = select_parent();
    auto p2 = select_parent();

    static std::uniform_real_distribution<> dist(0.0, 1.0);
    
    if (dist(generator_) <= mut_rate_) {
      dynamic_cast<ClimbChromosome*>(p1)->mutate();
    }
    if (dist(generator_) <= mut_rate_) {
      dynamic_cast<ClimbChromosome*>(p2)->mutate();
    }


    auto children = p1->recombine(p2);
    newpop[i++] = children.first;
    newpop[i++] = children.second;
  }

  for (auto cp : pop_) {
    delete cp;
  }
  std::swap(pop_, newpop);
}