#include "func_string.h"
#include "common.h"

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
  cout << "5.Calcular f(x)=5x*x+1/x\n" << endl;
  cout << "Ingrese opcion: ";
  cin >> opt;
  if(opt.empty() || opt.find_first_not_of(DIGITS) != string::npos){
    cout << "No es un numero, Ingrese una de las opciones\n" << endl;
    return opt_menu();
  }
  return opt;
}

//Chekea si se ingreso de forma correcta Y/N o y/n
string check_yesno(string s){
  while(s != "Y" && s != "y" && s != "N" && s != "n" ){
    cout << "Error! Ingrese (Y/N) o (y/n): ";
    cin >> s;
  }
  return s;
}

//Toma el string de numeros separado por ";" y devuelve un vector que contiene los numeros separados
vector<int> split_num(string s, string separator){
    vector<int> values = {};
    size_t pos = 0; //size_t = maximo tamaño posible de cualquier objeto
    string temp;
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
  for(int i = 0; i < s.size(); i++ ){
    if(s[i] != s[(s.size()-1)-i]){
      return false;
    }
  }
  return true;
}