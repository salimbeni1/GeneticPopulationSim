
///* Default parameter values *
#define POPU_SIZE 1000
#define NB_ALLELETOT 20000
#define ALLELE_TYPE 2
#define TIME_ 3000
#define NB_POPU 500


///* Text Message *
#define _ALLELE_TEXT_ "\033[33m Number of alleles \033[0m"
#define _FILE_TEXT_ " \033[35m local file path \033[0m"
#define _DEFAULT_TEXT_ "\033[31m Default Parameters: 10 000 individuals ( 20 000 alleles ), 500 Replicates ( populations ), 3 000 generations, no mutation, no migration, no selection. \033[0m"
#define _MIGRATION_TEXT "\033[32m type of migration \033[0m"
#define _MUT_OPTION_TEXT "\033[32m mutation option \033[0m"
#define _NBR_GENERATION_ "\033[33m Number of generations \033[0m"
#define _NBR_POPULATION_ "\033[33m Number of populations \033[0m"
#define _SEL_OPTION_TEXT "\033[32m Selection option \033[0m"

// ######### COLOURS ############

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[1;31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */



// ######### PROJECT DESCRIPTION

#define _DESCRIPTION_PROJECT "Genome Project: the goal of this project is to simulate genetic evolution through generations. To run the simulation, 3 options are available. First one is the default one. use -d or --default option. The second one is by reading a file. Use --fi and the complete path from build directory. You can also provide generations parameters and number of replicates and mutation/migration/selection options. The third one is personnalised option. you can provide all parameters. for that, use option -a with corresponds to the number of alleles and -g and -p to choose populations ( replicates ) and generations. You can also use mutation/migration/selection options."
