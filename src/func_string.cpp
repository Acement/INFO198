#include "func_string.h"


string opt_menu(){
  string opt;
  cout << "1.Detectar Palindrome" << endl;
  cout << "2.Contar Vocales" << endl;
  cout << "3.Contar letras en un texto" << endl;
  cout << "4.Promedio y sumatoria de un vector" << endl;
  cout << "5.Calcular f(x)=5x*x+1/x\n" << endl;
  cout << "Ingrese opcion: ";
  cin >> opt;
  return opt;
}

//Toma el string de numeros separado por ";" y devuelve un vector que contiene los numeros separados
vector<int> split_num(string s, string separator){
    vector<int> values = {};
    size_t pos = 0; //size_t = maximo tamaño posible de cualquier objeto
    string temp;
    while(pos = s.find(separator) != string::npos){//npos = valor que representa el ultimo numero de size_t, find devuelve la posicion donde primero encuentra una coincidencia
        temp = s.substr(0,pos);
        values.push_back(stoi(temp)); 
        s.erase(0, pos + separator.length());
    }
    values.push_back(stoi(s));

    return values;
}