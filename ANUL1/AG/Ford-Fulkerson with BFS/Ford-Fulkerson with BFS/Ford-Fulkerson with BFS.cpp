// Ford-Fulkerson with BFS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using namespace std;
ifstream fin("flux1.in");
ofstream fout("flux1.out");


int mat[2001][2001];
int n, m , flux;
int s, d;
bool stop;


bool bfs(int source, int dest, int t[]) {
	queue<int> q;
	bool viz[1001] = {};

	q.push(source);
	viz[source] = 1;
	t[source] = source;
	while (!q.empty()) {
		int curent = q.front();
		q.pop();

		for(int i=0;i<n;i++)
			if (mat[curent][i] != 0 and !viz[i]) {
				viz[i] = 1;
				t[i] = curent;

				if (i == dest)
					return 1;
				else
					q.push(i);
			}
	}
	return 0;
}
int main()
{
	fin >> n >> m;
	//fin >> s >> d;
	s = 0; d = n - 1;
	for (int i = 1; i <= m; i++) {
		int x, y, val;
		fin >> x >> y >> val;
		mat[x][y] = val;

	}

	while (true) {
		int t[1001] = {};

		bool gasit_drum  = bfs(s, d, t);
		if (!gasit_drum)
			break;

		//else
		vector<int> drum;
		int iter = d;

		drum.push_back(iter);
		while (iter != s) {
			drum.insert(drum.begin(), t[iter]);
			iter = t[iter];
		}

		int min = mat[drum[0]][drum[1]];
		for (int i = 1; i < drum.size() - 1; i++) {
			if (mat[drum[i]][drum[i + 1]] < min)
				min = mat[drum[i]][drum[i + 1]];
		}

		for (int i = 0; i < drum.size() - 1; i++) {
			mat[drum[i]][drum[i + 1]] -= min;
			mat[drum[i + 1]][drum[i]] += min;
		}

		flux += min;
	}

	fout << flux;
	return 0;
}
