
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
	int n;
	map <char, int> frec;
	string source;
	
	fin >> n;
	fin.get();
	for (int i = 1; i <= n; i++) {
		getline(fin, source);
		cout << "source:" << source << endl;
		char chr = source[0];
		cout << "chr:" << chr << endl;
		source.erase(0, 2);
		cout << "cut source:" << source << endl;
		frec[chr] = stoi(source);
	}
	//numar frecventele fiecarei litere
	

	//pastrez crescatoare nodurile dupa frecventa fiecarei litere
	priority_queue < Nod*, vector<Nod*>, compare> pq;


	cout << frec.size() << endl;
	for (auto pair : frec) {
		cout << pair.first << ':' << pair.second << endl <<endl;

		//creez fiecare nod , asociat fiecarei litere
		Nod* create = new Nod;
		create->st = create->dr = NULL;
		create->chr = pair.first; create->nr = pair.second;
		//adaug nodurile in lista de noduri sortata crescator
		pq.push(create);
	}
	//while (!pq.empty())
	//{
	//	cout << pq.top()->chr << ':' << pq.top()->nr << endl;
	//	pq.pop();
	//}
	//return 0;


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

	Nod* current = rad;
	char curr_chr;
	while (fin >> curr_chr) {
		if (curr_chr == '0')
			current = current->st;
		else
			current = current->dr;

		if (current->st == NULL) {
			//terminal
			cout << current->chr;
			current = rad;
		}
	}


	fin.close();
}