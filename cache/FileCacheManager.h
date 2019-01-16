#include "CacheManager.h"
#include "string"

using namespace std;

class FileCacheManager : public CacheManager {
    string fileName;

public:
    FileCacheManager(string file) {
        fileName = file;
    }

    string getSolution(string problem) {
        FileToucher *reader = FileToucher::getInstance();
        string sol = reader->getByKey(fileName, problem);
        return sol;
    }

    void saveSolution(string problem, string solution) {
        FileToucher *writer = FileToucher::getInstance();
        writer->writeToFile(fileName, solution, problem);
    }

    ~FileCacheManager() { }
};