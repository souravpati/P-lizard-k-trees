#include<fstream>
#include<iostream>
#include<string>
#include<sstream>

using namespace std;

bool canAtt(int x,int y,int **Graph,int N)
{

	//up
	int i = x-1, j = y;
	while (i >= 0 &&Graph[i][j]!=2 )
	{
		if (Graph[i][j] == 1)
		{
			return true;
		}
		i--;
	}

	//left
	i = x, j = y - 1;
	while (j >= 0 && Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		j--;
	}

	//down
	i = x+1, j = y;
	while (i< N && Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		i++;
	}

	//right
	i = x , j = y+1;
	while (j< N && Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		j++;
	}

	//up left
	i = x-1, j = y - 1;
	while (i >= 0&&j >= 0 && Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		i--;
		j--;
	}

	//up right
	i = x -1, j = y + 1;
	while (i >= 0 && j <N&& Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		i--;
		j++;
	}

	//down right
	i = x + 1, j = y + 1;
	while (i < N && j <N&& Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		i++;
		j++;
	}

	//down left
	i = x + 1, j = y - 1;
	while (i < N && j >=0&& Graph[i][j] != 2)
	{
		if (Graph[i][j] == 1)
			return true;
		i++;
		j--;
	}

	return false;
}

int main()
{
	freopen("out.txt", "r", stdin);
	// if (!in.is_open())
	// {
	// 	cout << "File Error!" << endl;
	// 	exit(-1);
	// }

	string status;
	cin >> status;
	if (status == "OK")
	{
		string line;
		cin >> line;
		int N = line.size();

		int **Graph=new int*[N];
		for (int i = 0; i < N; i++)
		{
			Graph[i] = new int[N];
		}

		for (int i = 0; i < line.size(); i++)
		{
			Graph[0][i] = line[i] - '0';
		}

		int k = 1;
		while (k<N)
		{
			cin >> line;
			for (int i = 0; i < line.size(); i++)
			{
				Graph[k][i] = line[i] - '0';
			}
			k++;
		}

		//check
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (Graph[i][j]==1&&canAtt(i,j,Graph,N))
				{
					cout << "Wrong Answer!" << endl;
					exit(-1);
				}
			}
		}
		cout << "Right Answer!" << endl;
	}
	else
	{
		cout << "FAIL" << endl;
	}
}