#include "file_operation.h"

vector<string> read_file(string nameFile){
    vector<string> parseFile = {};
    string temp;
    fstream myFile(nameFile);

    while(getline(myFile,temp)) parseFile.push_back(temp);

    myFile.close();
    return parseFile;
}