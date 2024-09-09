#include "login.h"
#include "common.h"
#include "func_string.h"


//Checkea si las credenciales ingresadas son correctas
bool check_login(string user, string password, bool* admin){
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