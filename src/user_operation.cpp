#include "user_operation.h"



//Checkea si las credenciales ingresadas son correctas
bool check_login(string user, string password, bool* admin){
  vector<tuple<string,string,string>> userVector = {};
  if (user.size() < 3 ||  count_symbols(user,LETTERS) < user.size()){ //Checkea si el usuario ingresado tenga 3 o mas simbolos y que sean todos letras
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else if (password.size() < 8 || (count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < password.size() ||(count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < 6){//Chequea que la contraseña tenga 8 o mas simbolos y que no existan caracteres especiales
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else{
    userVector = get_user_login(USERFILEPATH);
    for(tuple<string,string,string> i : userVector){
      if(get<0>(i) == user && get<1>(i) == password){ //Verifica si el usuario y contraseña coinciden y si es admin
        if(get<2>(i) == "admin") *admin = true;
        return true;
      }
      
    }
    cout << "ERROR!, Usuario o contraseña incorrectos exit\n" << endl;//Sale si no encuentra ningun usuario y contraseña que coincida
    return false;
  } 
  
}

//Saca los usuarios y sus respectivos elementos del archivo
vector<tuple<string,string,string>> get_user_login(string fileName){
  vector<tuple<string,string,string>> userVector = {}; 

  vector<string> read = read_file(fileName);
  vector<string> tempUser = {};
  tuple<string,string,string> tempTuple = {};

  
  for(string i : read){
    tempUser = split(i,",");
    tempTuple = {tempUser[0],tempUser[1],tempUser[2]};
    userVector.push_back(tempTuple);
    tempUser = {};
    tempTuple = {};
  }

  return userVector;
}

vector<tuple<string,string>> get_user_list(string fileName){
  vector<tuple<string,string>> userVector = {}; 

  vector<string> read = read_file(fileName);
  vector<string> tempUser = {};
  tuple<string,string> tempTuple = {};

  
  for(string i : read){
    tempUser = split(i,",");
    tempTuple = {tempUser[0],tempUser[2]};
    userVector.push_back(tempTuple);
    tempUser = {};
    tempTuple = {};
  }

  return userVector;
}