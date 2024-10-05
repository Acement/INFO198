#include "thread_operation.h"

//operacion de ejemplo
void *PrintHello(void *threadid) {
    long tid;
    tid = (long)threadid;
    cout << "Hello World! Thread ID, " << tid << endl;
    pthread_exit(NULL);
}

//Abre los treads y les asigna una operacion
void open_threads(){
    int cantThreads = stoi(getenv("CANTIDAD_THREAD"));
    int rc;
    int i;
    pthread_t threads[stoi(getenv("CANTIDAD_THREAD"))];

    for(i = 0; i < cantThreads; i++){
        cout << "Creando Thread" << endl;
        rc = pthread_create(&threads[i],NULL,PrintHello,(void *)i); //paa hacer las operacion con los threads (Thread a operar,limite inferior(?),Funcion a operar,limite superior(?))

        if(rc){
        cout << "No se pudo crear Thread " << rc << endl;
        }
    }

    for(i = 0; i < cantThreads; i++) pthread_join(threads[i],NULL); //Cierra los threads despues de haberlos usado

    //IDEA: para contar las palabras por libros, podriamos tener un vector con todos los libros donde cada thread va a poder sacar un libro y de esa forma que no se opere de nuevo, el sacar libro hacerlo con un puntero

}