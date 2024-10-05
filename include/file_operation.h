#ifndef FILE_OPERATION_H
#define FILE_OPERATION_H

#include "common.h"

void thread_operation();
vector<string> read_file(string fileName);
void add_line_to_file(string fileName, string line);
void add_user_to_file(string fileName, string line);
void erase_lines(string fileName, vector<string> newLines);

#endif