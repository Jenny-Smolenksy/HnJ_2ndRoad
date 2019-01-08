#include "ReverseFileCache.h"
#include "FileToucher.h"

#define REVERSE_FILE "rFile"

template<char *Problem, char *Soltion>
char *ReverseFileCache<Problem, Soltion>::getSolution(char *problem) {
    FileToucher *reader = FileToucher::getInstance();
    string sol = reader->getByKey(REVERSE_FILE, problem);
    return const_cast<char *>(sol.data());
}

template<char *Problem, char *Soltion>
void ReverseFileCache<Problem, Soltion>::saveSolution(char *problem, char *solution) {
    FileToucher *writer = FileToucher::getInstance();
    //TODO arrange problem and solution in wanted way before sending it to writer
    //write to reverse file in this mode  problem_solution
    writer->writeToFile(REVERSE_FILE, solution, problem);

}