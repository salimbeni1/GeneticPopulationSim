#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>

#include "Population.hpp"

/**
 * @brief class to model a simulation.
 * @details The Simulation is modeled with many populations and
 * will run over few (or many) generations.
 */
class Simulation
{

private:

std::vector<Population*> Populations_;   /**< list of populations */

unsigned int NbPopulations_;   /**< number of population */

unsigned int NbGenerations_;   /**< number of generations for the simulation */

std::ofstream Output_;   /**< output stream to output each generation */

std::map<std::string, double> SpecificityRatio_;   /**< list of specificity ratios for 'selection' option */

int MigrationModel_;   /**< int that refers to the type of migration model (model 1 2 or 3) */
bool ShouldIMute_;    /**< bool to check if the 'mutation' option is on */
bool Selection_;
double MigrationRate_;   /**< ratio of alleles that migrate during each migration */

int sequenceSize_;

public:

/**
 * @brief set the selectivity ratio for one type of allele
 * @detail at each new generation, new selectivity ratios will be created for each allele and will influence the next chosen generation
 * @param allele : type of allele (defined by its sequence -> string)
 * @param specificity : new specificity ratio
 */
void setSelectivityRatio(std::string allele,double specificity );

/**
 * @ brief randomly creates a new selectivity ratio for new alleles (usefull to run with mutation)
 */
void setSelectivityRatioRandom();

/**
 * @brief default constructor
 */
Simulation();

/**
 * @brief constructor based on file
 * @param int , int , std::string , std::vector
 * @return none
 */
Simulation(int const& NbGenerations,int const& NbPopulations,std::string const& file, std::vector<unsigned int> const& markers, int const& migrationMode, bool mutant, bool selectionOption);


/**
 * @brief constructor based on file
 * @param int , int , std::string , std::vector
 * @return none
 */
Simulation(int const& NbGeneration, int const& NbPopulation, int const& nbrIndividu, std::vector<std::string> sequences, std::vector<double> frequencies, int const& migrationMode, bool mutant, bool selectionOption);

/**
 * @brief Destructor that deletes pointers at the end
 * @param none
 * @return none
 */
~Simulation();


/**
 * @brief Loads the initial conditions ( frequencies )
 * @param
 * @return void
 */
std::map<std::string, int> LoadFromFile(std::string const& file, std::vector<unsigned int> const& markers);


/**
 * @brief saves generation values in "Output.txt"
 * @param output : output stream
 * @param Alleles : list of allele quantities
 * @param nbAlleles : total number of alleles (needed to calculate frequences)
 */
void SaveToFile(std::ofstream& output,std::vector<int> Alleles, int const& nbAlleles ) const;


/**
 * @brief runs the simulation
 * @param none
 * @return void
 */
void run();


/**
 * @brief adds the values of a map to an other map
 * @param changingMap : map that will insert values
 * @param additionalMap : map that will add values
 */
void mapFusion(std::map<std::string,int> & changingMap, std::map<std::string, int> const& additionalMap);


/**
 * @brief displays the loading output on terminal
 */
void displayCountdown(double chan, double maxiv);


/**
 * @brief makes populations migrate according to the selected migration model
 */
void Migrate();

/**
 * @brief migration model 1 (star formation)
 * @param migrationRatioUser : ratio of the alleles that will migrate for each population
 */
void starMigrationModel(double migrationRatioUser);

/**
 * @brief migration model 2 (ring formation)
 * @param
 */
void ringMigrationModel(double migrationRatioUser);

/**
 * @brief migration model 3 (flower formation)
 * @param
 */
void flowerMigrationModel(double migrationRatioUser);


/**
 * @brief asks the user for a migration rate
 */
void askMigrationRate();

/**
 * @brief asks the user for mutation rates
 */
void askMutant(std::vector<double>& trioRate);


/**
 * @brief asks the user for specific ratios
 */
void setSpecificityRatio();

};
#endif
