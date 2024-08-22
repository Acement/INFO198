#include <iostream>
#include <unistd.h>
#include "func_math.h"
#include "func_string.h"

using namespace std;

int main(int argc, char** argv){
  int c = 0;
  string user = "", password = "", text_in = "", num_vect = "", num = "";

  while((c=getopt(argc,argv,"u:p:t:v:n:"))!=-1){
    switch(c){
      case 'u':
        user = optarg;
      break;
      case 'p':
        password = optarg;
      break;
      case 't':
        text_in = optarg;
      break;
      case 'v':
        num_vect = optarg;
      break;
      case 'n':
        num = optarg;
      break;
    }
  }

  /*cout << "Usuario: " << user << endl;
  cout << "Contraseña: " << password << endl;
  cout << "Texto: " << text_in << endl;
  cout << "Vector de numeros: " << num_vect << endl;
  cout << "Numero: " << num << endl;*/

  return 0;
}
