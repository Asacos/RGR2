#ifndef FUNC_H_INCLUDED
#define FUNC_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <math.h>
#include <sstream>
#include <algorithm>
#include <list>
#include <vector>
#include <conio.h>

int char_to_int (char* cstr);
int road_size(int _N, int _M, int* _num_b, int* _num_e, int* _r_len);
void chr_div(char** line, char** first, char** second, char** third);
int min_ch2 (int a, int b);

#endif // FUNC_H_INCLUDED
