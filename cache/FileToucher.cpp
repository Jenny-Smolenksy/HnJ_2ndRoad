//
// Created by hilla on 1/8/19.
//

#include <fstream>
#include "FileToucher.h"
#include "../Utils.h"
#define DIVIDER '$'
FileToucher *FileToucher::instance = nullptr;

FileToucher::FileToucher() {

    pthread_mutex_init(&fileAccessMutex, nullptr);
}

/**
 * get the file toucher - singelton way
 * @return
 */
FileToucher *FileToucher::getInstance() {
    if (instance == nullptr) {
        instance = new FileToucher();
    }
    return instance;
}

/**
 * get a string by a specific key
 * @param fileName
 * @param key
 * @return
 */
string FileToucher::getByKey(string fileName, string key) {

    //lock mutual resource
    pthread_mutex_lock(&fileAccessMutex);

    ifstream fin;
    fin.open(fileName);
    string line;
    vector<string> splited;
    if (fin.is_open()) {
        while (getline(fin, line) && !line.empty()) {
            splited = Utils::split(line, DIVIDER);
            if (isSame(splited[0], key)) {
                fin.close();
                //release lock
                pthread_mutex_unlock(&fileAccessMutex);
                //found the key problem return its sol
                return splited[1];
            }
        }
        fin.close();
    }
    //release lock
    pthread_mutex_unlock(&fileAccessMutex);
    throw "key does not exist in cache! check for existence first";
}
/**
 * write problem to specific file
 * @param fileName
 * @param SolFormat
 * @param ProbFormat
 */
void FileToucher::writeToFile(string fileName, string SolFormat, string ProbFormat) {
    //lock mutual resource
    pthread_mutex_lock(&fileAccessMutex);

    ofstream eFile;
    eFile.open(fileName, ios::out | ios::app | ios::ate);
    if (!eFile.is_open()) {
        //release lock
        pthread_mutex_unlock(&fileAccessMutex);
        throw "cant open file";
    }
    eFile << ProbFormat << DIVIDER << SolFormat << "\n";
    eFile.close();

    //release lock
    pthread_mutex_unlock(&fileAccessMutex);
}

/**
 * check if two strings are the same
 * @param key
 * @param line
 * @return
 */
bool FileToucher::isSame(string key, string line) {
    if (key.length() != line.length()) {
        return false;
    }
    for (int i = 0; i < line.length(); i++) {
        if (key[i] != line[i]) {
            return false;
        }
    }
    return true;
}

/**
 * write to file ,no format
 * @param file
 * @param to_write
 */
void FileToucher::writeSimple(string file, string to_write) {

    //lock mutual resource
    pthread_mutex_lock(&fileAccessMutex);

    ofstream eFile;
    eFile.open(file, ios::out | ios::app | ios::ate);
    if (!eFile.is_open()) {
        //release lock
        pthread_mutex_unlock(&fileAccessMutex);
        throw "cant open file";
    }
    eFile << to_write << "\n";
    eFile.close();

    //release lock
    pthread_mutex_unlock(&fileAccessMutex);
}

/**
 * distructor
 */
FileToucher::~FileToucher() {
    if (instance != nullptr) {
        instance = nullptr;
    }
}



