#ifndef MULTIBINOMIAL_H
#define MULTIBINOMIAL_H

#include <vector>
#include <map>
#include <string>

/**
 * @brief class to generate a vector according to the multibinomial distribution.
 * @details we take a vector of int and give in return another one changed by
 *       the multibinomial distribution.
 */

class MultiBinomial {

public:



/**
 * @brief transforms a vector<int> through a mutibinomial procedure
 * @details this method takes a int vector and gives its version after a
       multibinomial distribution.
 * @param popInit : vector<int> that will be transformed.
 * @return result of the multibinomial distribution as a vector<int>.
 */
std::vector<int> generate(std::vector<int>);

/**
 * @brief generates the next generation and takes into account specificities
 * @param specificityRates : list of specificities of each allele
 * @param alleleQuantity : list of quantities of each allele
 * @param alleleTypes : list of sequences of each allele
 */
void generateWithSpecificity
								(std::map<std::string, double> specificityRates,
								std::vector<int> & alleleQuantity,
								std::vector<std::string> const& alleleTypes);

};

#endif
