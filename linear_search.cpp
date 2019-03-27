#include <iostream>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <ctime>

#define MatrixSize 256
#define RodSize 7


using namespace std;

struct t_result
{
    float min_time;
    float max_time;
    float avg_time;
    float cur_time;
    int files_count;

} result;



int a[256][256];
int main()
{

   // result.min_time = 1.7e+308;
   // result.max_time = 0;
   // result.avg_time = 0;
   // result.files_count = 0;
    /// файл вывода
    ofstream fout("output.txt");
    ifstream fin("input.txt");
    /// сканируем файлы в директории
    //HANDLE hFind;
   // WIN32_FIND_DATA data;

    //hFind = FindFirstFile("\Grid*.txt", &data);
   // if (hFind != INVALID_HANDLE_VALUE) {
   // do {
  //  result.files_count++;
    //ifstream fin(data.cFileName);


    /// считывание файла
    for (int i=0; i<MatrixSize; ++i)
        for (int j=0; j<MatrixSize; ++j)
           {
                fin >> a[i][j];

           }
    //result.cur_time = clock();


    ///==========================================
    /// Алгоритм
    vector < vector <int> > block;
    vector < int > amount;
    vector <int> tmp;
    int t;
    for (int i=0; i<MatrixSize; ++i)
        for (int j=0; j<MatrixSize; ++j)
        {
            tmp.clear();
            for (int g=0; g<RodSize; ++g)
                for (int k=0; k<RodSize; ++k)
            {
                tmp.push_back(a[(i+g)%MatrixSize][(j+k)%MatrixSize]);
            }
            t=0;
            while (t<block.size() && tmp!=block[t])
                ++t;
            if (t>=block.size())
            {
                block.push_back(tmp);
                amount.push_back(1);
            }
            else
                ++amount[t];
        }
        for (int i = 0; i< block.size(); ++i)
            fout << amount[i] << endl;
        //fout << block.size() << "\t";
        //double entr = 0;
        //for (int i = 0; i < amount.size(); ++i)
        //{
        //    entr-=1.0*amount[i]/(double)MatrixSize/(double)MatrixSize*log(1.0*amount[i]/(double)MatrixSize/(double)MatrixSize)/log(RodSize);
        //}
        //fout << entr << endl;

        amount.clear();
        block.clear();
    ///=========================================
    /// Конец алгоритма


   // result.cur_time = clock() - result.cur_time;
   // result.avg_time += result.cur_time;
   // result.min_time = min(result.min_time, result.cur_time);
   // result.max_time = max(result.max_time, result.cur_time);
   // fin.close();

   // } while (FindNextFile(hFind, &data));
   // FindClose(hFind);
   // fout.close();
   // }
   // result.avg_time/=result.files_count;
   // cout << "Files count: " << result.files_count << endl;
   // cout << "Min time: " << result.min_time << endl;
    //cout << "Max time: " << result.max_time << endl;
   // cout << "Avg time: " << result.avg_time << endl;
    return 0;
}
