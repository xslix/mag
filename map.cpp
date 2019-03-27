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

#define MatrixSize 256
#define RodSize 4


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

           }
    result.cur_time = clock();


    ///==========================================
    /// Алгоритм
    map <list <list <int> > ,int> block;
    list <list <int> > lst;
    list <int> tmp;
    for (int i=0; i<RodSize; ++i)
    {
        for (int j=0; j<RodSize; ++j)
        {
            tmp.push_back(a[i][j]);
        }
        lst.push_back(tmp);
    }
    for (int j=0; j<MatrixSize; ++j)
    {

        for (int i=0; i<MatrixSize; ++i)
        {
            block.insert(pair <list <list <int> > ,int>(lst,1));
            tmp.clear();
            for (int jj=0; jj<RodSize; ++jj)
                tmp.push_back(a[(i+RodSize)%MatrixSize][(j+jj)%MatrixSize]);
            lst.push_back(tmp);
            lst.pop_front();

        }
        int ii = 0;
        for (auto t : lst)
            {
                t.pop_front();
                t.push_back(a[ii%MatrixSize][(j+RodSize)&MatrixSize]);
                ++ii;
            }

    }
    lst.clear();
    block.clear();

    ///=========================================
    /// Конец алгоритма


    result.cur_time = clock() - result.cur_time;
    result.avg_time += result.cur_time;
    result.min_time = min(result.min_time, result.cur_time);
    result.max_time = max(result.max_time, result.cur_time);
    fin.close();

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
