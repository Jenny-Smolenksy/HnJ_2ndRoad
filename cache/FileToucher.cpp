//
// Created by hilla on 1/8/19.
//

#include <fstream>
#include "FileToucher.h"
#include "../Utils.h"

#define DIVIDER '_'

string FileToucher::getByKey(string fileName, string key) {
    ifstream fin;
    fin.open(fileName);
    string line;
    if (fin.is_open()) {
        while (getline(fin, line)) {
            if (line.find(key, 0) != string::npos) {
                fin.close();
                //found the key problem return its sol
                return Utils::split(line, DIVIDER)[1];
            }
        }
        fin.close();
    }
    throw "key does not exist in cache! check for existence first";
}

void FileToucher::writeToFile(string fileName, string SolFormat, string ProbFormat) {
    ofstream eFile;
    eFile.open(fileName, ios::out | ios::app | ios::ate);
    if (!eFile.is_open())
        throw "cant open file";
    eFile << ProbFormat << DIVIDER << SolFormat << "\n";
    eFile.close();
}

FileToucher *FileToucher::getInstance() {
    if (instance == nullptr) {
        instance = new FileToucher();

    }
    return instance;
}


