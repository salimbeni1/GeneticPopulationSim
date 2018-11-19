 #include <gtest/gtest.h>
 #include <iostream>
 #include <vector>

 #include "../src/multiBinomial.hpp"
 #include "../src/Population.hpp"

TEST ( Multinomial, positive_value )
{
        MultiBinomial multinomial_law;

        std::vector< int > initial_vector( 2, 100 );

        initial_vector = multinomial_law.generate(initial_vector );

        for (auto& nbAllele :initial_vector )
        {
                EXPECT_TRUE( nbAllele >= 0 );
        }
}

TEST ( Multinomial, Different_list )
{
        MultiBinomial multinomial_law;

        std::vector<int> initial_vector( 2, 100 );
        std::vector<int> second_vector = multinomial_law.generate ( initial_vector );

        EXPECT_FALSE ( second_vector == initial_vector );
}


//######################### POPULATION TEST ################################

TEST ( Population, Sum_Freq )
{
        Population pop(100, {"ACC", "ATG"}, {0.5,0.5}, { 0.0, 0.0, 0.0 } );

        for ( size_t i(0); i<10; ++i )
        {
                pop.update();
                EXPECT_EQ ( pop.getTotalAlleles() / 100, 1.0 ); //sum of all frequencies should be 1
        }
}

TEST (Population, constant_number_alleles )
{
        Population pop(100, {"ACC", "ATG"}, {0.5,0.5}, { 0.0, 0.0, 0.0 });

        int value(pop.getTotalAlleles());
        for ( size_t i(0); i<10; ++i )
        {
                pop.update();

                EXPECT_EQ (value,pop.getTotalAlleles()); //sum of all frequencies should be 1
        }

}

TEST ( Population, Mutation_cst_num_alleles )
{
        Population pop(100, {"ACC", "ATG"}, {0.5,0.5}, { 0.1, 0.1, 0.1 });

        for ( size_t i(0); i<10; ++i )
        {
                pop.mute();
                pop.update();

                EXPECT_EQ ((pop.getTotalAlleles() *1.0) / 100.0, 1.0); //sum of all frequencies should be 1
        }
}
