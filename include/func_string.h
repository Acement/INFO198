#ifndef FUNC_STRING_H
#define FUNC_STRING_H

#include "common.h"

using namespace std;

bool check_login(string user, string password);

bool check_num(string num);
string opt_menu();
bool check_empty(string s);
vector<int> split_num(string s, string separate);
string text_normalization(string s);
int count_symbols(string s, string filter);
bool check_pali(string s);

void print_separation();


#endif