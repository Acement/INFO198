#include <unistd.h>

#include "func_math.h"
#include "func_string.h"
#include "common.h"

using namespace std;


int main(int argc, char** argv){
  int c = 0, opt = 0;
  float numf;
  string user = "", password = "", textIn = "", num = "", yesno;
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
        textIn = optarg;
      break;
      case 'v':
        num_vect = split_num(optarg,";");
      break;
      case 'n':
        num = optarg;
      break;
    }
  }


  cout << "Bienvenido " << user << ", elige una de las siguientes opciones:\n"<< endl;

  while (check == false){
    opt = stoi(opt_menu());
    switch(opt){
      case 1:
        cout << "Opcion 1" << endl;
        if(check_pali(textIn)){
          cout << "'" << textIn <<"' es palindrome" << endl;
        }else{
          cout << "'" << textIn <<"' no es palindrome" << endl;
        }
      break;
      case 2:
        cout << "Opcion 2" << endl;
        cout << "'" << textIn << "' tiene " << count_symbols(textIn,VOCALS) << " vocales" << endl;
      break;
      case 3:
        cout << "Opcion 3" << endl;
        cout << "'" << textIn << "' tiene " << count_symbols(textIn,LETTERS) << " letras" << endl;
      break;
      case 4:
        cout << "Opcion 4" << endl;
        cout << "Vector: ";
        for (int i : num_vect){
          cout << i << " ";
        }
        cout << endl;
        cout << "La sumatoria es: " << summation(num_vect) << endl;
        cout << "El promedio es: " << average(num_vect) << endl;
      break;
      case 5:
        cout << "Opcion 5" << endl;
        if(!check_num(num)){
          cout << num << " no es un numero, no se puede calcular" << endl;
        }
        else {
          numf = calc_func(stoi(num));
          cout << "El resultado es: " << numf << endl;
        }
      break;
      default:
        cout << "Se ingreso opcion equivocada, ingrese de nuevo\n" << endl;
      break;
    }
    cout << "\n¿Desea realizar otra operacion? (Y/N): ";
    cin >> yesno;
    yesno = check_yesno(yesno);
    if (yesno == "n" || yesno == "N") {
      cout << "\nCerrando programa...\n" << endl;
      check = true;
    }else{
      cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    }
  }
  return 0;
}
