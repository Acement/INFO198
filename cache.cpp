#include <iostream>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;
//Agrega Lineas a un archivo cache vacio
void add_cache_lines_from_empty(string cachePath, string indexPath, int numLines){
    vector<string> tempCachelines = {};

    tempCachelines = read_file_up_to(indexPath,numLines);
    for(string i :tempCachelines) add_line_to_file(cachePath,i + "\n");
    return;
}

//Agrega Lineas a un archivo cache con lineas
void add_cache_lines(string cachePath, string indexPath, int numLines){
    vector<string> tempCacheLines = read_file(cachePath);
    string tempIndexLine;
    vector<string> splitedCacheLine;
    vector<string> splitedIndexLine;
    bool found = false;

    ifstream file;
    file.open(indexPath);

    //Agrega lineas que no se encuentre en el archivo cache, lo hace solo si hay menos lineas de las requeridas y hasta que se acaben las lineas en el indice invertido
    while(!file.eof() && tempCacheLines.size() < numLines){
        getline(file,tempIndexLine);
        splitedIndexLine = split(tempIndexLine,";");
        for(string i : tempCacheLines){
            splitedCacheLine = split(i,";");
            if (splitedCacheLine[0] == splitedIndexLine[0]){
                found = true;
                break;
            }
        }
        if(!found) tempCacheLines.push_back(tempIndexLine);
        found = false;
    }
    //Borra las lineas del archivo y les agrega las lineas que ya esatban y las nuevas
    erase_file_contents(cachePath);
    for(string i : tempCacheLines) add_line_to_file(cachePath,i + "\n");
    file.close();
    return;
}


int main(){
    /*
    Aca va la parte servidor/socket
    */

    int numLines = stoi(getenv("MAX_SIZE"));
    string cachePath = getenv("CACHE_FILE");
    string indexPath = getenv("INVERTED_INDEX");
    int numCacheLines = check_number_of_lines(cachePath);

    //Crea o completa el archivo cache usando las primeras MAX_SIZE lineas del indice que no se encuentren el el archivo cache
    if(numCacheLines == 0) add_cache_lines_from_empty(cachePath,indexPath,numLines);
    else if (numCacheLines < numLines) add_cache_lines(cachePath,indexPath,numLines);
    else if (numCacheLines > numLines) cut_lines_up_to(cachePath,numLines);
    else cout << "CARGANDO CACHE" << endl;

    /*
    Aca va la busqueda y el reemplazo si esque no lo pilla en el cache
    */
    

    return 0;
}