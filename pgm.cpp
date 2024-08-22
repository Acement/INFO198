#include <unistd.h>

#include "func_math.h"
#include "func_string.h"

using namespace std;

int main(int argc, char** argv){
  int c = 0, opt = 0;
  string user = "", password = "", text_in = "", num = "";
  vector<int>num_vect = {};
  bool check = false;

//Toma los valores de entrada
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
        num_vect = split_num(optarg,";");
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

  cout << "Bienvenido " << user << ", elige una de las siguientes opciones:\n"<< endl;

  while (check == false){
    opt = stoi(opt_menu());
    switch(opt){
      case 1:
        cout << "caso 1" << endl;
        check = true;
      break;
      case 2:
        cout << "caso 2" << endl;
        check = true;
      break;
      case 3:
        cout << "caso 3" << endl;
        check = true;
      break;
      case 4:
        cout << "caso 4" << endl;
        check = true;
      break;
      case 5:
        cout << "caso 5" << endl;
        check = true;
      break;
      default:
        cout << "Se ingreso caso equivocado, ingrese de nuevo" << endl;
      break;
    }
    

  }



  return 0;
}
