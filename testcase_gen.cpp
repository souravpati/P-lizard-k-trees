#include <iostream>
#include <fstream>
#include <string>
#include<bits/stdc++.h>
using namespace std;

void gen(string type,int N, int lizzNum, string filename,double treeRatio)
{
	int **Graph=new int*[N];
	for (int i = 0; i < N; i++)
	{
		Graph[i] = new int[N];
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int tmp = ceil(10 * treeRatio);
			int num = 1+rand() % 10;
			if (num <= tmp)
			{
				Graph[i][j] = 2;
			}
			else
			{
				Graph[i][j] = 0;
			}
		}
	}
	

	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "File Error!" << endl;
		exit(-1);
	}

	out << type << endl;
	out << N << endl;
	out << lizzNum << endl;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			out << Graph[i][j];
		}
		out << endl;
	}

}

int main()
{
	gen("SA", 35, 45, "input4.txt",0.000000001);
	//gen("SA", 12, 12, "input.txt",0.05);
}