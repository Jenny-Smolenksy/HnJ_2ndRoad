//
// Created by hilla on 1/8/19.
//

#ifndef HNJ_2NDROAD_FILETOUCHER_H
#define HNJ_2NDROAD_FILETOUCHER_H

#include <string>

using namespace std;
/**
 * file toucher class - deal with files
 */
class FileToucher {
    static FileToucher *instance;

    pthread_mutex_t fileAccessMutex;
    FileToucher();

public:
    static FileToucher *getInstance();

    string getByKey(string fileName, string key);

    void writeToFile(string fileName, string SolFormat, string ProbFormat);

    void writeSimple(string file,string to_write);

    bool isSame(string key,string line);

    ~FileToucher();

};


#endif //HNJ_2NDROAD_FILETOUCHER_H
