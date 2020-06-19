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

int main()
{
//open file
    ifstream fin;
    fin.open("input.txt");
    if (!fin.is_open())
    {
        cout<<"file opening error!"<<endl;
        return 0;
    }

//read number
    string str;
    getline(fin, str);
    char *cstr=new char[str.length()+1];
    strcpy(cstr, str.c_str());
    int N=char_to_int(cstr);

//read towns
    string town[N];
    for (int i=0; i<N; i++)
    {
        getline(fin, town[i]);
    }

//read number
    getline(fin, str);
    cstr=new char[str.length()+1];
    strcpy(cstr, str.c_str());
    int M=char_to_int(cstr);

    if (M==0)
    {
        cout<<"string number error!"<<endl;
        return 0;
    }

//read roads
    string road[M];
    for (int i=0; i<M; i++)
    {
        if (fin.eof()==false)
        {
            getline(fin, road[i]);
        }
        else
        {
            cout<<"string number error!"<<endl;
            return 0;
        }
    }

//format
    char *town_char[N];
    char *town_name[N];
    char *town_x[N];
    char *town_y[N];
    for (int i=0; i<N; i++)
    {
        town_char[i]=new char[town[i].length()+1];
        strcpy(town_char[i], town[i].c_str());
    }

    for (int i=0; i<N; i++)
    {
        chr_div(&town_char[i], &town_name[i], &town_x[i], &town_y[i]);
    }

    char *road_char[M];
    char *road_begin[M];
    char *road_end[M];
    char *road_length[M];
    for (int i=0; i<M; i++)
    {
        road_char[i]=new char[road[i].length()+1];
        strcpy(road_char[i], road[i].c_str());
    }

    for (int i=0; i<M; i++)
    {
        chr_div(&road_char[i], &road_begin[i], &road_end[i], &road_length[i]);
    }
    int x_pos[N];
    int y_pos[N];
    int r_len[M];
    int num_b[M];
    int num_e[M];

    for (int i=0; i<N; i++)
    {
        strcpy(cstr, town_x[i]);
        x_pos[i]=char_to_int(cstr);
        strcpy(cstr, town_y[i]);
        y_pos[i]=char_to_int(cstr);
    }

    for (int i=0; i<M; i++)
    {
        strcpy(cstr, road_length[i]);
        r_len[i]=char_to_int(cstr);
        strcpy(cstr, road_begin[i]);
        num_b[i]=char_to_int(cstr);
        strcpy(cstr, road_end[i]);
        num_e[i]=char_to_int(cstr);
    }

//size control
    for (int i=0; i<M; i++)
    {
        int x=x_pos[num_e[i]]-x_pos[num_b[i]];
        int y=y_pos[num_e[i]]-y_pos[num_b[i]];
        if (r_len[i]<(sqrt(x*x+y*y)))
        {
            cout<<"road size error!"<<endl;
            return 0;
        }
    }

    for (int i=0; i<M; i++)
        if (num_b[i]==num_e[i])
            {
                r_len[i]=0;
            }

    int _N=N;
    int _M=M;
    int _num_b[M];
    int _num_e[M];
    int _r_len[M];

    for (int i=0; i<M; i++)
    {
        _num_b[i]=num_b[i];
        _num_e[i]=num_e[i];
        _r_len[i]=r_len[i];
    }

    if (road_size(_N, _M, _num_b, _num_e, _r_len)==0)
        return 0;

    int r_len_m=0;
     for (int i=0; i<M; i++)
        {
            if (r_len_m<r_len[i])
                r_len_m=r_len[i];
        }

//map
    int xmax=x_pos[0];
    int xmin=x_pos[0];
    int ymax=y_pos[0];
    int ymin=y_pos[0];

    for (int i=1; i<N; i++) //поиск минимальных и максимальных х и у
    {
        if(x_pos[i]>xmax)
            xmax=x_pos[i];

        if(x_pos[i]<xmin)
            xmin=x_pos[i];

        if(y_pos[i]>ymax)
            ymax=y_pos[i];

        if(y_pos[i]<ymin)
            ymin=y_pos[i];
    }

    int x_pos_an[N];
    int y_pos_an[N];

    for (int i=0; i<N; i++) //поиск х и у относительно карты
    {
        x_pos_an[i]=x_pos[i]-xmin+1;
        y_pos_an[i]=y_pos[i]-ymin+1;
    }

    int xmax_an=xmax-xmin+1;
    int ymax_an=ymax-ymin+1;

    int x_ch[M];
    int y_ch[M];
    int x_pos_b[M];
    int y_pos_b[M];
    int x_pos_e[M];
    int y_pos_e[M];
    for (int i=0; i<M; i++)//смещени€ по х и у
    {
        x_pos_b[i]=x_pos_an[num_b[i]];
        y_pos_b[i]=y_pos_an[num_b[i]];
        x_pos_e[i]=x_pos_an[num_e[i]];
        y_pos_e[i]=y_pos_an[num_e[i]];
        x_ch[i]=x_pos_e[i]-x_pos_b[i];
        y_ch[i]=y_pos_e[i]-y_pos_b[i];
    }

    int matr_r[xmax_an+2][ymax_an+2];
    for (int i=0; i<xmax_an+2; i++)
        for (int j=0; j<ymax_an+2; j++)
            matr_r[i][j]=0;

    for (int i=0; i<M; i++)
    {
        if(x_ch[i]>=0)
        for (int j=x_pos_b[i]+1; j<x_pos_b[i]+x_ch[i]+1; j++)
            matr_r[j][y_pos_b[i]]++;
        if(x_ch[i]<0)
            for (int j=x_pos_b[i]+x_ch[i]; j<x_pos_b[i]; j++)
            matr_r[j][y_pos_b[i]]++;
        if(y_ch[i]>=0)
        for (int j=y_pos_b[i]+1; j<y_pos_b[i]+y_ch[i]; j++)
            matr_r[x_pos_b[i]+x_ch[i]][j]+=10;
        if(y_ch[i]<0)
        for (int j=y_pos_b[i]+y_ch[i]+1; j<y_pos_b[i]; j++)
            matr_r[x_pos_b[i]+x_ch[i]][j]+=10;
    }

    for (int i=0; i<xmax_an+2; i++)
        cout<<"#";
    cout<<endl;
    for (int i=1; i<ymax_an+1; i++)
    {
        cout<<"#";
        for (int j=1; j<xmax-1; j++)
        {
            int point_an=-1;
            for (int k=0; k<N; k++)
            {
                if(x_pos_an[k]==j && y_pos_an[k]==i)
                {
                    point_an=k;
                }
            }
            if (matr_r[j][i]==0)
            {
                if (point_an==-1)
                    cout<<" ";
                else
                    cout<<point_an;
            }
            else if(matr_r[j][i]<10 && matr_r[j][i]>0)
                {
                    for (int l=0; l<matr_r[j][i]; l++)
                        cout<<"/";
                }
            else if(matr_r[j][i]>10 && matr_r[j][i]<20)
                {
                    matr_r[j][i]-=10;
                    matr_r[j][i+1]++;
                    j--;
                }
            else if(matr_r[j][i]>20)
                {
                    matr_r[j][i]-=10;
                    matr_r[j][i+1]+=10;
                    j--;
                }
        }
        cout<<"#"<<endl;
    }
    for (int i=0; i<xmax_an+2; i++)
        cout<<"#";
    cout<<endl;


//way
    cout<<"Input begin number:"<<endl;
    int st;
    cin>>st;
    cout<<"Input finish number:"<<endl;
    int fn;
    cin>>fn;

    int st_fn_cor=-1;
    if(st<N && fn<N)
        st_fn_cor++;

    if (st_fn_cor==-1)
    {
        cout<<"Number error!"<<endl;
        return 0;
    }

    for (int i=0; i<M; i++)
    {
        if (num_b[i]==st)
        {
        st_fn_cor++;
        break;
        }
    }

    for (int i=0; i<M; i++)
        if (num_e[i]==fn)
        {
        st_fn_cor++;
        break;
        }

    if(st_fn_cor!=2)
    {
        cout<<"No way found!"<<endl;
        return 0;
    }

    int dij[N][N]; // матрица св€зей
    int d[N]; // минимальное рассто€ние
    int v[N]; // посещенные вершины
    int temp, minindex, min;
    int begin_index = st;
    // »нициализаци€ матрицы св€зей
    for (int i=0; i<N; i++)
        for (int j=0; j<N; j++)
            dij[i][j]=0;

    for (int i = 0; i<N; i++)
    {
        for (int j = 0; j<N; j++)
        {
            for (int k=0; k<M; k++)
            if ((num_b[k]==i) && (num_e[k]==j))
            dij[i][j] = r_len[k];
        }
    }
  // ¬ывод матрицы св€зей
  for (int i = 0; i<N; i++)
  {
    for (int j = 0; j<N; j++)
      cout<<dij[i][j]<<"\t";
    cout<<endl;
  }
  //»нициализаци€ вершин и рассто€ний
  for (int i = 0; i<N; i++)
  {
    d[i] = 10000;
    v[i] = 1;
  }
  d[begin_index] = 0;
  // Ўаг алгоритма
  do {
    minindex = 10000;
    min = 10000;
    for (int i = 0; i<N; i++)
    { // ≈сли вершину ещЄ не обошли и вес меньше min
      if ((v[i] == 1) && (d[i]<min))
      { // ѕереприсваиваем значени€
        min = d[i];
        minindex = i;
      }
    }
    // ƒобавл€ем найденный минимальный вес
    // к текущему весу вершины
    // и сравниваем с текущим минимальным весом вершины
    if (minindex != 10000)
    {
      for (int i = 0; i<N; i++)
      {
        if (dij[minindex][i] > 0)
        {
          temp = min + dij[minindex][i];
          if (temp < d[i])
          {
            d[i] = temp;
          }
        }
      }
      v[minindex] = 0;
    }
  } while (minindex < 10000);

  // ¬ывод кратчайших рассто€ний до вершин
    cout<<"size:"<<endl;
    for (int i = 0; i<N; i++)
        cout<<d[i]<<"\t";
    cout<<endl;
    getch();
    system("cls");
//map
    int ps=0;
    while (v[ps]!=fn)
    {
        ps++;
    }
    ps++;
    int _v[ps];
    for (int i=0; i<ps; i++)
        _v[i]=v[i];

    int x_ch_dn[ps-1];
    int y_ch_dn[ps-1];
    int x_pos_b_dn[ps-1];
    int y_pos_b_dn[ps-1];
    int x_pos_e_dn[ps-1];
    int y_pos_e_dn[ps-1];
    for (int i=0; i<ps-1; i++)//смещени€ по х и у
    {
        x_pos_b_dn[i]=x_pos_an[_v[i]];
        y_pos_b_dn[i]=y_pos_an[_v[i]];
        x_pos_e_dn[i]=x_pos_an[_v[i+1]];
        y_pos_e_dn[i]=y_pos_an[_v[i+1]];
        x_ch_dn[i]=x_pos_e_dn[i]-x_pos_b_dn[i];
        y_ch_dn[i]=y_pos_e_dn[i]-y_pos_b_dn[i];
    }

    for (int i=0; i<xmax_an+2; i++)
        for (int j=0; j<ymax_an+2; j++)
            matr_r[i][j]=0;

    for (int i=0; i<ps-1; i++)
    {
        if(x_ch_dn[i]>=0)
        for (int j=x_pos_b_dn[i]+1; j<x_pos_b_dn[i]+x_ch_dn[i]+1; j++)
            matr_r[j][y_pos_b_dn[i]]++;
        if(x_ch_dn[i]<0)
            for (int j=x_pos_b_dn[i]+x_ch_dn[i]; j<x_pos_b_dn[i]; j++)
            matr_r[j][y_pos_b_dn[i]]++;
        if(y_ch_dn[i]>=0)
        for (int j=y_pos_b_dn[i]+1; j<y_pos_b_dn[i]+y_ch_dn[i]; j++)
            matr_r[x_pos_b_dn[i]+x_ch_dn[i]][j]+=10;
        if(y_ch_dn[i]<0)
        for (int j=y_pos_b_dn[i]+y_ch_dn[i]+1; j<y_pos_b_dn[i]; j++)
            matr_r[x_pos_b_dn[i]+x_ch_dn[i]][j]+=10;
    }

    for (int i=0; i<xmax_an+2; i++)
        cout<<"#";
    cout<<endl;
    for (int i=1; i<ymax_an+1; i++)
    {
        cout<<"#";
        for (int j=1; j<xmax-1; j++)
        {
            int point_an=-1;
            for (int k=0; k<N; k++)
            {
                if(x_pos_an[k]==j && y_pos_an[k]==i)
                {
                    point_an=k;
                }
            }
            if (matr_r[j][i]==0)
            {
                if (point_an==-1)
                    cout<<" ";
                else
                    cout<<point_an;
            }
            else if(matr_r[j][i]<10 && matr_r[j][i]>0)
                {
                    for (int l=0; l<matr_r[j][i]; l++)
                        cout<<"X";
                }
            else if(matr_r[j][i]>10 && matr_r[j][i]<20)
                {
                    matr_r[j][i]-=10;
                    matr_r[j][i+1]++;
                    j--;
                }
            else if(matr_r[j][i]>20)
                {
                    matr_r[j][i]-=10;
                    matr_r[j][i+1]+=10;
                    j--;
                }
        }
        cout<<"#"<<endl;
    }
    for (int i=0; i<xmax_an+2; i++)
        cout<<"#";
    cout<<endl;

    /*
    char *town_name[]
    int x_pos[]
    int y_pos[]

    int num_b[]
    int num_e[]
    int r_len[]
    */
//ask for points
//find the way
//cout map
//show the way
    fin.close();
    return 0;
}
