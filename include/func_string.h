#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

bool check_num(string num);
string opt_menu();
string check_yesno(string s);
vector<int> split_num(string s, string separate);
int count_symbols(string s, string filter);
bool check_pali(string s);


#endif