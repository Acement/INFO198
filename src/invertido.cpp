#include "invertido.h"

map<string, map<int, int>> invertedIndex;

void cargarConteo(string& outputDir, string& extension) {
    for (auto& entry : filesystem::directory_iterator(outputDir)) {
        if (entry.path().extension() == "." + extension) {
            int fileID = stoi(entry.path().stem().string()); // Asume que el nombre del archivo es el ID
            ifstream archivo(entry.path());
            string palabra;
            int cantidad;

            while (archivo >> palabra >> cantidad) {
                invertedIndex[palabra][fileID] += cantidad; // Acumula el conteo de la palabra
            }
            archivo.close();
        }
    }
}

void crearIndiceInvertido(string& outputFilePath) {
    ofstream output(outputFilePath);
    if (!output.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir el índice invertido: " << outputFilePath << endl;
        return;
    }

    // Escribir el índice invertido en el archivo de salida
    for (const auto& entry : invertedIndex) {
        output << entry.first; // La palabra
        for (const auto& [id, cantidad] : entry.second) {
            output << ";(" << id << "," << cantidad << ")"; // (ID, Cantidad)
        }
        output << endl;
    }

    output.close();
    cout << "Índice invertido creado exitosamente en: " << outputFilePath << endl;
}
