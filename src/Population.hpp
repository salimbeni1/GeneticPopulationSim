#ifndef Population_hpp
#define Population_hpp

#include "multiBinomial.hpp"
#include <vector>
#include <string>
#include <map>
#include <iostream>

/**
 * @brief class to model a population that can be updated through generations
 */
class Population
{

private:

int nbrAllele_;   /**< (int) Total number of alleles */
std::vector<std::string> alleleSequences_;   /**< (stirng) list of sequences of each allele */
std::vector<int> alleleQuantity_;   /**< (int) list of quantities of each allel */
MultiBinomial random_;   /**< (Multibinomial) variable of class multibinomial which is called when a multinomial distribution is wanted */

//std::map<std::string, double> specificityRatio;

std::vector<double> mutationRates;   /**< (double) list of the mutation rates for each nucleotide position */


public:

/**
 * @brief Constructor of Population
 */
Population(std::map<std::string, int> GeneticInformation, std::vector<double> MutRate  );

/**
 * @brief Constructor
 * @param nbrAllele
 * @param sequences
 * @param MutRate : mutationRates
 */
Population(int const& nbrAllele, std::vector<std::string> const& sequences,
           std::vector<double> frequencies, std::vector<double> MutRate );

/**
 * @brief update the population
 * @detail generates the next generation
 */
void update();

/**
 * @brief update that takes specifities into account
 * @param specificityRatio : list of the specifities of each allele
 */
void update(std::map<std::string, double> specificityRatio);


/**
 * @brief returns the total number of alleles in the population
 * @return number of alleles (int)
 */
int getTotalAlleles() const;


int getnbrAllele() const;


/**
 * @brief returns the vector of allele sequences
 * @return allele sequences (std::vector<int>)
 */
std::vector<std::string> getAlleleSequence() const;

/**
 * @brief returns the vector of allele quantities
 * @return allele quantities (std::vector<int>)
 */
std::vector<int> getAlleleQuantity() const;



/**
 * @brief gives a list of alleles leaving a population and erases them from the population
 * @param nbrPeopleLeaving : number of people that should leave (int)
 * @return list of alleles leaving (map<string, int>)
 */
std::map<std::string, int> leavingPop(int nbrPeopleLeaving);

/**
 * @brief add the new migrant alleles to the population
 * @param migrants : list of migrants that should be added
 */
void insertMigrants(std::map<std::string, int> migrants);


/**
 * @brief randomly mutes alleles of the population
 */
void mute();

/**
 * @brief randomly swaps a nucleotide
 * @param sequence : sequence that will mute
 * @param nucleotide : position of the nucleotide that will mute
 * @param randomNumber : random number (1-3) that will define the new nucleotide
 * @return mutated sequence (string)
 */
std::string Mutate(std::string sequence, int nucleotide, int randomNumber) const;


/**
 * @brief insertes a map<string, int> in two different vectors
 * @detail the map will add its value, previous values of the vectors will remain
 * @param mappa : map that will be transfered
 * @param vectorS : vector<string> in which we will insert the keys (string)
 * @param vectorI : vector<int> in which we will insert the values (int)
 */
void insertMapInTwoVectors(std::map<std::string, int> mappa,
                           std::vector<std::string>& vectorS, std::vector<int>& vectorI) const;

};
#endif /* Population_hpp */
