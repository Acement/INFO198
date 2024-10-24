#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

const char* procesos_path = getenv("PROCESOS");
const char* resultados_path = getenv("RESULTADOS");
const int cantidad_cores = stoi(getenv("CANTIDAD_CORES"));

vector<bool> cores_disponibles(cantidad_cores, true); // Inicialmente, todos los núcleos están libres

int obtener_core_disponible() {
    for (int i = 0; i < cantidad_cores; ++i) {
        if (cores_disponibles[i]) {
            cores_disponibles[i] = false; // Marcar el núcleo como ocupado
            return i; // Retorna el primer núcleo disponible
        }
    }
    return -1; // Ningún núcleo disponible
}

void liberar_core(int core_id) {
    cores_disponibles[core_id] = true; // Marcar el núcleo como libre
}

void ejecutar() {
    ifstream procesos(procesos_path);
    string linea;

    while (getline(procesos, linea)) {
        // Lógica para asignar el CORE disponible
        int core_id = obtener_core_disponible();
        if (core_id == -1) {
            cout << "No hay núcleos disponibles en este momento." << endl;
            continue; // No se puede procesar la línea actual
        }

        // Enviar mensaje al DISTRIBUIDOR
        string mensaje = to_string(core_id) + ":" + linea;

        // Crear un proceso para el DISTRIBUIDOR
        pid_t pid = fork();
        if (pid == 0) {
            // Ejecutar DISTRIBUIDOR
            execl("./distribuidor", "distribuidor", mensaje.c_str(), NULL);
            exit(0);
        } else {
            // Esperar a que el DISTRIBUIDOR termine
            waitpid(pid, nullptr, 0);
            liberar_core(core_id); // Liberar el núcleo después de que el proceso finalice
        }
    }
    cout << "Resultados almacenados en: " << resultados_path << endl;
}

int main() {
    ejecutar();
    return 0;
}