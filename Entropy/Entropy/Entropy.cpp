// Entropy.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
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
#include <cstdlib>
#include <sstream>
#define MatrixSize 256
#define RodSize 8


using namespace std;

struct t_result
{
	float min_time;
	float max_time;
	float avg_time;
	float cur_time;
	int files_count;

} result;

int a[257][257];
int o[257][257];
int z[257][257];
unordered_map <string, int> window;

pair <int, int> getSum(int x1, int y1, int x2, int y2)
{
	return make_pair(z[x2][y2] + z[x1 - 1][y1 - 1] - z[x1 - 1][y2] - z[x2][y1 - 1],
		o[x2][y2] + o[x1 - 1][y1 - 1] - o[x1 - 1][y2] - o[x2][y1 - 1]);
}

template <class T>
std::string to_string(T t)
{
	std::ostringstream oss;
	oss << t;
	return oss.str();
}

int main()
{

	result.min_time = 1.7e+308;
	result.max_time = 0;
	result.avg_time = 0;
	result.files_count = 0;
	// файл вывода
	ofstream fout("output.txt");
	// сканируем файлы в директории
	HANDLE hFind;
	WIN32_FIND_DATA data;

	hFind = FindFirstFile("\Grid*.txt", &data);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			result.files_count++;
			ifstream fin(data.cFileName);


			// считывание файла
			for (int i = 1; i <= MatrixSize; ++i)
				for (int j = 1; j <= MatrixSize; ++j)
				{
					fin >> a[i][j];
					z[i][j] = 0;
					o[i][j] = 0;
				}
			result.cur_time = clock();


			//==========================================
			// Алгоритм
			for (int i = 1; i <= MatrixSize; ++i)
				for (int j = 1; j <= MatrixSize; ++j)
				{

					z[i][j] = z[i - 1][j] + z[i][j - 1] - z[i - 1][j - 1] + (a[i][j] == 1);
					o[i][j] = o[i - 1][j] + o[i][j - 1] - o[i - 1][j - 1] + (a[i][j] == 2);
				}
			for (int i = 1; i <= MatrixSize; ++i)
				for (int j = 1; j <= MatrixSize; ++j)
				{
					auto p = make_pair(0, 0);
					p = getSum(i, j, min(MatrixSize, i + RodSize - 1), min(MatrixSize, j + RodSize - 1));
					if (i + RodSize - 1 > MatrixSize)
					{
						auto add = getSum(1, j, (i + RodSize - 1) % MatrixSize, min(MatrixSize, j + RodSize));
						p.first += add.first;
						p.second += add.second;
					}
					if (j + RodSize - 1 > MatrixSize)
					{
						auto add = getSum(i, 1, min(MatrixSize, i + RodSize), (j + RodSize - 1) % MatrixSize);
						p.first += add.first;
						p.second += add.second;
					}
					if (i + RodSize - 1 > MatrixSize && j + RodSize - 1 > MatrixSize)
					{
						auto add = getSum(1, 1, (i + RodSize - 1) % MatrixSize, (j + RodSize - 1) % MatrixSize);
						p.first += add.first;
						p.second += add.second;
					}
					string res = to_string<int>(p.first) + "_" + to_string<int>(p.second);
					// cout << res;
					if (window.find(res) != window.end())
						window[res]++;
					else
						window[res] = 1;
				}

			//=========================================
			// Конец алгоритма


			result.cur_time = clock() - result.cur_time;
			result.avg_time += result.cur_time;
			result.min_time = min(result.min_time, result.cur_time);
			result.max_time = max(result.max_time, result.cur_time);
			fin.close();
			
			//entropy
			fout << window.size() << "\t";
			double entr = 0;
			for (auto win : window)
			{
				//fout << win.first << "\t" << win.second << "\n";
				entr -= 1.0 * win.second / (double)MatrixSize / (double)MatrixSize *
					log(1.0 * win.second / (double)MatrixSize / (double)MatrixSize) / log(RodSize * RodSize * RodSize * RodSize);
			}
			fout << entr << endl;

			window.clear();

		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
		fout.close();

	}
	result.avg_time /= result.files_count;
	cout << "Files count: " << result.files_count << endl;
	cout << "Min time: " << result.min_time << endl;
	cout << "Max time: " << result.max_time << endl;
	cout << "Avg time: " << result.avg_time << endl;
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
