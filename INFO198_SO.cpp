#include <unistd.h>

#include "func_math.h"
#include "func_string.h"
#include "common.h"

using namespace std;

//Realiza la accion para la opcion elegida y repite el menu hasta salir
void execute(bool check, string textIn, string numVect, string num){

  int opt;
  float numf;
  vector<int>numVectSplit = {};

  while (check == true){
    opt = stoi(opt_menu());
    switch(opt){
      //Detectar Palindrome
      case 1:
        print_separation();
        if(check_empty(textIn)){
          cout << "Parametro invalido, no se pudo realizar operacion" << endl;
        }
        else{
            cout << "Opcion 1\n" << endl;
          if(check_pali(textIn)){
            cout << "'" << textIn <<"' es palindrome" << endl;
          }else{
            cout << "'" << textIn <<"' no es palindrome" << endl;
          }
        }
        print_separation();
      break;
      //2.Contar Vocales
      case 2:
        print_separation();
        if(check_empty(textIn)){
          cout << "Parametro invalido, no se pudo realizar operacion" << endl;
        }
        else{
          cout << "Opcion 2\n" << endl;
          cout << "'" << textIn << "' tiene " << count_symbols(textIn,VOCALS) << " vocales" << endl;
        }
        
        print_separation();
      break;
      //3.Contar letras en un texto
      case 3:
          print_separation();
        if(check_empty(textIn)){
          cout << "Parametro invalido, no se pudo realizar operacion" << endl;
        }
        else{
          cout << "Opcion 3\n" << endl;
          cout << "'" << textIn << "' tiene " << count_symbols(textIn,LETTERS) << " letras" << endl;
        }
        print_separation();
      break;
      //4.Promedio y sumatoria de un vector
      case 4:
        print_separation();
        if(check_empty(numVect)){
          cout << "Parametro invalido, no se pudo realizar operacion" << endl;
        }
        else{
          numVectSplit = split_num(numVect,";");
          cout << "Opcion 4\n" << endl;
          cout << "Vector: ";
          for (int i : numVectSplit){
            cout << i << " ";
          }
          cout << endl;
          cout << "La sumatoria es: " << summation(numVectSplit) << endl;
          cout << "El promedio es: " << average(numVectSplit) << endl;
        }
        print_separation();
      break;
      //5.Calcular f(x)=5x*x+1/x
      case 5:
        print_separation();
        if(check_empty(num)){
          cout << "Parametro invalido, no se pudo realizar operacion" << endl;
        }
        else{
          cout << "Opcion 5\n" << endl;
          if(!check_num(num)){
            cout << num << " no es un numero, no se puede calcular" << endl;
          }
          else {
            numf = calc_func(stoi(num));
            cout << "El resultado es: " << numf << endl;
          }
        }
        
        print_separation();
      break;
      //6.Salir
      case 6:
        check = false;
      break;
      //No se ingreso una opcion disponible
      default:
        cout << "Se ingreso opcion equivocada, ingrese de nuevo\n" << endl;
      break;
    }
  }
}

int main(int argc, char** argv){
  int c = 0;
  float numf;
  string user = "", password = "", textIn = "", num = "" , numVect= "";
  bool check;

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
        numVect = optarg;
      break;
      case 'n':
        num = optarg;
      break;
    }
  }
  
  check = check_login(user,password);
  execute(check,textIn,numVect,num);

  cout << "Cerrando programa...\n" << endl;
  return 0;
}
