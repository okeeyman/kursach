#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include "Header.h"
using namespace::std;

void output(int** p, int n) //����� �����
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

int** input(int** g, int n) //���������� ������� ��������� �������
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
			cout << "8 - ����� ������" << endl;
			output(g, n);
			cout << "�";
			cin >> g[i][j];
			cout << endl;
		}
	}
	return g;
}

int** input_auto(int** g, int n) //���������� ������� ��������� ��� ����� G �������������
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

int** input_auto_euler(int** g, int n) //���������� ������� � ��������� ������ ��������� ��� ����� G �������������
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

int** euler(int** g, int n) //�������� ������ �������� �����
{
	int i, j;
	int start, pos = 0, p, k, LIFO[100], C[2][100];
	start = 0;
	int temp = 0;
	int one = 0;

	ofstream FILE("Euler_cycle.txt");

	FILE << "������� ���������:" << endl;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			FILE << g[i][j] << " ";
		}
		FILE << endl;
	}

	cout << endl;

	LIFO[0] = start; // ������� � ���� ��������� �������
	k = 1; // ������� ������� �����
	while (k != 0)
	{
		p = 0;
		// ������� ������� � ����������� ������� � ������� � �������� ����� ������� � �����

		for (i = 0; i < n; i++)

			if (g[LIFO[k - 1]][i] == 1)
			{
				p = 1;
				break;
			}
		if (p != 0)
		{
			LIFO[k] = i; //������� ������� � ����
			//�������� ����� ��� ������
			g[LIFO[k - 1]][i] = 2;
			g[i][LIFO[k - 1]] = 2;
			k++; // �������� ������� ����� �� 1 �����
		}
		else
		{
			// ������� �������� �����
			C[0][pos] = LIFO[k - 1];
			C[1][pos] = LIFO[k - 2];
			pos++;
			k--;
		}
	}

	// ������� ���������
	for (i = 0; i < pos - 1; i++)
		cout << C[0][i] << " " << C[1][i] << endl;
	// ������ � ����
	FILE << "������� ����:" << endl;

	for (i = 0; i < pos - 1; i++) {
		FILE << C[0][i] << " " << C[1][i] << endl;
	}
	FILE.close();
	return 0;
}
