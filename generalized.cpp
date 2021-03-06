#include <iostream>
#include <cstdio>
#include <vector>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <ctime>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <sstream>
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

int a[MatrixSize + 1][MatrixSize + 1];
int o[MatrixSize + 1][MatrixSize + 1];
int z[MatrixSize + 1][MatrixSize + 1];
//unordered_map <string, int> window;
unordered_map<pair<int, int>, int, hash_pair> window;


int getSum (int x1, int y1, int x2, int y2, int (&mas)[MatrixSize + 1][MatrixSize + 1])
{
    return mas[x2][y2]+mas[x1-1][y1-1]-mas[x1-1][y2]-mas[x2][y1-1];
}

//template <class T>
//std::string to_string(T t)
//{
//    std::ostringstream oss;
//    oss << t;
//    return oss.str();
//}


int main()
{

    result.min_time = 1.7e+308;
    result.max_time = 0;
    result.avg_time = 0;
    result.files_count = 0;
    /// ���� ������
    ofstream fout("output.txt");
    /// ��������� ����� � ����������
    HANDLE hFind;
    WIN32_FIND_DATA data;

    hFind = FindFirstFile("\Grid*.txt", &data);
    if (hFind != INVALID_HANDLE_VALUE) {
    do {
    result.files_count++;
    ifstream fin(data.cFileName);


    /// ���������� �����
    for (int i = 1; i <= MatrixSize; ++i)
        for (int j = 1; j <= MatrixSize; ++j)
           {
                fin >> a[i][j];
                z[i][j] = 0;
                o[i][j] = 0;
           }
    result.cur_time = clock();


    ///==========================================
    /// ��������
    for (int i = 1; i <= MatrixSize; ++i)
        for (int j = 1; j <= MatrixSize; ++j)
           {

               z[i][j]= z[i-1][j] + z[i][j-1] - z[i-1][j-1] + (a[i][j] == 1);
               o[i][j]= o[i-1][j] + o[i][j-1] - o[i-1][j-1] + (a[i][j] == 2);
           }
    for (int i = 1; i <= MatrixSize; ++i)
        for (int j = 1; j <= MatrixSize; ++j)
        {
            pair<int, int> p = make_pair(0, 0);
            p.first = getSum(i, j, min(MatrixSize, i + RodSize - 1), min(MatrixSize, j + RodSize - 1), z);
            p.second = getSum(i, j, min(MatrixSize, i + RodSize - 1), min(MatrixSize, j + RodSize - 1), o);
            if (i + RodSize - 1 > MatrixSize)
             {
                p.first += getSum( 1, j, (i + RodSize - 1) % MatrixSize, min(MatrixSize, j + RodSize - 1), z);
                p.second += getSum( 1, j, (i + RodSize - 1) % MatrixSize, min(MatrixSize, j + RodSize - 1), o);
             }
            if (j + RodSize - 1 > MatrixSize)
            {
                p.first += getSum( i, 1, min(MatrixSize, i + RodSize - 1), (j + RodSize - 1) % MatrixSize, z);
                p.second += getSum( i, 1, min(MatrixSize, i + RodSize - 1), (j + RodSize - 1) % MatrixSize, o);
            }
            if (i + RodSize - 1 > MatrixSize && j + RodSize - 1 > MatrixSize)
            {
                p.first += getSum( 1, 1, (i + RodSize - 1) % MatrixSize, (j + RodSize - 1) % MatrixSize, z);
                p.second += getSum( 1, 1, (i + RodSize - 1) % MatrixSize, (j + RodSize - 1) % MatrixSize, o);
            }
            //string res = to_string<int>(p.first) + "_" + to_string<int>(p.second);

           // cout << res;
           // if (window.find(p) != window.end())
                window[p]++;
            //else
             //   window[p] = 1;
        }

    ///=========================================
    /// ����� ���������


    result.cur_time = clock() - result.cur_time;
    result.avg_time += result.cur_time;
    result.min_time = min(result.min_time, result.cur_time);
    result.max_time = max(result.max_time, result.cur_time);
    fin.close();

    ///entropy
    fout << window.size() << "\t";
    //double entr = 0;
    //for (auto win : window)

    // //fout << win.first << "\t" << win.second << "\n";
    // entr-= 1.0 * win.second / (double)MatrixSize / (double)MatrixSize *
    //        log(1.0 * win.second / (double)MatrixSize /(double)MatrixSize) / max(1.0,log(RodSize * RodSize * RodSize * RodSize));
    //}
    //fout << entr << endl;

    window.clear();

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
