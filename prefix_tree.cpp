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
#include <random>
#define MatrixSize 256
#define RodSize 8
#define RN 200



using namespace std;

struct t_result
{
    float min_time;
    float max_time;
    float avg_time;
    float cur_time;
    int files_count;

} result;


struct t_tree_node
{
    int value;
    struct t_tree_node * lst[3];

    t_tree_node()
    {
        lst[0] = NULL;
        lst[1] = NULL;
        lst[2] = NULL;
        value = 0;
    }



};
void del (t_tree_node * node)
{
   if (node == NULL) return;
    for (int i=0; i<3; ++i)
        del(node->lst[i]);
    delete(node);
    return;
}
void prnt (t_tree_node * node)
{
    if (node == NULL) return;
    if (node->lst[0]==NULL && node->lst[1]==NULL && node->lst[2]==NULL)
        cout << node->value << endl;
    else
        for (int i=0; i<3; ++i)
        prnt(node->lst[i]);
    return;
}


int a[256][256];
int main()
{
    struct t_tree_node *block = NULL, *tree = NULL;
    result.min_time = 1.7e+308;
    result.max_time = 0;
    result.avg_time = 0;
    result.files_count = 0;
    /// файл вывода
//    ofstream fout("output.txt");
    /// сканируем файлы в директории
//    HANDLE hFind;
//    WIN32_FIND_DATA data;
//
//    hFind = FindFirstFile("\Grid*.txt", &data);
//    if (hFind != INVALID_HANDLE_VALUE) {
//    do {
//    result.files_count++;
    ifstream fin("Grid_0.txt");
//    ofstream fout("output.txt");
    freopen("output.txt","w",stdout);


    /// считывание файла
    for (int i=0; i<MatrixSize; ++i)
        for (int j=0; j<MatrixSize; ++j)
           {
                fin >> a[i][j];
                a[i][j]--;

           }
    result.cur_time = clock();
    srand(unsigned(time(0)));
    int resAns = 0;
    for (int rk = 0; rk < RN; ++rk) {
    ///==========================================
    /// Алгоритм
    //cout << "s" << endl;
    del(block);
    block = new(struct t_tree_node);
    block->value = -1;
   // cout << "c" << endl;
   int RH = rand() % MatrixSize;
   int RW = rand() % MatrixSize;
   int ans = 0;
   int f = 0;
   try {
    for (int i=RW; i<MatrixSize+RW; ++i)
        for (int j=RH; j<MatrixSize+RH; ++j)
        {
            tree = block;


             for (int ii=0; ii<RodSize; ++ii)
                for (int jj=0; jj<RodSize; ++jj)
                    {
                        //cout << "+" << a[(i+ii)%MatrixSize][(j+jj)%MatrixSize] << endl;
                    if (tree->lst[a[(i+ii)%MatrixSize][(j+jj)%MatrixSize]] == NULL)
                        tree->lst[a[(i+ii)%MatrixSize][(j+jj)%MatrixSize]] = new (struct t_tree_node);
                   // cout << "-"  << endl;
                    tree = tree->lst[a[(i+ii)%MatrixSize][(j+jj)%MatrixSize]];

                    }
                   // cout << "v" << tree->value << endl;
            tree->value++;
            ans++;
            if  (tree->value > 1)
            {
                //if (f)
               // {
                    //resAns += ans;
                    cout << ans << endl;
                    throw 1;
               // }
               // else
                  //  f = 1;
            }
        }
        }
        catch(const int er) {};
    }

   // cout << resAns/(double) RN;

    ///=========================================
    /// Конец алгоритма

//    prnt(block);
//    result.cur_time = clock() - result.cur_time;
//    result.avg_time += result.cur_time;
//    result.min_time = min(result.min_time, result.cur_time);
//    result.max_time = max(result.max_time, result.cur_time);
//    fin.close();

//    } while (FindNextFile(hFind, &data));
//    FindClose(hFind);
//    fout.close();
//    }
//    result.avg_time/=result.files_count;
//    cout << "Files count: " << result.files_count << endl;
//    cout << "Min time: " << result.min_time << endl;
//    cout << "Max time: " << result.max_time << endl;
//    cout << "Avg time: " << result.avg_time << endl;
    return 0;
}
