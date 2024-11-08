#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <tuple>

#include "common.h"
#include "file_operation.h"
#include "func_string.h"

using namespace std;

//Conecta al servior (Sacado del ejemplo del ayudante)
int connectServer(const string& serverIP, int serverPort) {
    cout << "IP :" << serverIP << endl;
    cout << "PUERTO: " << serverPort << endl;
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("BUSC:Error al crear el socket del cliente");
        exit(EXIT_FAILURE);
    }
    cout << "BUSC:socket creado" << endl;
    // Configurar la dirección del servidor
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    // Conectar al servidor y verificar errores
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("BUSC: Error al conectar al servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    }

    cout << "BUSC:Conectado al servidor." << endl;
    // Retornar el socket del cliente al servidor
    return clientSocket;
}

//Envia mensaje (Sacado del ejemplo del ayudante)
void sendMessage(int clientSocket, const string& message) {
    cout << "BUSC:Enviando mensaje al servidor..." << endl;
    send(clientSocket, message.c_str(), message.length(), 0);
}

// Función para recibir y mostrar un mensaje del servidor (Sacado del ejemplo del ayudante)
string recieveMessage(int clientSocket) {
    char buffer[1024];
    string respuesta;
    ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("BUSC:Error al recibir datos del servidor");
        close(clientSocket);
        exit(EXIT_FAILURE);
    } else if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        //cout << "BUSC:Respuesta del servidor:\n" << buffer << endl;
        respuesta = buffer;
    }
    return respuesta;
}

int main(){
    /*
    aca va la parte socket
    tiene parte envia(cliente)
    */
    int PORT = std::stoi(getenv("CACHE_PORT"));
    const char* IP_SERVER = getenv("IP_SERVER"); 
    int topk = std::stoi(getenv("TOPK"));
    

    

    //Parte envia mensaje
    bool keepSearching = true;
    string search;
    string searchNormal; //La frase a buscar normalizada
    vector <string> splitedSearch = {};
    vector <string> recievedSearch = {};
    vector <string> mapa = read_file(getenv("MAPA_ARCHIVOS"));
    string recievedMessage = "";
    vector <tuple<int,int>> addVector = {};
    vector <tuple<int,int>> crossVector = {};
    vector <string> tempTuple = {};
    
    cout << "PID PROCESO: " << getpid() << endl;
    cout << "Iniciando Buscador" << endl << endl;
    cout << "Conectando al servidor" << endl;
    int cacheSocket = connectServer(IP_SERVER,PORT);
    sleep(1);
    do{
        cout << "Ingrese busqueda: ";
        getline(cin,search);
        

        for (int i = 0; i < search.length(); i++){
            searchNormal += tolower(search[i]); //Normaliza la entrada
        }
        if(searchNormal == "salir ahora") {
            cout << "SALIENDO..." << endl;
            sendMessage(cacheSocket,"salir_ahora");
            keepSearching = false;
            sleep(1);
        } else{
            
            cout << "BUSQ: enviando a cache: " << searchNormal << endl;
            sendMessage(cacheSocket,searchNormal);

            do{
                recievedMessage = recieveMessage(cacheSocket);
                cout << "BUSQ: mensaje recibido: " << recievedMessage << endl;
                if(recievedMessage != "check") recievedSearch.push_back(recievedMessage);
            }while (recievedMessage != "check");    
            print_separation();

            for(string i : recievedSearch) {
                splitedSearch = split(i,";");
                cout << splitedSearch[0] << ": ";
                if(splitedSearch[1] != "No Se encontro"){
                    for(int j = 1; j < splitedSearch.size(); j++){
                        splitedSearch[j] = remove_character(splitedSearch[j],'(');
                        splitedSearch[j] = remove_character(splitedSearch[j],')');
                        cout << splitedSearch[j] << " | ";
                        tempTuple = split(splitedSearch[j],",");
                    
                        if(addVector.size() == 0) addVector.push_back({stoi(tempTuple[0]),stoi(tempTuple[1])});
                        else{
                            int pos = 0;
                            for(tuple <int,int> x : addVector){
                                if (get<0>(x) == stoi(tempTuple[0])) {
                                    cout << "AddVector Suma" << endl;
                                    cout << "Valor inicial: " << get<1>(x);
                                    int tempValue = get<1>(x) + stoi(tempTuple[1]);
                                    get<1>(x) = tempValue;
                                    get<1>(addVector[pos]) = get<1>(x);
                                    cout << " | Resultado de suma: " << tempValue << " | Resultado real: " << get<1>(addVector[pos]) << endl;
                                    break; 
                                }
                                else if(x == addVector.back() && get<0>(x) != stoi(tempTuple[0])) {
                                    cout << "addVector push_back" << endl;
                                    addVector.push_back({stoi(tempTuple[0]),stoi(tempTuple[1])});
                                }
                                pos++;
                            }
                        }
                    }
                    cout << endl;
                }
            }
            for (tuple <int,int> i : addVector){
                cout << "ID libro: " << get<0>(i) << " Puntaje: " << get<1>(i) << endl;
            }
            
        }       
            /*
            Imprime resultados, podrias limpiar el recievedSearch depues de calcular el puntaje
            */
        
        searchNormal = ""; //Resetea la variable
        addVector.clear();
        
    }while (keepSearching);

    return 0;
}