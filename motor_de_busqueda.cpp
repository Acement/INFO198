#include <iostream>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

int main(){
    /*
    Aca va la parte socket
    */

    string search; //elemento a buscar
    string line; 
    vector<string> splitedLine;
    ifstream file(getenv("INVERTED_INDEX"));

    while(getline(file,line)){
        splitedLine = split(line,";");
        if(search == splitedLine[0]){
            /*
            Aca seria enviar line como mensaje a cache
            */
           return 0;
        }
    }
    /*
    Aca seria enviar "" como mensaje a cache, asi cache avisa que no se encrontro la palabra en el indice
    */
    file.close();

    return 0;
}