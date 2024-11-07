#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <thread>

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

// Función para conectar al servidor
int connectServer(const string& serverIP, int serverPort) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }
    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    // Conectar al servidor y verificar errores
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("CACHE:Error al conectar al servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    cout << "Conectado al servidor." << endl;
    // Retornar el socket del cliente al servidor
    return clientSocket;
}

// Función para enviar un mensaje al servidor
void sendMessage(int clientSocket, const string& message) {
    cout << "CACHE: Enviando mensaje al servidor: " <<  message << endl;
    send(clientSocket, message.c_str(), message.length(), 0);
}

// Función para recibir y mostrar un mensaje del servidor
string receiveMessage(int clientSocket) {
    char buffer[1024];
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Error al recibir datos del servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    } else if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        cout << "Respuesta del servidor:\n" << buffer << endl;
    }
    return buffer;
}

//Envia el mensaje al motor
string send_message_motor(string message){
    int PORT_MOTOR = std::stoi(getenv("MOTOR_PORT"));
    const char* IP_SERVER = getenv("IP_SERVER");

    int clientSocket = connectServer(IP_SERVER, PORT_MOTOR); // Conectar al servidor
    bool continua = true;

    if (message == "salir_ahora"){
        sendMessage(clientSocket,"salir_ahora");
        return "";
    }else{
         sendMessage(clientSocket,message);

        return receiveMessage(clientSocket);
    }   
}
   

//Funcion Busqueda
string wordSearch(string search,vector<string> readCache){
    vector<string> tempSearchVector = {};
    string indexSearch;
   
    for(string j : readCache){
        tempSearchVector = split(j,";");
        //Si lo encuentra en el cache
        if(search == tempSearchVector[0]) {
            cout << "CACHE" << endl;
            return j;
            break;
        }else if(search != tempSearchVector[0] && j == readCache.back()){//Si no lo encuentra en el cache
            cout << "Mandando a motor" << endl;
            indexSearch = send_message_motor(search);
            if(indexSearch.length() == 0) {
                cout << "No se encontro la palabra " << search << endl;
                return "No se encontro " + search;
            }else{
                replace_in_cache(getenv("CACHE_FILE"),indexSearch);  
                return indexSearch;
            }
        }
    }
}


// Funcion para manejar cada cliente entrante
void handleClient(int clientSocket,vector<string> readCache) {
    char buffer[1024];
    ssize_t bytesRead;
    string respuesta;
    bool continua = true;
    vector<string> splitedBuffer = {};
    string checker = "check";
    // Bucle para manejar las opciones del cliente
    while (continua) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        buffer[bytesRead] = '\0';
        cout << "CACHE: " << buffer << endl;
        respuesta = buffer;
        if (respuesta == "salir_ahora") {
            cout << "CACHE SALIENDO ..." << endl;
            
            send_message_motor("salir_ahora");
            
            sleep(1);
            continua = false;
            
            
        }else{
            splitedBuffer = split(buffer, " ");
            for (string i : splitedBuffer){
                respuesta = wordSearch(i,readCache);
                send(clientSocket, respuesta.c_str(), respuesta.length(), 0);
            }
            send(clientSocket, checker.c_str() , checker.length(), 0);
        }
        
        
    }
    close(clientSocket); // Cerrar el socket del cliente al recibir la opción de salida
    cout << "Cache Stop " << endl;
    exit(0);
}



int main(){

    //Operaciones del cache
    const int opt = 1;
    int numLines = stoi(getenv("MAX_SIZE"));
    string cachePath = getenv("CACHE_FILE");
    string indexPath = getenv("INVERTED_INDEX");
    int numCacheLines = check_number_of_lines(cachePath);
    vector<string> readCache;

    //Crea o completa el archivo cache usando las primeras MAX_SIZE lineas del indice que no se encuentren el el archivo cache
    if(numCacheLines == 0) add_cache_lines_from_empty(cachePath,indexPath,numLines);
    else if (numCacheLines < numLines) add_cache_lines(cachePath,indexPath,numLines);
    else if (numCacheLines > numLines) cut_lines_up_to(cachePath,numLines);
    else cout << "No se ha modificado el cache" << endl;

    cout << "CARGANDO CACHE..." << endl << endl;
    readCache = read_file(cachePath);
    /*
    Aca va la parte servidor/socket
    tiene parte escucha y parte envia(servidor/cliente)
    */
    //Variables de cache
    int CACHE_PORT = std::stoi(getenv("CACHE_PORT"));
    cout << "CACHE: PORT: " << CACHE_PORT << endl;
    cout << "CACHE: PID: " << getpid() << endl;

    int cacheCLientSocket, cacheServerSocket;

    struct sockaddr_in cacheServerAddr, cacheClientAddr;
    socklen_t cacheClientAddrLen = sizeof(cacheClientAddr);

        //Crea el socket del servidor
    cacheServerSocket = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(cacheServerSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (cacheServerSocket == -1) {
        perror("Error al crear el socket del servidor");
        exit(EXIT_FAILURE);
    }
    

        //Enlaza la direccion al socket
    memset(&cacheServerAddr, 0, sizeof(cacheServerAddr));
    cacheServerAddr.sin_family = AF_INET;
    cacheServerAddr.sin_port = htons(CACHE_PORT); // Puerto del servidor
    cacheServerAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazamos socket a dirección del servidor
    
    if (bind(cacheServerSocket, (struct sockaddr *)&cacheServerAddr, sizeof(cacheServerAddr)) == -1) {
        perror("Error al enlazar el socket");
        close(cacheServerSocket);
        exit(EXIT_FAILURE);
    }


    // Escuchar conexiones entrantes
    if (listen(cacheServerSocket, 5) == -1) {
        perror("Error al escuchar");
        close(cacheServerSocket);
        exit(EXIT_FAILURE);
    }

    cout << "CACHE: Esperando conexiones entrantes..." << endl;

    while (true) {
        // Aceptar conexion entrante
        cacheCLientSocket = accept(cacheServerSocket, (struct sockaddr *)&cacheClientAddr, &cacheClientAddrLen);
        cout << "socket aceptado" << endl;
        if (cacheCLientSocket == -1) {
            perror("Error al aceptar la conexión");
            continue; // Continuar esperando conexiones
        }

        cout << "Cliente conectado" << endl;
        // Crear un nuevo hilo para manejar la conexión del cliente (solucion a desconexiones automaticas y caidas)
        thread(handleClient, cacheCLientSocket,readCache).detach(); 
        
    }
    
    exit(0);

    return 0;
}