#include "func_string.h"
#include "common.h"

//Checkea si las credenciales ingresadas son correctas
bool check_login(string user, string password){
  if (user.size() < 3 || user != TEMP_USER || count_symbols(user,LETTERS) < user.size()){
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else if (password.size() < 8 || password != TEMP_PASSWORD || (count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < password.size() ||(count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < 6){
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else{
    cout << "Bienvenido " << user << ", elija una de las siguientes opciones\n" << endl;
    return true;
  } 
  
}

//Chekea si el valor ingresado es un numero
bool check_num(string num){
  if(num.empty() || num.find_first_not_of(DIGITS) != string::npos){
    return false;
  }
  return true;
}

//Menu del programa
string opt_menu(){
  string opt;
  cout << "1.Detectar Palindrome" << endl;
  cout << "2.Contar Vocales" << endl;
  cout << "3.Contar letras en un texto" << endl;
  cout << "4.Promedio y sumatoria de un vector" << endl;
  cout << "5.Calcular f(x)=5x*x+1/x" << endl;
  cout << "6.Salir\n" << endl;
  cout << "Ingrese opcion: ";
  cin >> opt;
  if(opt.empty() || opt.find_first_not_of(DIGITS) != string::npos){
    cout << "No es un numero, Ingrese una de las opciones\n" << endl;
    return opt_menu();
  }
  return opt;
}

bool check_empty(string s){
  if(s.size() == 0) return true;
  return false;
}

//Toma el string de numeros separado por ";" y devuelve un vector que contiene los numeros separados
vector<int> split_num(string s, string separator){
    vector<int> values = {};
    size_t pos = 0; //size_t = maximo tamaño posible de cualquier objeto
    string temp;
    if(s[s.size()-1] == separator[0]) s.erase(s.size() - 1);
    while((pos = s.find(separator)) != string::npos){//npos = valor que representa el ultimo numero de size_t, find devuelve la posicion donde primero encuentra una coincidencia
        temp = s.substr(0,pos);
        values.push_back(stoi(temp));
        s.erase(0, pos + separator.length());
    }
    values.push_back(stoi(s));

    return values;
}

int count_symbols(string s, string filter){
  int count = 0;
  for(int i = 0; i < s.size(); i++){
    if (filter.find(s[i]) != string::npos) count++;
  }
  return count;
}

//Checkea si el string ingresado es palidrome
bool check_pali(string s){
  s = text_normalization(s);
  for(int i = 0; i < s.size()/2; i++ ){
    if(s[i] != s[(s.size()-1)-i]){
      return false;
    }
  }
  return true;
}

//Cambia las mayusculas a minusculas y elimina los espacios en blanco
string text_normalization(string s){
  for (int i = 0; i < s.size(); i++){
    if(isupper(s[i])){
      s[i] = tolower(s[i]);
    }else if(s[i] == ' '){
      s.erase(i,1);
      i--;
    }
    
  }
  return s;
}
//Impriem una linea para separar las ejecuciones del sistema
void print_separation(){
  cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
}