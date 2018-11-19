#include "multiBinomial.hpp"
#include <iostream>
#include <random>



std::vector<int> MultiBinomial::generate(std::vector<int> popInit)
{
								// p is the sum of all the number in the vector
								int p(0);
								for(auto w : popInit)
								{ p += w; }

								int q(p);

								// popFInal has the same size of popInit
								std::vector<int> popFinal(popInit);

								// binomial random generator
								static std::random_device rd;
								static std::mt19937 rng(rd());
								int i(popInit.size()-1);

								while(i > 0)
								{
																std::binomial_distribution<int> dbinom(p,popInit[i]/(q*1.0));
																popFinal[i] = dbinom(rng);

																popInit.pop_back();
																p -= popFinal[i];
																q -= popInit[i];
																--i;
								}
								popFinal[0] = p;

								return popFinal;
}

void MultiBinomial::generateWithSpecificity
								(std::map<std::string, double> specificityRates,
								std::vector<int>& alleleQuantity,
								std::vector<std::string> const& alleleTypes)
{
								// si on les alleles dans la map ne sont pas les meme que ceux de alleleTypes
								std::map<std::string,double>::iterator it;

								for(auto el : alleleTypes)
								{
																it = specificityRates.find(el);

																if(it == specificityRates.end())
																{ specificityRates[el] = 0; }
								}

								std::vector<int> popInit = alleleQuantity;
								// p is the sum of all the number in the vector
								int p(0);
								for(auto w : popInit)
								{ p += w; }
								int q(p);
								// popFInal has the same size of popInit
								std::vector<int> popFinal(popInit);


								// binomial random generator
								static std::random_device rd;
								static std::mt19937 rng(rd());
								int i(popInit.size()-1);

								double sommeOfFitnessFr(0);


								while(i > 0)
								{
													int w = 0;
													while(w < popInit.size())
													{
																	sommeOfFitnessFr += (popInit[w]*1.0*specificityRates[alleleTypes[w]]);
																	++w;
													}
													double fitnessFrequency = (popInit[i]*(1+specificityRates[alleleTypes[i]]))/((q*1.0)+sommeOfFitnessFr);

													std::binomial_distribution<int> dbinom(p,fitnessFrequency);
													popFinal[i] = dbinom(rng);

													popInit.pop_back();
													p -= popFinal[i];
													q -= popInit[i];
													--i;
								}

								popFinal[0] = p;

								alleleQuantity = popFinal;
}
