#include <sys/wait.h>
#include "common.h"
#include "file_operation.h"
#include "func_string.h"

void program(int rep, vector<string> tempArray, int ogThreads, string datos){

    struct timespec timeBegin, timeEnd;
    long sec, nanosec;
    double timeElapsed;

    vector<int> threadArray = {};
    for(string i : tempArray) threadArray.push_back(stoi(i));

    cout << "PID EJECUTADOR: " << getpid() << endl;
    cout << "Iniciando analisis de performance" << endl << endl;


    erase_file_contents(datos);

    if(rep < 2){
        cout << "ERROR! Insuficientes repeticiones" << endl;
    }else{
      for(int j = 0; j < rep; j++){
      
        cout << "\nRepeticion: " << j << endl;
            

        for(int i : threadArray){
          setenv("CANTIDAD_THREAD",to_string(i).c_str(),1);
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
          add_line_to_file(datos,to_string(timeElapsed) + "\n");
        }
              
      }
      cout  << endl;

      /*
      Llamar a la funcion analisis en python
      */

      setenv("CANTIDAD_THREAD",to_string(ogThreads).c_str(),1); //Restora la cantidad de threads original


    }
}

int main(int argc, char** argv){

  int rep = stoi(argv[0]);
  vector<string> threadArray = split(argv[1],",");
  int ogThreads = stoi(argv[2]);
  string datos = argv[3];

  

  program(rep,threadArray,ogThreads,datos);

  return 0;
}