#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include "Header.h"
using namespace::std;

void output(int** p, int n) //Вывод графа
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}
}

int** input(int** g, int n) //Заполнение матрицы смежности вручную
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			g[i][j] = 0;
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			system("cls");
			g[i][j] = 8;
			cout << "8 - место записи" << endl;
			output(g, n);
			cout << "»";
			cin >> g[i][j];
			cout << endl;
		}
	}
	return g;
}

int** input_auto(int** g, int n) //заполнение матрицы смежности для графа G Автоматически
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				g[i][j] = 0;
			}
			else
			{
				g[i][j] = rand() % 2;
			}
			g[j][i] = g[i][j];
		}
	}
	return g;
}

int** input_auto_euler(int** g, int n) //заполнение матрицы с эйлеровым циклом смежности для графа G Автоматически
{
	int two = 0;
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum = 0;
		for (int j = 0; j < n; j++)
		{
			if (g[i][j] == 1) sum++;

			if ((g[i][j] == 0) && (i != j)) two = j;
		}
		if (sum % 2 == 1)
		{
			g[i][two] = 1;
		}
	}
	return g;
}

int** euler(int** g, int n) //Алгоритм поиска Эйлерова цикла
{
	int i, j;
	int start, pos = 0, p, k, LIFO[100], C[2][100];
	start = 0;
	int temp = 0;
	int one = 0;

	ofstream FILE("Euler_cycle.txt");

	FILE << "Матрица смежности:" << endl;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			FILE << g[i][j] << " ";
		}
		FILE << endl;
	}

	cout << endl;

	LIFO[0] = start; // Заносим в стек стартовую вершину
	k = 1; // Позиция вершины стека
	while (k != 0)
	{
		p = 0;
		// Находим вершину с минимальным номером и смежную с вершиной номер которой в стеке

		for (i = 0; i < n; i++)

			if (g[LIFO[k - 1]][i] == 1)
			{
				p = 1;
				break;
			}
		if (p != 0)
		{
			LIFO[k] = i; //Заносим вершину в стек
			//Помечаем ребро как прямое
			g[LIFO[k - 1]][i] = 2;
			g[i][LIFO[k - 1]] = 2;
			k++; // Сдвигаем позицию стека на 1 вверх
		}
		else
		{
			// Выносим обратное ребро
			C[0][pos] = LIFO[k - 1];
			C[1][pos] = LIFO[k - 2];
			pos++;
			k--;
		}
	}

	// Выводим результат
	for (i = 0; i < pos - 1; i++)
		cout << C[0][i] << " " << C[1][i] << endl;
	// Запись в файл
	FILE << "Эйлеров цикл:" << endl;

	for (i = 0; i < pos - 1; i++) {
		FILE << C[0][i] << " " << C[1][i] << endl;
	}
	FILE.close();
	return 0;
}
