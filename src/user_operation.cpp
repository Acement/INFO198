#include "user_operation.h"



//Checkea si las credenciales ingresadas son correctas
bool check_login(string user, string password, bool* admin){
  vector<tuple<string,string,string>> userVector = {};
  userVector = get_users(USERFILEPATH);
  for(tuple<string,string,string> i : userVector){
    cout <<"Usuario: " << get<0>(i) << endl;
    cout <<"Contraseña: " << get<1>(i) << endl;
    cout <<"Rol: ";
    if(get<2>(i) == "admin" ){
      *admin = true;
      cout << "Admin" << endl;
    }
    else{
      cout << get<2>(i) << endl;
    }
  }
  if (user.size() < 3 || user != TEMP_USER || count_symbols(user,LETTERS) < user.size()){
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;

    return false;
  }else if (password.size() < 8 || password != TEMP_PASSWORD || (count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < password.size() ||(count_symbols(password,DIGITS) + count_symbols(password,LETTERS)) < 6){
    cout << "ERROR!, Usuario o contraseña incorrectos\n" << endl;
    return false;
  }else{
    *admin = true;
    return true;
  } 
  
}

vector<tuple<string,string,string>> get_users(string fileName){
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
