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

//Se guarda replaceLine en la primera posicion del cache y elimina la ultima
void replace_in_cache(string cachePath, string replaceLine){
    vector<string> tempCacheVector = read_file(cachePath);
    vector<string> cacheIn = {replaceLine};
    for(string i : tempCacheVector) cacheIn.push_back(i);
    cacheIn.pop_back();
    erase_file_contents(cachePath);
    for(string i : cacheIn) add_line_to_file(cachePath,i);
}


int main(){
    /*
    Aca va la parte servidor/socket
    */

    int numLines = stoi(getenv("MAX_SIZE"));
    string cachePath = getenv("CACHE_FILE");
    string indexPath = getenv("INVERTED_INDEX");
    int numCacheLines = check_number_of_lines(cachePath);
    vector<string> readCache;
    vector<string> found = {};
    vector<string> tempSearchVector;
    string indexSearch = "";

    //Crea o completa el archivo cache usando las primeras MAX_SIZE lineas del indice que no se encuentren el el archivo cache
    if(numCacheLines == 0) add_cache_lines_from_empty(cachePath,indexPath,numLines);
    else if (numCacheLines < numLines) add_cache_lines(cachePath,indexPath,numLines);
    else if (numCacheLines > numLines) cut_lines_up_to(cachePath,numLines);
    else cout << "No se ha modificado el cache" << endl;

    cout << "CARGANDO CACHE..." << endl << endl;
    readCache = read_file(cachePath);

    string frase;
    vector<string> splitedInput = {};
    cout  << "Ingrese frase (sin caracteres especiales):";
    getline(cin,frase); 
    //Cierra el cache
    if(frase == "salir ahora"){
        /*
        Cerrar MOTOR DE BUSQUEDA
        */
        return 0;
    }else{
        splitedInput = split(frase," ");

        //Busca cada palabra de la frase
        for(string i : splitedInput){
            for(string j : readCache){
                tempSearchVector = split(j,";");
                //Si lo encuentra en el cache
                if(i == tempSearchVector[0]) {
                    found.push_back(j);
                    break;
                }else if(i != tempSearchVector[0] && j == readCache.back()){//Si no lo encuentra en el cache
                    /*
                    Aca va a buscar al motor de busqueda, guardandolo en indexSearch
                    */
                    if(indexSearch.length() == 0) cout << "No se encontro la palabra " << i << endl;
                    else{
                        replace_in_cache(cachePath,indexSearch);  
                        found.push_back(indexSearch);
                    }
                }
            }
        }
    }

    

    return 0;
}