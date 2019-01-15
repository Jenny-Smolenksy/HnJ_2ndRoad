//
// Created by hilla on 1/8/19.
//

#include <fstream>
#include "FileToucher.h"
#include "../Utils.h"


#define DIVIDER '$'
FileToucher *FileToucher::instance = nullptr;

FileToucher *FileToucher::getInstance() {
    if (instance == nullptr) {
        instance = new FileToucher();

    }
    return instance;
}

string FileToucher::getByKey(string fileName, string key) {
    ifstream fin;
    fin.open(fileName);
    string line;
    vector<string> splited;
    if (fin.is_open()) {
        while (getline(fin, line) && !line.empty()) {
            splited = Utils::split(line, DIVIDER);
            if (isSame(splited[0], key)) {
                fin.close();
                //found the key problem return its sol
                return splited[1];
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

void FileToucher::writeSimple(string file, string to_write) {
    ofstream eFile;
    eFile.open(file, ios::out | ios::app | ios::ate);
    if (!eFile.is_open())
        throw "cant open file";
    eFile << to_write << "\n";
    eFile.close();
}




