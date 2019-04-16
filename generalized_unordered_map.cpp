#include <iostream>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <ctime>
#include <map>
#include <list>
#include <string>
#include <unordered_map>

#define MatrixSize 256
#define RodSize 20


using namespace std;

struct t_result
{
    float min_time;
    float max_time;
    float avg_time;
    float cur_time;
    int files_count;
} result;

struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const pair<T1, T2>& p) const
    {
        auto hash1 = hash<T1>{}(p.first);
        auto hash2 = hash<T2>{}(p.second);
        return hash1 ^ hash2;
    }
};

int a[256][256];
int main()
{

    result.min_time = 1.7e+308;
    result.max_time = 0;
    result.avg_time = 0;
    result.files_count = 0;
    /// файл вывода
    ofstream fout("output.txt");
    /// сканируем файлы в директории
    HANDLE hFind;
    WIN32_FIND_DATA data;

    hFind = FindFirstFile("\Grid*.txt", &data);
    if (hFind != INVALID_HANDLE_VALUE) {
    do {
    result.files_count++;

    ifstream fin(data.cFileName);


    /// считывание файла
    for (int i=0; i<MatrixSize; ++i)
        for (int j=0; j<MatrixSize; ++j)
           {
                fin >> a[i][j];
                a[i][j]--;

           }
    result.cur_time = clock();
    unordered_map<pair<int,int>, int, hash_pair> mp;

    ///==========================================
    /// Алгоритм

    pair<int,int> tmp;

    for (int i=0; i<MatrixSize; ++i)
        for (int j=0; j<MatrixSize; ++j)
        {
            tmp.first = 0;
            tmp.second = 0;
            for (int ii=0; ii<RodSize; ++ii)
                for (int jj=0; jj<RodSize; ++jj)
                {
                    if (a[(i+ii)%MatrixSize][(j+jj)%MatrixSize] == 0)
                        ++tmp.first;
                    if (a[(i+ii)%MatrixSize][(j+jj)%MatrixSize] == 1)
                        ++tmp.second;

                }
            // cout << "+" << tmp << endl;
         //   if (mp.find(tmp) != mp.end())
          //      mp[tmp]++;
         //   else
         //       mp[tmp] = 1;
             mp[tmp]++;
            //cout << "-" << endl;
        }


    ///=========================================
    /// Конец алгоритма
    //cout << "*" << endl;
        //cout << "%" << endl;
    result.cur_time = clock() - result.cur_time;
    result.avg_time += result.cur_time;
    result.min_time = min(result.min_time, result.cur_time);
    result.max_time = max(result.max_time, result.cur_time);
    fin.close();
    mp.clear();

    } while (FindNextFile(hFind, &data));
    FindClose(hFind);
    fout.close();
    }
    result.avg_time/=result.files_count;
    cout << "Files count: " << result.files_count << endl;
    cout << "Min time: " << result.min_time << endl;
    cout << "Max time: " << result.max_time << endl;
    cout << "Avg time: " << result.avg_time << endl;
    return 0;
}
