#include <unistd.h>
#include <sys/wait.h>


#include "thread_operation.h"
#include "user_operation.h"
#include "file_operation.h"
#include "func_math.h"
#include "func_string.h"
#include "env_setter.h"
#include "common.h"

using namespace std;



//Realiza la accion para la opcion elegida y repite el menu hasta salir
void execute(bool check, string textIn, string numVect, string num,string user, bool admin, string userFilePath){

  int opt;
  float numf;
  bool checkIndex = false; //Flag temporal para crear indice invertido
  vector<int>numVectSplit = {};
  
  

  while (check == true){
    opt = stoi(opt_menu(user,admin,checkIndex));
    if(!admin && (opt == 98 || opt == 99 || opt == 100)) cout << "Se ingreso opcion equivocada, ingrese de nuevo\n" << endl;
    else if(opt == 8 && !checkIndex) cout << "Se ingreso opcion equivocada, ingrese de nuevo\n" << endl;
    else{
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
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
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
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
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
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
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
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
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
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;

        //6.Contar palabras de un archivo
        case 6:{
          print_separation();
          cout<<"Programa contador de palabras"<<endl;
          pid_t pid = fork(); //Crear un proceso hijo
          if (pid == 0) { 
            execl("./contar_palabras", "contar_palabras", NULL);
            exit(0); 
          }
          
          else if (pid > 0) {
            wait(NULL); 
          } 
          
          else {
            cout<<"Error al crear el proceso"<<endl;
          }                
            break;
        }

        //7.Conteo Paralelo con threads
        case 7:{
          print_separation();

          

          cout << "Opcion 7\n" << endl;
          string archivoStopWords = get_enviroment_variable("STOP_WORDS");
          cargarStopWords(archivoStopWords);
          open_threads();
          crearMapaArchivo();  // Crear el mapa de archivos
          
          checkIndex = true; //Flag temporal para crear indice invertido

          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;
        }
        
        case 8:{
          print_separation();

          cout << "Opcion 8\n" << endl;
          crearIndiceInvertido();

          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;
        }
        //98.Lista de usuarios
        case 98:
          print_separation();
          cout << "Opcion 98\n" << endl; 

          print_user_list(get_user_list(userFilePath));
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;
        //99.Ingresar usuario
        case 99:
          print_separation();
          cout << "Opcion 99\n" << endl; 
          add_user(userFilePath);
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;
        //100.Eliminar Usuario
        case 100:
          print_separation();
          cout << "Opcion 100\n" << endl;
          erase_user(userFilePath);
          cout << "\nPresione ENTER para continuar...";
          getc(stdin);
          getc(stdin);
        break;
        //0.Salir
        case 0:
          check = false;
        break;
        //No se ingreso una opcion disponible
        default:
          cout << "Se ingreso opcion equivocada, ingrese de nuevo\n" << endl;
        break;
      }

    }
    
  }
}

int main(int argc, char** argv){
  int c = 0;
  string userIn = "", passwordIn = "", textIn = "", num = "" , numVect= "";
  bool check ;
  bool admin = false;

  set_env_from_file();
  string userFilePath = get_enviroment_variable("USER_FILE_PATH");

//Toma los valores de entrada
  while((c=getopt(argc,argv,"u:p:t:v:n:"))!=-1){
    switch(c){
      case 'u':
        userIn = optarg;
      break;
      case 'p':
        passwordIn = optarg;
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

  
  
  //cout << string(userFilePath) << endl;
  check = check_login(userIn,passwordIn,&admin,userFilePath);
  execute(check,textIn,numVect,num,userIn,admin,userFilePath);
  
  
  //string userFilePath = USER_FILE_PATH;
  //check = check_login(userIn,passwordIn,&admin,userFilePath);
  //execute(check,textIn,numVect,num,userIn,admin,userFilePath);
  
  cout << "Cerrando programa...\n" << endl;
  return 0;
}
