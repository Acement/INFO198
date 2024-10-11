#include <iostream>
#include "invertido.h"
#include "env_setter.h"

using namespace std;

int main(int argc, char** argv) {
    cout<<"PID: "<<getpid()<<endl;
    char* INVERTED_INDEX = getenv("INVERTED_INDEX");
    char* OUTPUT_DIR = getenv("OUTPUT_DIR");
    char* EXTENSION = getenv("EXTENSION");

    if (!INVERTED_INDEX || !OUTPUT_DIR || !EXTENSION) {
        cerr << "Error: Faltan variables de entorno necesarias." << endl;
        return 1;
    }

    string outputDir = string(OUTPUT_DIR);
    string extension = string(EXTENSION);
    string invertedIndexPath = string(INVERTED_INDEX);

    cargarConteo(outputDir, extension);
    crearIndiceInvertido(invertedIndexPath);
}
