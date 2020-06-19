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
#include "func.h"
using namespace std;

int char_to_int (char* cstr)
{
    int N=0;
    int i=0;
    while (cstr[i] >= 0x30 && cstr[i] <= 0x39)
    {
        N=N+(cstr[i] & 0x0F);
        N=N*10;
        i++;
    }
    N=N/10;
    return N;
}

int road_size(int _N, int _M, int* _num_b, int* _num_e, int* _r_len)
{
    int matr[_N][_N];
    for (int i=0; i<_N; i++)
        for (int j=0; j<_N; j++)
            matr[i][j]=0;
    for (int i=0; i<_M; i++)
        {
            if (matr[_num_b[i]][_num_e[i]]==0)
            {
                matr[_num_b[i]][_num_e[i]]=_r_len[i];
            }
            else
            {
                cout<<"road size error!"<<endl;
                return 0;
            }

            if (_r_len[i]==0)
            {
                cout<<"road size error!"<<endl;
                return 0;
            }

        }
    return 1;
}

void chr_div(char** line, char** first, char** second, char** third)
{
        const char *sep=" ";
        char*ptr=0;
        ptr=strtok(*line, sep);
        *first=new char(strlen(ptr));
        strcpy(*first, ptr);
        ptr=strtok(0, sep);
        *second=new char(strlen(ptr));
        strcpy(*second, ptr);
        ptr=strtok(0, sep);
        *third=new char(strlen(ptr));
        strcpy(*third, ptr);

}

int min_ch2 (int a, int b)
{
    if (a<=b)
        return a;
    return b;
}
