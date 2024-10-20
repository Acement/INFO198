#include <sys/wait.h>
#include "common.h"
#include "file_operation.h"
#include "func_string.h"

void program(){

    int ogThreads; //Cantidad original de threads

    int rep = stoi(getenv("REPETICIONES"));

    struct timespec timeBegin, timeEnd;
    long sec, nanosec;
    double timeElapsed;

    vector<string> tempArray = split(getenv("ARRAY_THREADS"),",");
    vector<int> threadArray = {};
    for(string i : tempArray) threadArray.push_back(stoi(i));


    ogThreads = stoi(getenv("CANTIDAD_THREAD")); //Guarda la cantidad original de threads

    erase_file_contents(getenv("DATOS"));

    if(rep < 2){
        cout << "ERROR! Insuficientes repeticiones" << endl;
    }else{
        for(int i : threadArray){
            setenv("CANTIDAD_THREAD",to_string(i).c_str(),1);
            add_line_to_file(getenv("DATOS"),to_string(i) + "\n"); //Guarda la cantidad de threads en el archivo ()
            for(int j = 0; j < rep; j++){
                clock_gettime(CLOCK_REALTIME, &timeBegin);
                pid_t pid = fork(); //Crear un proceso hijo
                if (pid == 0) { 
                  execl("./contar_paralelo", "contar_paralelo", NULL);
                  exit(0); 
                }
          
                else if (pid > 0) {
                  wait(NULL); 
                } 
          
                else {
                  cout<<"Error al crear el proceso"<<endl;
                }
                clock_gettime(CLOCK_REALTIME, &timeEnd);

                sec = timeEnd.tv_sec - timeBegin.tv_sec;
                nanosec = timeEnd.tv_nsec - timeBegin.tv_nsec;
                
                timeElapsed = sec + nanosec*1e-9;
                add_line_to_file(getenv("DATOS"),to_string(timeElapsed) + "\n");
              }
              
            }
            cout  << endl;

            /*
            Llamar a la funcion analisis en python
            */

            setenv("CANTIDAD_THREAD",to_string(ogThreads).c_str(),1); //Restora la cantidad de threads original


          }
}

int main(){
    program();

    return 0;
}