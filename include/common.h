#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <vector>
#include <tuple>
#include <string.h>
#include <fstream>
#include <unistd.h>

using namespace std;

static string DIGITS = "0123456789,";
static string VOCALS = "aeiouAEIOU";
static string LETTERS = "abcdefghijklmnñopqrstuvwxyzABCDEFGHYJKLMNÑOPQRSTUVWXYZ";

static string USERFILEPATH = "./data/users.txt";

static string TEMP_USER = "usuario";
static string TEMP_PASSWORD = "contraseña";
static bool ADMIN = true;

#endif