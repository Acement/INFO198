#include <iostream>
#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

int main(){
    bool keepSearching = true;
    string search;
    string searchNormal; //La frase a buscar normalizada

    vector<string> mapa = read_file(getenv("MAPA_ARCHIVOS"));
    
    cout << "PID PROCESO: " << getpid() << endl;
    cout << "Iniciando Buscador" << endl << endl;
    do{
        cout << "Ingrese busqueda: ";
        getline(cin,search);
        cout << search << endl;
        

        for (int i = 0; i < search.length(); i++){
            searchNormal += tolower(search[i]); //Normaliza la entrada
        }
        cout << searchNormal << endl;
        if(searchNormal == "salir ahora") keepSearching = false; 
        else{
            //Seguir operaciones
        }
        searchNormal = ""; //Resetea la variable
    }while (keepSearching);

    return 0;
}