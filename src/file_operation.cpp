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
    myFile.open(fileName,ios::app);
    myFile << line;
    myFile.close();
}

void add_user_to_file(string fileName, string line){
    fstream myFile;
    myFile.open(fileName,ios::app);
    
    myFile << "\n" + line;
    myFile.close();
}

void erase_lines(string fileName, vector<string> fileIn){
    ofstream myFile;
    myFile.open(fileName,ofstream::out | ofstream::trunc);
    myFile.close();
    int j = 1;

    for(string i : fileIn){
        if(j == fileIn.size()) add_line_to_file(fileName,i);
        else add_line_to_file(fileName,i + "\n");
        j++;
    }

}