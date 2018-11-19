#include "Simulation.hpp"
#include "ConstGlobal.h"

#include <assert.h>
#include <random>


///////////////////////////////////////////////////////
///               CONSTRUCTOR                      ///
/////////////////////////////////////////////////////


Simulation::Simulation() : NbPopulations_ ( 500 ), NbGenerations_ ( 3000 ), MigrationModel_(0), ShouldIMute_ ( false )
{
        sequenceSize_ = 3;
        Output_.open("Output.txt");
        if ( !Output_.is_open() )
        { std::cerr << "COULD NOT OPEN OFSTREAM FILE"; }

        Output_ << 0 << '\t';

        for ( size_t i(0); i < NbPopulations_; ++i )
        {
                Populations_.push_back(new Population( 20000,{"ATG", "ATT"},{0.3,0.7}, { 0.0, 0.0, 0.0 } ) );
                SaveToFile( Output_, Populations_[i]->getAlleleQuantity(), Populations_[i]->getTotalAlleles() );
        }

        Output_ << '\n';

        askMigrationRate();

        std::cout << RED <<"FACT : Vous ne pouvez pas respirer et avaler en même temps." << std::endl;
        std::cout <<std::endl;
}



Simulation::Simulation(int const& NbGenerations,int const& NbPopulations,
                       std::string const& file,
                       std::vector<unsigned int> const& markers,
                       int const& migrationMode, bool mutant, bool selectionOption)
        : NbPopulations_( NbPopulations), NbGenerations_ (NbGenerations), MigrationModel_(migrationMode), ShouldIMute_ ( mutant ), Selection_(selectionOption)
{

        Output_.open("Output.txt");
        if ( !Output_.is_open() )
        { std::cerr << "COULD NOT OPEN OFSTREAM FILE"; }

        Output_ << 0 << '\t';

        std::map<std::string, int> population(LoadFromFile(file,markers));
        sequenceSize_ = population.begin()->first.size();

        std::vector<double> MutRate;
        askMutant(MutRate);

        for ( size_t i(0); i < NbPopulations_; ++i )
        {
                Populations_.push_back(new Population(population, MutRate) );
                SaveToFile( Output_, Populations_[i]->getAlleleQuantity(), Populations_[i]->getTotalAlleles() );
        }
        Output_ << '\n';

        askMigrationRate();

        if ( Selection_ )
        {
                setSpecificityRatio();
        }

        std::cout << RED <<"FACT : Vous pouvez toujours voir votre nez, mais votre cerveau fait comme s'il n'était pas là." << std::endl;
        std::cout <<std::endl;
}




Simulation::Simulation(int const& NbGeneration, int const& NbPopulation, int const& nbAlleles,
                       std::vector<std::string> sequences, std::vector<double> frequencies, int const& migrationMode, bool mutant, bool selectionOption)
        : NbPopulations_ (NbPopulation), NbGenerations_(NbGeneration), MigrationModel_(migrationMode), ShouldIMute_( mutant ), Selection_(selectionOption)
{
        assert ( sequences[0].size() != 0 );
        sequenceSize_ = sequences[0].size();
        std::vector<double> MutRate;
        askMutant(MutRate);

        Output_.open("Output.txt");
        if ( !Output_.is_open() )
        { std::cerr << "COULD NOT OPEN OFSTREAM FILE"; }

        Output_ << 0 << '\t';
        for ( size_t i(0); i < NbPopulations_; ++i )
        {
                Populations_.push_back( new Population(nbAlleles, sequences, frequencies, MutRate));
                SaveToFile( Output_, Populations_[i]->getAlleleQuantity(), Populations_[i]->getTotalAlleles() );
        }
        Output_ << '\n';

        askMigrationRate();

        if ( Selection_ )
        {
                setSpecificityRatio();
        }

        std::cout<< RED <<"FACT : Vous n'avez jamais vu votre vrai visage, seulement des photos et votre reflet." << std::endl;
        std::cout <<std::endl;
}

////////////////////////////////////////////////////////
///               DESTRUCTOR                        ///
//////////////////////////////////////////////////////


Simulation::~Simulation() //Destructor
{
        for ( auto& element : Populations_ )
        {
                Output_ << '\t';
                for (auto sequence : element->getAlleleSequence() )
                { Output_<<sequence << '|'; }

                Output_ << '\t';

                delete element; //avoids memory leak
        }

        Output_.close();
}



////////////////////////////////////////////////////////////////////
///               Runs the Simulation                           ///
//////////////////////////////////////////////////////////////////

void Simulation::run()
{
        for ( size_t loop(0); loop < NbGenerations_; ++loop )
        {
                setSelectivityRatioRandom();
                Output_ << loop + 1 << '\t';

                for ( auto& population : Populations_ )
                {
                        if ( !Selection_ )
                        {
                                population->update();
                        }
                        else {  population->update(SpecificityRatio_); }

                        if ( ShouldIMute_ )
                        { population->mute(); }

                        SaveToFile(Output_, population->getAlleleQuantity(), population->getTotalAlleles());
                }

                Migrate();
                Output_<<'\n';
                displayCountdown(loop,NbGenerations_-1);
        }
        std::cout<<std::endl;
        int graph(0);
        if(Populations_.size() < 8)
        { graph += system("python ../scripts/qMultiUltraGraphPro.py &"); }
        graph += system("python ../scripts/qUltraGraphPro.py &");
        if(graph != 0)
        { std::cout<<"erreur dans la creation des graphes"<<std::endl; }
}


///////////////////////////////////////////////////////
///                    ANNEXE                      ///
/////////////////////////////////////////////////////


void Simulation::mapFusion(std::map<std::string,int> & changingMap, std::map<std::string, int> const& additionalMap)
{
        for(auto& add : additionalMap)
        { changingMap[add.first] += add.second; }
}


void Simulation::displayCountdown(double chan, double maxiv)
{
        for(int j(1); j<43; ++j)
        {
                if(std::abs(chan-(maxiv/42)*j)<0.9)
                {
                    std::cout <<"  | ";
                        for(int a(0); a<=j; ++a)
                        {
                                if(0<=a and a<6)
                                { std::cout<<"\033[48;5;129m"<<" "<<"\033[0m"; }
                                if(6<=a and a<12)
                                { std::cout<<"\033[48;5;21m"<<" "<<"\033[0m"; }
                                if(12<=a and a<18)
                                { std::cout<<"\033[48;5;81m"<<" "<<"\033[0m"; }
                                if(18<=a and a<24)
                                { std::cout<<"\033[48;5;46m"<<" "<<"\033[0m"; }
                                if(24<=a and a<30)
                                { std::cout<<"\033[48;5;226m"<<" "<<"\033[0m"; }
                                if(30<=a and a<36)
                                { std::cout<<"\033[48;5;208m"<<" "<<"\033[0m"; }
                                if(36<=a and a<42)
                                { std::cout<<"\033[48;5;196m"<<" "<<"\033[0m"; }
                        }

                        for(int a(41-j); a>0; --a)
                        { std::cout<<"\033[1;40;30m"<<" "<<"\033[0m"; }
                        int q((chan/maxiv)*100);
                        std::cout<<" | "<<q<<" %";
                        std::cout<<"\r"<<std::flush;
                }
        }
}


////////////////////////////////////////////////////////////////////
///                    Output Management                        ///
//////////////////////////////////////////////////////////////////

std::map<std::string, int> Simulation::LoadFromFile( std::string const& file, std::vector<unsigned int> const& markers)  //pour une population
{
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        std::map<std::string, int> Alleles;

        std::ifstream input(file);

        std::string wholeSequence;
        std::string newSequence;

        if(input.is_open())
        {
                while(!input.eof())
                {
                        getline(input, wholeSequence);
                        wholeSequence.clear();
                        getline(input, wholeSequence);

                        for ( auto& index : markers )
                        {
                                if ( wholeSequence[index] == 'A' or  wholeSequence[index] == 'C' or wholeSequence[index] == 'T' or wholeSequence[index] == 'G' )
                                { newSequence += wholeSequence[index]; }
                                else
                                {
                                        std::vector<char> nucl = { 'A', 'T', 'C', 'G' };
                                        newSequence += nucl[dis(gen)];
                                }
                        }

                        ++Alleles[newSequence];

                        newSequence.clear();

                        input >> std::ws;
                }
        }
        else
        { std::cerr << "ERROR: COULD NOT READ FILE" << std::endl; }

        input.close();

        return Alleles;
}


void Simulation::SaveToFile(std::ofstream& output,std::vector<int> Alleles, int const& nbAlleles ) const
{
        output.precision(2);
        for ( size_t i(0); i<Alleles.size(); ++i )
        {
                if ( !(i==0) )
                { output<< "|"; }
                output << (1.0 * Alleles[i] / nbAlleles);
        }
        output << '\t';
}



////////////////////////////////////////////////////////////////////////
//                           MIGRATION                                //
////////////////////////////////////////////////////////////////////////

void Simulation::starMigrationModel(double migrationRatioUser)
{

        int nbrPop = Populations_.size();
        double ratioMax = 1.0/nbrPop;
        double migrationRatio(0);
        double nbrAlle = Populations_[0]->getTotalAlleles();


        if(migrationRatioUser < 0)
        {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, ratioMax);

                migrationRatio = dis(gen);
        }
        else if(migrationRatioUser <ratioMax)
        { migrationRatio = migrationRatioUser; }
        else
        {
                std::cout<<"error : incompatible migration ratio"<<std::endl;
                std::cout<<"the migration ratio will be set to 0"<<std::endl;
        }


        std::vector<std::map<std::string, int> > m(Populations_.size()); // each map is the number of allele that is going to migrate to a specific population
        for(int i(0); i<nbrPop; ++i)
        {
                for(int j(0); j<nbrPop; ++j)
                {
                        if(j != i)
                        { mapFusion(m[i],Populations_[j]->leavingPop(migrationRatio*nbrAlle)); }
                }
        }


        for(size_t i(0); i<Populations_.size(); ++i)
        { Populations_[i]->insertMigrants(m[i]); }
}


void Simulation::flowerMigrationModel(double migrationRatioUser)
{
        int nbrPop = Populations_.size();
        double ratioMax = 1.0/(nbrPop-1);
        double migrationRatio(0);

        double nbrAlle = Populations_[0]->getTotalAlleles();


        if(migrationRatioUser < 0)
        {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, ratioMax);

                migrationRatio = dis(gen);
        }
        else if(migrationRatioUser <ratioMax)
        { migrationRatio = migrationRatioUser; }
        else
        {
                std::cout<<"error : incompatible migration ratio"<<std::endl;
                std::cout<<"the migration ratio will be set to 0"<<std::endl;
        }


        std::vector<std::map<std::string, int> > m(Populations_.size()); // each map is the number of allele that is going to migrate to a specific population

        for(int i(1); i<nbrPop; ++i)
        {
                mapFusion(m[0],Populations_[i]->leavingPop(migrationRatio*nbrAlle));
                mapFusion(m[i],Populations_[0]->leavingPop(migrationRatio*nbrAlle));
        }


        for(size_t i(0); i<Populations_.size(); ++i)
        { Populations_[i]->insertMigrants(m[i]); }

}


void Simulation::ringMigrationModel(double migrationRatioUser)
{

        int nbrPop = Populations_.size();
        double ratioMax = 1.0/(2);
        double migrationRatio(0);

        double nbrAlle = Populations_[0]->getTotalAlleles();


        if(migrationRatioUser < 0)
        {
                static std::random_device rd;
                static std::mt19937 gen(rd());
                std::uniform_real_distribution<> dis(0.0, ratioMax);

                migrationRatio = dis(gen);
        }
        else if(migrationRatioUser <ratioMax)
        {
                migrationRatio = migrationRatioUser;
        }
        else
        {
                std::cout<<"error : incompatible migration ratio"<<std::endl;
                std::cout<<"the migration ratio will be set to 0"<<std::endl;
        }

        std::vector<std::map<std::string, int> > m(Populations_.size()); // each map is the number of allele that is going to migrate to a specific population

        for(int i(0); i<nbrPop; ++i)
        {
                if(i == nbrPop-1)
                { mapFusion(m[i],Populations_[0]->leavingPop(migrationRatio*nbrAlle)); }
                else
                { mapFusion(m[i],Populations_[i+1]->leavingPop(migrationRatio*nbrAlle)); }
        }


        for(size_t i(0); i<Populations_.size(); ++i)
        { Populations_[i]->insertMigrants(m[i]); }

}


void Simulation::Migrate()
{
        if ( MigrationModel_ == 1 )
        {
                starMigrationModel(MigrationRate_);
        }

        if ( MigrationModel_ == 2 )
        {
                ringMigrationModel(MigrationRate_);
        }

        if ( MigrationModel_ == 3 )
        {
                flowerMigrationModel(MigrationRate_);
        }
}

void Simulation::askMigrationRate()
{
        if ( MigrationModel_ != 0 )
        {
                std::cout << "Enter the migration rate : ";
                std::cin >> MigrationRate_;

                std::cout<< std::endl;
        }
        else { MigrationRate_ = 0.0; }
}


////////////////////////////////////////////////////////////////////
///                           MUTATION                          ///
//////////////////////////////////////////////////////////////////




void Simulation::askMutant( std::vector<double>& trioRate)
{
        if ( ShouldIMute_ )
        {
                double rate;
                bool condition;

                for(int i(0); i<sequenceSize_; ++i)
                {
                        do {
                                std::cout << "Enter mutation rate for nucleotide " << i+1 << " : ";
                                std::cin >> rate;

                                condition = std::cin.fail();
                                std::cin.clear();
                                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                                if (condition) std::cout << "ERROR : incorrect rate value\n";
                                if (rate<0 or rate>1) std::cout << "ERROR : a rate should be between 0 and 1\n";
                        } while(condition or rate < 0 or rate > 1);

                        trioRate.push_back(rate);
                }
        }
        else
        { trioRate = { 0.0, 0.0, 0.0 }; } //useless but checks no lags
}


////////////////////////////////////////////////////////////////////
///                           SELECTIVITY                       ///
//////////////////////////////////////////////////////////////////


void Simulation::setSelectivityRatio(std::string allele,double specificity )
{
        // si on veut on peut mettre ici le controle de la valeur de specificity ex : pa plus petit de -1
        SpecificityRatio_[allele] = specificity;
}


void Simulation::setSelectivityRatioRandom()
{
        double n(0);
        // rend le en distribution de -1 a +infini

        std::map<std::string,double>::iterator it;

        for(auto pop: Populations_)
        {
                for(auto al : pop->getAlleleSequence())
                {
                        it = SpecificityRatio_.find(al);

                        if(it == SpecificityRatio_.end())
                        { SpecificityRatio_[al] = n; }
                }
        }
}

void Simulation::setSpecificityRatio()
{
        std::vector<std::string> initialsequences(Populations_[0]->getAlleleSequence());
        std::vector<double> initalRatios;

        for ( size_t sequence(0); sequence < initialsequences.size(); ++sequence)
        {
                double a;
                do {
                        std::cout << "Enter specific ratio for allele " << initialsequences[sequence]
                                  << " : ";
                        std::cin >> a;
                        if ( a < -1 ) { std::cerr << "ERROR: EXPECT value >= -1"; }

                } while ( a < -1 );

                initalRatios.push_back(a);

                SpecificityRatio_[initialsequences[sequence]] = initalRatios[sequence];
        }
}
