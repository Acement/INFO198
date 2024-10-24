#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

void procesar_mensaje(const string& mensaje) {
    int core_id;
    string operacion;

    // Parsear mensaje
    size_t pos = mensaje.find(":");
    if (pos != string::npos) {
        core_id = stoi(mensaje.substr(0, pos)); // Extraer core_id
        operacion = mensaje.substr(pos + 1);    // Extraer operación
    }

    // Convertir core_id a string
    string core_id_str = to_string(core_id);

    // Llamar al CORE
    pid_t pid = fork();
    if (pid == 0) {
        // Ejecutar CORE con core_id y operación
        execl("./core", "core", core_id_str.c_str(), operacion.c_str(), nullptr);
        perror("Error ejecutando core"); // Error si execl falla
        exit(1);
    }

    // Esperar el resultado del proceso hijo
    waitpid(pid, nullptr, 0);
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        string mensaje = argv[1];
        procesar_mensaje(mensaje);
    }
    return 0;
}
