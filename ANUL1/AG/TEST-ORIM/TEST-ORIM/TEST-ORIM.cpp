// TEST-ORIM.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <functional>
#include <vector>
#define inf 1000000000
using namespace std;
ifstream fin("prim.in");
ofstream fout("prim.out");

int n, m , total;
typedef struct nou{
	int val;
	int nod;
} pint;

bool compare(pint a, pint b) {
	return a.val > b.val;
}

vector<pint> muc[1001];

int main()
{	
	fin >> n >> m;
	for (int i = 1; i <= m; i++) {
		int x, y, val;
		fin >> x >> y >> val;

		muc[x].push_back({ val,y });
		muc[y].push_back({ val,x });

	}
	
	int dist[1001], t[1001];
	bool viz[1001];
	for (int i = 1; i <= n; i++) {
		dist[i] = inf;
		t[i] = i;
		viz[i] = 0;
	}
	dist[1] = 0;

	priority_queue <pint, vector<pint>, function<bool(pint,pint)> > pq(compare);
	pq.push({ 0,1 });

	while (!pq.empty()) {
		auto top = pq.top();
		pq.pop();

		int curent = top.nod;

		if (viz[curent] == 1)
			continue;

		viz[curent] = 1;
		for (auto it : muc[curent]) {
			if (!viz[it.nod] and dist[it.nod] > it.val) {
				dist[it.nod] = it.val;
				pq.push({ it.val,it.nod });
				t[it.nod] = curent;
			}
		}
	}

	for (int i = 1; i <= n; i++) {
		fout <<i<<' ' << t[i] << endl;
		total += dist[i];
	}
	fout << total;

}