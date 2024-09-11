#include "file_operation.h"

//Abre el archivo y guarda cada linea en un vector
vector<string> read_file(string fileName){
    vector<string> parseFile = {};
    string temp;
    fstream myFile(fileName);

    while(getline(myFile,temp)) parseFile.push_back(temp);

    myFile.close();
    return parseFile;
}
void add_line_to_file(string fileName, string line){
    fstream myFile;
    myFile.open(USERFILEPATH,ios::app);
    myFile << "\n" + line;
    myFile.close();
}