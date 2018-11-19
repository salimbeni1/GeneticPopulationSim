#include <iostream>
#include <tclap/CmdLine.h>
#include <utility>
#include <cmath>
#include "src/Simulation.hpp"
#include <sstream>
#include <ConstGlobal.h>


//using namespace TCLAP;

/*--------variables for the simulation---------*/
unsigned int _nbGenerations;
unsigned int _nbPopulations;
int _migrationOption;
bool _mutationOption;
bool _selectionOption;

std::string _file;
unsigned int _nbAlleles;


bool _fastafileOption;
bool _defaultOption;
bool _PersonalisedOption;


/*----------functions for TCLAP ---------------------*/

//intialises all variables
void parseOptions(int argc, char** argv);

/*looks for all the possible gene sequences for a certain sequence length
   allows to create a constraint in TCLAP */
/*void possibleSequences
   (std::vector<std::string>& sequences, const int& sequenceLeungth);*/

//serie of tests to avoid impossible values
bool test(std::vector<std::string> sequences);
bool test2(std::vector<std::string> sequences, size_t size);
bool test4(std::vector<double> frequences);
bool test5(std::vector<std::string> sequences);


std::vector<unsigned int> ask_markers();
std::vector<double> ask_mutationRates();
void ask_sequencesWithFrequence
        (std::vector<std::string>& sequences, std::vector<double>& frequences);








/*----------------------------main-----------------------------*/
int main(int argc, char **argv )
{

        try
        {
                parseOptions(argc, argv);

                if (_defaultOption)
                {
                        Simulation simulation;
                        simulation.run();
                }

                if (_PersonalisedOption)
                {
                        std::vector<std::string> sequences;
                        std::vector<double> frequences;
                        ask_sequencesWithFrequence(sequences, frequences);

                        Simulation simulation(_nbGenerations,_nbPopulations, _nbAlleles, sequences, frequences, _migrationOption, _mutationOption, _selectionOption);
                        simulation.run();
                }

                if (_fastafileOption)
                {
                        Simulation simulation(_nbGenerations, _nbPopulations, _file, ask_markers(), _migrationOption, _mutationOption, _selectionOption);
                        simulation.run();
                }
        }

        catch (TCLAP::ArgException& e)
        { std::cout << "ERROR: " << e.error() << " " << e.argId() << std::endl; }
        catch (char const* e)
        { std::cout << "ERROR: " << e << std::endl; }

        return 0;
}
/*-------------------------------------------------------------*/









/*----------------------parse option------------------------------*/
void parseOptions(int argc, char** argv)
{
        TCLAP::CmdLine cmd( _DESCRIPTION_PROJECT );

        TCLAP::SwitchArg defaultOption("d", "default",_DEFAULT_TEXT_, false);

        TCLAP::ValueArg <unsigned int>
        nbAlleles("a", "al", _ALLELE_TEXT_, true, 0, "unsigned int");

        TCLAP::ValueArg<std::string>
        file("f","fi", _FILE_TEXT_, true, "error", "std::string");

/*je veux soi un nom de fichier (string) soi des valeurs entrée (individu)
   soi l'option par default*/
        std::vector<TCLAP::Arg*> xorlist;
        xorlist.push_back(&defaultOption);
        xorlist.push_back(&file);
        xorlist.push_back(&nbAlleles);



        cmd.xorAdd(xorlist);

        std::vector<int> allowed = {1,2,3};
        TCLAP::ValuesConstraint<int> allowedMgr(allowed);

        TCLAP::ValueArg<int>
        migration("", "mi", _MIGRATION_TEXT, false, 0, &allowedMgr);
        cmd.add(migration);

        TCLAP::SwitchArg mutationOption("", "mu", _MUT_OPTION_TEXT, false);
        cmd.add(mutationOption);

        TCLAP::SwitchArg selectionOption("s", "sel", _SEL_OPTION_TEXT, false);
        cmd.add(selectionOption);

        TCLAP::ValueArg<unsigned int>
        nbGene("g", "gen",  _NBR_GENERATION_, false, 0, "unsigned int");
        cmd.add(nbGene);

        TCLAP::ValueArg<unsigned int>
        nbPop("p", "pop", _NBR_POPULATION_, false, 0, "unsigned int");
        cmd.add(nbPop);

/* 4 représente le nombre de nucléotides différents et 3 le nombre de
   nucléotides par séquence*/




        cmd.parse(argc, argv);

        _nbGenerations = nbGene.getValue();
        _nbPopulations = nbPop.getValue();
        _mutationOption = mutationOption.getValue();
        _migrationOption = migration.getValue();
        _selectionOption = selectionOption.getValue();


        if (file.isSet())
        {
                _fastafileOption = true;
                _file = file.getValue();
        }

        if (nbAlleles.isSet())
        {
                _PersonalisedOption = true;
                _nbAlleles = nbAlleles.getValue();
        }

        if(defaultOption.isSet())
        { _defaultOption = true; }
        else
        {
                if(nbGene.getValue()==0)
                {
                        _nbGenerations = 100; //default value
                        std::cout << "WARNING: number of generations has been set to 100\n";
                }
                if(nbPop.getValue()==0)
                {
                        _nbPopulations = 2; //default value
                        std::cout << "WARNING: number of populations has been set to 2\n";
                }
        }
}


/*---------------------------tests------------------------*/
bool test(std::vector<std::string> sequences)
{
        return sequences.size() == 0;
}

bool test4(std::vector<double> frequences)
{
        double control(0);
        for (auto frequence : frequences)
        { control += frequence; }
        return (!(std::fabs(control-1.0) < 1e-15));
}

bool test2(std::vector<std::string> sequences, size_t size)
{
        for(size_t i(0); i<sequences.size(); ++i)
        { if(!(sequences[i].size()==size)) return true; }
        return false;
}

bool test5(std::vector<std::string> sequences)
{
        for(size_t i(0); i<sequences.size(); ++i)
        {
                for(size_t j(0); j<sequences[i].size(); ++j)
                {
                        if (!(sequences[i][j]=='A') and !(sequences[i][j]=='C') and
                            !(sequences[i][j]=='G') and !(sequences[i][j]=='T'))
                        {return true;}
                }
        }
        return false;
}


std::vector<unsigned int> ask_markers()
{
        std::vector<unsigned int> markers;
        unsigned int marker;
        std::string line; //-> can't use getline on string stream
        std::stringstream ss;

        std::cout << "Enter some markers to read the fasta file : " << std::flush;
        getline(std::cin, line);
        ss << line;

        while(!ss.eof())
        {
                ss >> marker;
                if(!ss.fail())
                {
                        markers.push_back(marker);
                        ss >> std::ws;
                }
                else
                {throw("one of your marker is not an unsigned int");}
        }

        return markers;
}


std::vector<double> ask_mutationRates()
{
        std::vector<double> mutationRates;
        double rate;
        std::string line; //-> can't use getline on string stream
        std::stringstream ss;

        std::cout << "Enter a mutation rate for each position of a nucleotide : " << std::flush;
        getline(std::cin, line);
        ss << line;

        while(!ss.eof())
        {
                ss >> rate;
                if(!ss.fail() and !(rate>1) and !(rate<0))
                {
                        mutationRates.push_back(rate);
                        ss >> std::ws;
                }
                else
                {throw("one of your rates is not a number between 0 and 1");}
        }

        return mutationRates;
}


void ask_sequencesWithFrequence
        (std::vector<std::string>& sequences, std::vector<double>& frequences)
{
        size_t size;
        std::cout << "Which size should your sequences have ? : ";
        while (!(std::cin>>size))
        {
                std::cerr << "ERROR : incorrect size value\n";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Which size should your sequences have ? : ";
        }
        std::cin.ignore(); // -> get rid of '\n' left in the cin or else getline doesn't work


        std::string sequence;
        double frequence;
        std::string line; //-> can't use getline on string stream
        std::stringstream ss1;
        std::stringstream ss2;
        bool incorrectValue;

        /* do while until the entered values are coherent */
        do
        {
                try
                {
                        /* need to reinitialise sstreams, vectors and bools or else it stacks */
                        incorrectValue=false;
                        ss1.clear();
                        sequences.clear();
                        frequences.clear();

                        std::cout << "Enter sequences with their respective frequence (ex: AAA/0.5): "
                                  << std::flush;
                        getline(std::cin, line);
                        ss1 << line;

                        /* the while puts the entered values in the different vectors */
                        while(!ss1.eof())
                        {
                                ss2.clear();
                                ss1 >> line;
                                ss2 << line;
                                getline(ss2, sequence, '/');
                                ss2 >> frequence;

                                if(!ss1.fail() and !ss2.fail() and !(frequence>1) and !(frequence<0))
                                {
                                        sequences.push_back(sequence);
                                        frequences.push_back(frequence);
                                        ss1 >> std::ws;
                                        ss2 >> std::ws;
                                }
                                else
                                {
                                        std::cerr << "one of your frequences is not a number between 0 and 1\n";
                                        throw (true);
                                }
                        }

                        /* the tests will see if the entered values are coherent, else restart do while */
                        if (test(sequences))
                        {
                                std::cerr << "allele sequences are missing\n";
                                throw(true);
                        }
                        if (test2(sequences, size))
                        {
                                std::cerr << "at least one sequence doesn't respect your given size\n";
                                throw(true);
                        }
                        if(test5(sequences))
                        {
                                std::cerr << "incorrect DNA sequence (only A,C,G or T)\n";
                                throw (true);
                        }
                        if (test4(frequences))
                        {
                                std::cerr << "sum of the frequences should be equal to 1\n";
                                throw (true);
                        }
                } //-> end of try
                catch(bool b)
                {incorrectValue=true;}

        } while(incorrectValue); //-> end of do while

}
