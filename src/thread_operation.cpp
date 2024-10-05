#include "file_operation.h"
#include "thread_operation.h"

pthread_mutex_t lock;

//Struct con el puntero del vector con las direcciones
struct fileOperation{
    vector<string>* filePathList;
};


void *print_file_path(void *threadOperation){
    vector<string>* threadVector;
    string output;
    pid_t tid = gettid();
    string filePath;

    threadVector = ((struct fileOperation*)threadOperation)->filePathList;

    while((*threadVector).size() != 0){
        pthread_mutex_lock(&lock); //Bloquea el acceso al vector
        if(!(*threadVector).empty()){
            filePath = (*threadVector).back();
            (*threadVector).pop_back(); 
        }
        pthread_mutex_unlock(&lock);//Desbloquea el acceso al vector
        //Esto se hace para que no haga pop justo cuando otro thread esta usando esa variable, asi ni se repiten paths ni se corrompa la salida

        /*Aqui deberia ir la parte contar palabras, filePath es la direccion del archivo actual

        */
        cout << filePath << " | Thread " << tid << endl;
    }

    return NULL;
}

//Abre los treads y les asigna una operacion
void open_threads(){
    int cantThreads = stoi(getenv("CANTIDAD_THREAD"));
    int rc;
    int i;
    pthread_t threads[cantThreads];

    //Crea el vector con las direcciones de los archivos a leer
    vector<string> filePathList = get_files(getenv("MAPA_ARCHIVOS"));

    //Asigna el puntero del vector al puntero dentro de la estructura
    struct fileOperation *threadOperation = (struct fileOperation *)malloc(sizeof(struct fileOperation));
    threadOperation->filePathList = &filePathList;

    //Mutex es para la sincronizacion de los vectores
    if (pthread_mutex_init(&lock, NULL) != 0) { 
        printf("\n mutex init has failed\n"); // Si no se puede inicializar Mutex no hace nada
    }
    else{
        for(i = 0; i < cantThreads; i++){
            rc = pthread_create(&threads[i],NULL,print_file_path,(void *)threadOperation); //Para hacer las operacion con los threads (Thread a operar,limite inferior(?),Funcion a operar,limite superior(?))

            if(rc){
                cout << "No se pudo crear Thread " << rc << endl;
            }
        }

        for(i = 0; i < cantThreads; i++) pthread_join(threads[i],NULL); //Cierra los threads despues de haberlos usado

        pthread_mutex_destroy(&lock); //Cierra Mutex
    }

}