#include "Population.hpp"

#include <random>
#include <fstream>
#include <assert.h>


Population::Population(std::map<std::string, int> GeneticInformation,
                       std::vector<double> MutRate )
        :  nbrAllele_ (0), mutationRates ( MutRate )
{
        for ( auto& info : GeneticInformation )
        {
                alleleSequences_.push_back( info.first );
                alleleQuantity_.push_back( info.second );

                nbrAllele_ += info.second;
        }
}



Population::Population(int const& nbrAllele,
                       std::vector<std::string> const& sequences, std::vector<double> frequencies,
                       std::vector<double> MutRate )
        : nbrAllele_(nbrAllele), alleleSequences_(sequences), mutationRates ( MutRate )
{
        for ( size_t i(0); i < frequencies.size(); ++i )
        { alleleQuantity_.push_back(nbrAllele_ * frequencies[i] ); }
}


////////////////////////////////////////////////////
///           UPDATE THE POPULATION             ///
//////////////////////////////////////////////////


void Population::update()
{
        alleleQuantity_ = random_.generate(alleleQuantity_);
}



void Population::update(std::map<std::string, double> specificityRatio)
{
        random_.generateWithSpecificity
                (specificityRatio,alleleQuantity_,alleleSequences_);
}


/////////////////////////////////////////
///             GETTERS              ///
///////////////////////////////////////



int Population::getnbrAllele() const
{
        return nbrAllele_;
}

int Population::getTotalAlleles() const
{
        int counter(0);

        for (auto& quantity : alleleQuantity_)
        {
                counter += quantity;
        }

        return counter;
}

std::vector<int> Population::getAlleleQuantity() const
{
        return alleleQuantity_;
}

std::vector<std::string> Population::getAlleleSequence() const
{
        return alleleSequences_;
}


////////////////////////////////////////////////////////////////////////
//                           MIGRATION                                //
////////////////////////////////////////////////////////////////////////


std::map<std::string, int> Population::leavingPop(int nbrPeopleLeaving)
{
        std::map<std::string, int> popLeaving;

        static std::random_device rd;
        static std::mt19937 generator(rd());

        for(int i(0); i<nbrPeopleLeaving; ++i)
        {
                std::uniform_int_distribution<int> distribution(1,getTotalAlleles());

                int n(distribution(generator));
                int pf(-1);
                int cnt = 0;
                bool state(true);
                for(size_t j(0); j< alleleSequences_.size(); ++j)
                {
                        cnt += alleleQuantity_[j];
                        if((n <= cnt) and (state == true))
                        {
                                pf = j;
                                state = false;
                        }
                }

                assert (alleleQuantity_.size() == alleleSequences_.size() );
                ++popLeaving[alleleSequences_[pf]];
                --alleleQuantity_[pf];
        }
        return popLeaving;
}



void Population::insertMapInTwoVectors(std::map<std::string, int> mappa,
                                       std::vector<std::string>& vectorS, std::vector<int>& vectorI) const
{
        for(auto& mapPair : mappa)
        {
                unsigned int cnt(0);
                int a(-1);
                for(auto& strin : vectorS)
                {
                        if(strin == mapPair.first)
                        { a = cnt; }

                        ++cnt;
                }

                if( a < 0 ) // si on ajoute une nouvelle allele
                {
                        vectorS.push_back(mapPair.first);
                        vectorI.push_back(mapPair.second);
                }
                else // si l allele existe deja
                { vectorI[a] += mapPair.second; }
        }
}



void Population::insertMigrants(std::map<std::string, int> migrants)
{
        int a(0);
        for(auto ma : migrants)
        { a += ma.second; }

        insertMapInTwoVectors(migrants,alleleSequences_, alleleQuantity_);
}




////////////////////////////////////////////////////////////////////////
//                           MUTATION                                 //
////////////////////////////////////////////////////////////////////////


void Population::mute()
{
        /* création d'un device random, il y aura trois distributions différentes.  */
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_int_distribution<int> duni(1,3);


        /* la première boucle permet de passer de nucléotide en nucléotide (3 nucléotides)*/
        for(int j(0); j<3; ++j)
        {
                std::map<std::string, int> AllelesCopy;
                for (unsigned i(0); i<alleleQuantity_.size(); ++i)
                { AllelesCopy[alleleSequences_[i]] = alleleQuantity_[i]; }

                /* map de copie -> besoin de clear quand on recommence la boucle */
                std::map<std::string, int> NewAlleles;
                std::map<char, int> nucleoMarker;

                for (auto sequence : AllelesCopy)
                { ++nucleoMarker[sequence.first[j]]; }

                /* Cette boucle la passe de nucléotide en nucléotide */
                for (auto nucleotide : nucleoMarker)
                {
                        /* Deuxième distribution qui définie le nombre de nucléotide spécifique
                           (nucleotide.first) qui vont muter*/
                        std::binomial_distribution<int> dbinom(nucleotide.second, mutationRates[j]);

                        /* Troisième distribution qui définie quel nucléotide dans notre liste va
                           muter */
                        std::uniform_int_distribution<int> duni2(0, nucleotide.second);
                        int random1(dbinom(rng));

                        /* boucle pour faire les n mutations */
                        for(int i(0); i<random1; ++i)
                        {
                                int m(0); //Compteur de quantité

                                int random2(duni2(rng)); //Numero du nucléotide qui va muté

                                for(auto sequence : AllelesCopy)
                                {
                                        if(sequence.first[j] == nucleotide.first)
                                        { m += sequence.second; }

                                        /* Quand m>random2 -> sait quelle séquence doit muté */
                                        if (m > random2)
                                        {
                                                --NewAlleles[sequence.first];
                                                ++NewAlleles[Mutate(sequence.first,j, duni(rng))];
                                                break;
                                        }
                                }
                        }
                }
                insertMapInTwoVectors(NewAlleles,alleleSequences_, alleleQuantity_);
        }
}



std::string Population::Mutate(std::string sequence, int nucleotide, int randomNumber) const
{
        int mutation[] = {'A', 'C', 'G', 'T'};

        switch(sequence[nucleotide])
        {
        case 'A': sequence[nucleotide] = mutation[(0+randomNumber)%4];
                break;
        case 'C': sequence[nucleotide] = mutation[(1+randomNumber)%4];
                break;
        case 'G': sequence[nucleotide] = mutation[(2+randomNumber)%4];
                break;
        case 'T': sequence[nucleotide] = mutation[(3+randomNumber)%4];
                break;
        }
        return sequence;
}
