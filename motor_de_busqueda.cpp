#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

string search_index(string search){
    string line; 
    vector<string> splitedLine;
    ifstream file(getenv("INVERTED_INDEX"));

    while(getline(file,line)){
        splitedLine = split(line,";");
        if(search == splitedLine[0]){
           return line;
        }
    }
    file.close();

    return "";

}

// Funcion para manejar cada cliente entrante
void handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;
    string respuesta;
    bool continua = true;
    // Bucle para manejar las opciones del cliente
    while (continua) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesRead] = '\0';
        cout <<"MOTOR: " << buffer << endl;
        if (buffer == "salir ahora") {
            cout << "MOTOR SALIENDO..." << endl;
            continua = false;
            
        }else{
            respuesta = search_index(buffer);
            send(clientSocket, respuesta.c_str(), respuesta.length(), 0);
        }

    }
    cout << "Motor Stop " << endl;
    close(clientSocket); // Cerrar el socket del cliente al recibir la opción de salida
}

int main(){
    /*
    Aca va la parte socket
    tiene que escuchar(servidor)
    */
   const int opt = 1;
   int PORT_MOTOR = std::stoi(getenv("MOTOR_PORT"));

   // Crear socket de servidor
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (serverSocket == -1) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Configurar dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_MOTOR); // Puerto del servidor
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazamos socket a dirección del servidor
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error al enlazar el socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        perror("Error al escuchar");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    cout << "MOTOR: Esperando conexiones entrantes..." << endl;

    while (true) {
        // Aceptar conexion entrante
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("Error al aceptar la conexión");
            continue; // Continuar esperando conexiones
        }

        cout << "Cliente conectado" << endl;
        // Crear un nuevo hilo para manejar la conexión del cliente (solucion a desconexiones automaticas y caidas)
        thread(handleClient, clientSocket).detach(); 
        
    }


    return 0;
}