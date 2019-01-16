#include "CacheManager.h"
#include "string"

using namespace std;
/**
 * File Cache Manager class
 */
class FileCacheManager : public CacheManager {
    string fileName;

public:
    /**
     * constructor
     * @param file
     */
    FileCacheManager(string file) {
        fileName = file;
    }

    /**
     * get the solution
     * @param problem
     * @return
     */
    string getSolution(string problem) {
        FileToucher *reader = FileToucher::getInstance();
        string sol = reader->getByKey(fileName, problem);
        return sol;
    }

    /**
     * save solution to file
     * @param problem
     * @param solution
     */
    void saveSolution(string problem, string solution) {
        FileToucher *writer = FileToucher::getInstance();
        writer->writeToFile(fileName, solution, problem);
    }

    ~FileCacheManager() = default;
};