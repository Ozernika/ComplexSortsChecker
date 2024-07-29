#include <iostream>
#include <windows.h>
#include <random>
#include <chrono>
#include <ctime>
using namespace std;

std::mt19937 gen(time(0));
std::uniform_int_distribution<>id(0, 1000000);

void rand_array(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		*(arr + i) = id(gen);
	}
}

void insert_sort(int* arr, int size)
{
	for (int i = 1; i < size; i++)
	{
		for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
		{
			int temp = arr[j - 1];
			arr[j - 1] = arr[j];
			arr[j] = temp;
		}
	}
}
void print_arr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << *(arr + i) << "  ";
	}
}
int increment(long inc[], long size) {
	int p1, p2, p3, s;

	p1 = p2 = p3 = 1;
	s = -1;
	do {
		if (++s % 2) {
			inc[s] = 8 * p1 - 6 * p2 + 1;
		}
		else {
			inc[s] = 9 * p1 - 9 * p3 + 1;
			p2 *= 2;
			p3 *= 2;
		}
		p1 *= 2;
	} while (3 * inc[s] < size);

	return s > 0 ? --s : 0;
}

void shellSort(int *a, long size) {
	long inc, i, j, seq[40];
	int s;

	// вычисление последовательности приращений
	s = increment(seq, size);
	while (s >= 0) {
		// сортировка вставками с инкрементами inc[] 
		inc = seq[s--];

		for (i = inc; i < size; i++) {
		int temp = a[i];
			for (j = i - inc; (j >= 0) && (a[j] > temp); j -= inc)
				a[j + inc] = a[j];
			a[j + inc] = temp;
		}
	}
}
void shellSort_reverse(int* a, long size) {
	long inc, i, j, seq[40];
	int s;

	// вычисление последовательности приращений
	s = increment(seq, size);
	while (s >= 0) {
		// сортировка вставками с инкрементами inc[] 
		inc = seq[s--];

		for (i = inc; i < size; i++) {
			int temp = a[i];
			for (j = i - inc; (j >= 0) && (a[j] < temp); j -= inc)
				a[j + inc] = a[j];
			a[j + inc] = temp;
		}
	}
}
void MergeSort(int* a, int p, int q, int r)
{
	int n1 = q - p + 1;
	int n2 = r - q;
	int* L1 = new int[n1];
	int* L2 = new int[n2];
	for (int i = 0; i < n1; i++)
		L1[i] = a[p + i];
	for (int j = 0; j < n2; j++)
		L2[j] = a[q + j + 1];
	int i = 0, j = 0, k = p;
	while (i < n1 && j < n2)
	{
		if (L1[i] <= L2[j])
		{
			a[k] = L1[i];
			i++;
		}
		else
		{
			a[k] = L2[j];
			j++;
		}
		k++;
	}
	while (i < n1)
	{
		a[k] = L1[i];
		i++;
		k++;
	}
	while (j < n2)
	{
		a[k] = L2[j];
		j++;
		k++;
	}
}
void Merge(int* a, int p, int r)
{
	if (p >= r) {
		return;
	}
	int q = p + (r - p) / 2;
	Merge(a, p, q);
	Merge(a, q + 1, r);
	MergeSort(a, p, q, r);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите 1, если хотите выполнить сортировку простой вставки" << endl;
	cout << "Введите 2, если хотите выполнить сортировку Шелла со смещениями Р. Седжвика" << endl;
	cout << "Введите 3, если хотите выполнить сортировку слиянием" << endl;
	int ch;
	cin >> ch;
	cout << "Введите размер массива: ";
	int size;
	cin >> size;
	int* arr = new int[size];
	rand_array(arr, size);
	shellSort(arr, size);
	//shellSort_reverse(arr, size);
	if (ch == 1)
	{
		auto start = chrono::high_resolution_clock::now();
		insert_sort(arr, size);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;
		cout << "Время выполения алгоритма: " << duration.count() << " с";
	}
	else if (ch == 2)
	{
		auto start = chrono::high_resolution_clock::now();
		shellSort(arr, size);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;
		cout << "Время выполения алгоритма: " << duration.count() << " с";
	}
	else
	{
		auto start = chrono::high_resolution_clock::now();
		Merge(arr, 0, size - 1);
		auto end = chrono::high_resolution_clock::now();
		chrono::duration<float> duration = end - start;
		cout << "Время выполения алгоритма: " << duration.count() << " с";
	}
	//cout << endl << "Отсортированный массив" << endl;
	//print_arr(arr, size);
	return 0;
}