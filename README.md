# Genome Project of Team 1                

The goal of this project is to simulate the evolution of genotypes throughout time. To do this we based our program on The Wright-Fisher model 

## Simulation of the Wright-Fisher model                 

### Without extension:                
We model a population with N individuals ( stay constant throughout M generations) and with 2N alleles ( diploid individuals). We simulate a evolution of allele frequencies  through M generations. 

### Extensions:           

* Mutation :  We use the Juke-Cantor model to implement mutation in our simulation 
* Migration : We use the star, ring and complete  model to implement migration in our simulation
* Selection : Based on the principe that one allele can dominate over another one.


To run the extension ( see inputs example section ), you can provide the following commands:

```
--mu to activate mutation ( program will ask you mutations rates )
```

Note: the mutation rates affect highly the speed of the program. We advise you to use
approximately 1 mutation for 100 generation which corresponds to a rate of 0.001 for
100 generations. --> 0.0001 for 1000 generations.

```
-s or --sel to activate selection ( the program will ask you the selection rates )
```

Note: The selections rates have to be between -1 and ∞

```
--mi x to activate migration ( program will ask you to enter the migration rates. )
```

Note: x here stands for an integer ( 1, 2 or 3 ). Those integers correspond to
the model of migration wanted:

1: Star model.
2: Ring model.
3: Flower model.


OVERALL NOTE: It is not advised to run the simulation with mutation and selection at
the same time for memory reasons.

## Getting started               

You need to have a gtest library, a cmake library, and the T-clap library.

#### 1) Clone our repository in your terminal ( in the folder you want) using this link:

https://github.com/EPFL-SV-cpp-projects/Team_1.git

#### 2) To be in the right directory :

```
cd Team1
```

#### 3) You have to create specific directories                    

```
mkdir build
mkdir doc
```

#### 4) To compile our program

```
cd build
cmake.. 
make 
```

#### 5) To run our program:

3 main modes are available for this program:

- Default

```
./main -d
```

The default mode will simply run the simulation with the following parameters:

Number of generations: 3000
Number of alleles: 20000
Number of populations ( replicates ): 500

NO MUTATION; NO MIGRATION; NO SELECTION

- Personalized ( without file )

In this mode, you can choose all parameters. To use this mode, enter the number
of alleles you want to treat. Example:
```
./main -a 20000
```

This command will run the simulation with a total of 20'000 alleles which corresponds
to 10 000 individuals per population as we treat diploids genomes.

Then, you can provide the number of generations and populations ( replicates )
using the -g and -p commands.

After entering the commands, the program will ask you what is the size of the
sequence wanted. We advise you to choose 2 or 3 at the beginning. Then, you have
to choose which sequence to treat with what frequency.

NOTE: Sum of all frequencies has to be 1.

Example:
```
./main -a 20000 -g 3000 -p 500
```

Size of sequence: 3

Alleles and frequence: 

```	
ACC/0.5 ATT/0.5

	OR

 ACC/0.3 ATG/0.3 ATT/0.3 AGG/0.1
```


- Loading mode ( with file )

Files have to be in the extra folder, and marked by the .fa document type.
To run the simulation with a specific file, enter the following command:
```
./main --fi "../extra/YOUR_FILE.fa"
```
You can provide complementary informations such as the number of generations and
the number of replicates ( number of populations ).

NOTE: If you do not provide those informations, default one will be provided.

## output

Example: ![example](https://github.com/EPFL-SV-cpp-projects/Team_1/blob/master/extra/Frequenza_delle_Allele.png)

The Output file is available after the simulation has ran in the
build directory as "Output.txt"

Note: We provide in our program a python script that prints graphs after
the simulation with the help of matplotlib python library.

Different graphs can be generated for maximum 8 generations. If more populations
are present, all datas will be printed on a single graph.

## Documentation                     

To generate Doxygen documentation you have to be in the build directory:

```
make
make doc
```

The documentation will be available in the doc folder. Enter in doc/html and
open class.html to view all classes.

## Googletest       

To launch the tests, you can use the following command in the build directory:

make test
./unittest


## Authors                    

This project  for the EPFL course “projet en informatique pour SV” was made only by:

* **BARBARIC ROBERT** - *2nd year SV at EPFL*
* **BUU-HOANG ALIX** - *2nd year SV at EPFL*
* **HERVE NINO** - *2nd year SV at EPFL*
* **RIBAULT-GAILLARD ANTOINE** - *2nd year SV at EPFL*
* **SALIMBENI ETIENNE** - *2nd year SV at EPFL*
* **WAHLER NINA** - *2nd year SV at EPFL*

## Acknowledgments

We thank our family for moral supports. We blame Mr Antoine R-G for his bad jokes
during the oral.

Note: unfortunately, as our startup did not get enough money to grow up, we won't
make any update of the program. This is so the final version of it. We hope it will
be useful for your studies in lab.

Btw: As we can treat many populations at the same time, we advise you
to use this program on Drosophilia Melanogaster.
