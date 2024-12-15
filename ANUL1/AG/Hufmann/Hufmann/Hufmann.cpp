
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>

#include <functional>
#include <map>
#include <queue>
using namespace std;
ifstream fin("huffman.in");

struct Nod {
	char chr;
	int nr;
	Nod* st, * dr;
};

struct compare {
	bool operator()(Nod* p1, Nod* p2) {
		if (p1->nr < p2->nr)
			return false;
		else if (p1->nr > p2->nr)
			return true;
		else {
			return p1->chr > p2->chr;
		}
	}
};

int main()
{
	map <char, int> frec;
	string source;
	getline(fin, source);

	//numar frecventele fiecarei litere
	for (auto& chr : source) {
		frec[chr]++;
	}

	//pastrez crescatoare nodurile dupa frecventa fiecarei litere
	priority_queue < Nod* ,vector<Nod*>, compare> pq;


	cout << frec.size() << endl;
	for (auto pair : frec) {
		cout << pair.first << ':' << pair.second << endl<<endl;

		//creez fiecare nod , asociat fiecarei litere
		Nod* create = new Nod;
		create->st = create->dr = NULL;
		create->chr = pair.first; create->nr = pair.second;
		//adaug nodurile in lista de noduri sortata crescator
		pq.push(create);
	}


	while (pq.size() > 1) {
		Nod* min1, * min2;
		min1 = pq.top();
		pq.pop();
		min2 = pq.top();
		pq.pop();

		//leg noul nod la primele 2 noduri din lista
		//cele cu frecventa cea mai mica
		//valoarea noului nod va fi suma celor 2, st si dr
		//char ul nu conteaza
		Nod* create = new Nod;
		create->st = min1; create->dr = min2;
		create->nr = min1->nr + min2->nr;
		create->chr = min(min1->chr,min2->chr);
		pq.push(create);
	}
	
	//raman cu radacina arborelui
	Nod* rad = pq.top();

	//bfs
	queue<pair<Nod*,string>> q;
	q.push(pair<Nod*,string>(rad,""));
	
	//fiecarui caracter ii asociez un cod format din 1 si 0
	map<char, string> codare;

	//bfs
	while (!q.empty()) {
		auto curent = q.front();
		q.pop();

		Nod* node;
		string node_string;
		node = curent.first;
		node_string = curent.second;

		if (node->st != NULL) {
			//daca nu e nod terminal
			q.push(pair<Nod*, string>(node->st, node_string + "0"));
			q.push(pair<Nod*, string>(node->dr, node_string + "1"));
		}
		else {
			//nod terminal
			codare[node->chr] = node_string;
		}

	}

	//afisez codarea
	for (auto& chr : source) {
		cout << codare[chr];
	}

	
	fin.close();
}