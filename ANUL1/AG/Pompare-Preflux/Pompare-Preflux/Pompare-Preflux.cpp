// Pompare-Preflux.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("date.in");
ofstream fout("date.out");


int mat[1001][1001],inaltime[1001],rezervor[1001],n,m;
void initializare_preflux(int source, int dest) {
	for (int i = 0; i < n; i++)
	{
		inaltime[i] = 0;
		rezervor[i] = 0;
	}

	inaltime[source] = n;

	for(int i=0;i<n;i++)
		if (mat[source][i] != 0) {
			int cap = mat[source][i];

			mat[source][i] = 0;
			mat[i][source] = cap;

			rezervor[i] = cap;
			rezervor[source] -= cap;

		}
}

void pompare(int from, int to) {
	int quantity = min(rezervor[from],mat[from][to]);

	mat[from][to] -= quantity;
	mat[to][from] += quantity;

	rezervor[from] -= quantity;
	rezervor[to] += quantity;
}

void inaltare(int nod) {
	int minimul = INT_MAX;
	//
	for (int i = 0; i < n; i++)
		if (mat[nod][i])
			minimul = min(minimul, inaltime[i]);
	inaltime[nod] = 1 + minimul;
}

void pompare_preflux(int source, int dest) {
	initializare_preflux(0, n - 1);
	while (true) {
		for(int i=1;i<n-1;i++)
				if(rezervor[i]>0)
					for(int j=0;j<n;j++)
						if (mat[i][j]>0 and inaltime[i] == inaltime[j] + 1)
						{
							pompare(i, j);
							continue;
						}
		for (int i = 1; i < n - 1; i++)
			if (rezervor[i] > 0) {
				bool ok = 1;
				for (int j = 0; j < n and ok; j++)
					if (mat[i][j])
						if (!(inaltime[i] <= inaltime[j]))
							ok = 0;
				if (ok == 1) {
					inaltare(i);
					continue;
				}
			}

		break;
	}
}

int main()
{
	fin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, val;
		fin >> x >> y >> val;
	}

	pompare_preflux(0, n - 1);
	fout << rezervor[n - 1];
}
