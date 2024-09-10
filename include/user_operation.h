#ifndef USER_OPERATION_H
#define USER_OPERATION_H

#include "common.h"
#include "func_string.h"
#include "file_operation.h"

bool check_login(string user, string password, bool* admin);
vector<tuple<string,string,string>> get_users(string fileName);

#endif