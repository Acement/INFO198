#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

string search_index(string search){
    cout << "MOTOR: Buscando en indice: " << search << endl;
    string line; 
    vector<string> splitedLine;
    ifstream file(getenv("INVERTED_INDEX"));

    while(getline(file,line)){
        cout << "MOTOR: Leyendo linea del indice: " << line << endl;
        splitedLine = split(line,";");
        if(search == splitedLine[0]){
            file.close();
            return line;
        }
    }
    cout << "MOTOR: No se encontro en indice: " << search << endl;
    file.close();

    return "";

}

// Funcion para manejar cada cliente entrante
void handleClient(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead;
    string respuesta;
    string searched;
    bool continua = true;
    // Bucle para manejar las opciones del cliente
    while (continua) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesRead] = '\0';
        cout <<"MOTOR: " << buffer << endl;
        respuesta = buffer;
        if (respuesta == "salir_ahora") {
            cout << "MOTOR SALIENDO..." << endl;
            continua = false;
            
        }else{
            searched = search_index(respuesta);
            if (searched.length() == 0) searched = respuesta+";No Se encontro";
            cout << "MOTOR: enviando a cache: " << searched << endl;
            send(clientSocket, searched.c_str(), searched.length(), 0);
        }

    }
    
    close(clientSocket); // Cerrar el socket del cliente al recibir la opción de salida
    cout << "Motor Stop " << endl;
    exit(0);
}

int main(){
    /*
    Aca va la parte socket
    tiene que escuchar(servidor)
    */
   const int opt = 1;
   int PORT_MOTOR = std::stoi(getenv("MOTOR_PORT"));
   bool check = true;

   cout << "MOTOR: PORT: " << PORT_MOTOR << endl;
   cout << "MOTOR: PID: " << getpid() << endl;

   // Crear socket de servidor
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    
    serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (serverSocket == -1) {
        perror("MOTOR: Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }
    

    // Configurar dirección del servidor
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT_MOTOR); // Puerto del servidor
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazamos socket a dirección del servidor
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("MOTOR:Error al enlazar el socket");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        perror("MOTOR:Error al escuchar");
        close(serverSocket);
        exit(EXIT_FAILURE);
    }
    cout << "MOTOR: Esperando conexiones entrantes..." << endl;

    while (check) {
        // Aceptar conexion entrante
        clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == -1) {
            perror("MOTOR:Error al aceptar la conexión");
            continue; // Continuar esperando conexiones
        }

        cout << "MOTOR:Cliente conectado" << endl;
        // Crear un nuevo hilo para manejar la conexión del cliente (solucion a desconexiones automaticas y caidas)
        thread(handleClient, clientSocket).detach(); 
        
        
    }

    
    return 0;
}