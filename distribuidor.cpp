#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void procesar_mensaje(const string& mensaje) {
    int core_id;
    string operacion;
    string datos;

    // Parsear mensaje
    size_t pos = mensaje.find(":");
    if (pos != string::npos) {
        core_id = stoi(mensaje.substr(0, pos));
        operacion = mensaje.substr(pos + 1);
    }

    // Llamar al CORE
    pid_t pid = fork();
    if (pid == 0) {
        // Ejecutar CORE
        execl("./core", "core", operacion.c_str(), nullptr);
        exit(0);
    }
    // Esperar el resultado
    waitpid(pid, nullptr, 0);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        string mensaje = argv[1];
        procesar_mensaje(mensaje);
    }
    return 0;
}
