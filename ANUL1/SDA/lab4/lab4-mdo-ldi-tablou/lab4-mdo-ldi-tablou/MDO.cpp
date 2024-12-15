#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

//teta(n)- n noua capacitate a vectorului
void MDO::redimensionare() {
	TElem* new_val;
	int *new_urm, *new_prec;
	new_val = new TElem[2 * cp];
	new_urm = new int[2 * cp];
	new_prec = new int[2 * cp];

	for (int i = 0; i < cp; i++) {
		new_val[i] = val[i];
		new_urm[i] = urm[i];
		new_prec[i] = prec[i];
	}
	for (int i = cp; i < 2 * cp -1; i++) {
		new_val[i] = TElem(-1, -1);
		new_urm[i] = i+1;
		new_prec[i] = -1;
	}
	new_val[2 * cp - 1] = TElem(-1, -1);
	new_urm[2 * cp - 1] = -1;
	new_prec[2 * cp - 1] = -1;

	delete[] val;
	delete[] urm;
	delete[] prec;

	val = new_val;
	urm = new_urm;
	prec = new_prec;

	primLiber = cp;
	cp *= 2;
}


//teta(1)
void MDO::dealoca(int index) {
	//dealoca nodul de la pozitia "index"
	if(primLiber!=-1)
		prec[primLiber] = index;
	urm[index] = primLiber;
	primLiber = index;
}
//teta(1)
void MDO::initSpatiuLiber() {
	prim = -1;
	primLiber = 0;
	cp = 2;

	val = new TElem[cp];
	urm = new int[cp];
	prec = new int[cp];

	for (int i = 0; i < cp-1; i++) {
		val[i] = TElem(-1, -1);
		urm[i] = i + 1;
		prec[i] = -1;
	}
	val[cp - 1] = TElem(-1, -1);
	urm[cp - 1] = -1;
	prec[cp - 1] = -1;
}

//teta(1)
int MDO::aloca() {
	//marcheaza nodul ca si ocupat
	//returneaza pozitia ce a fost ocupata
	int index = primLiber;
	primLiber = urm[primLiber];
	return index;
}

//teta(1)
int MDO::creeazaNod(TElem pereche) {
	if(primLiber==-1){//nu avem spatiu
		redimensionare();
	}

	int index_liber = aloca();

	val[index_liber] = pereche;
	urm[index_liber] = -1;
	prec[index_liber] = -1;

	return index_liber;
}

//teta(1)
MDO::MDO(Relatie r) {
	rel = r;
	len = 0;
	initSpatiuLiber();
}

//O(n)
void MDO::adauga(TCheie c, TValoare v) {
	

	if (len == 0) {
		int index_nod = creeazaNod(TElem(c, v));
		prim = index_nod;
		len++;
		return;
	}

	int before_it = -2;
	int it = prim;
	while (it != -1 and !rel(c, val[it].first)) {
		before_it = it;
		it = urm[it];
	}

	if (it != -1)//intre 2
	{
		adauga_inainte(TElem(c, v), it);
	}
	else{//se add la sfarsit
		int index_nod = creeazaNod(TElem(c, v));
		urm[before_it] = index_nod;
		prec[index_nod] = before_it;
	}
	len++;
}
//teta(1)
void MDO::adauga_inainte(TElem pair_to_add, int before_this) {
	int index_nod = creeazaNod(pair_to_add);

	if (before_this == prim) {
		prec[prim] = index_nod;
		urm[index_nod] = prim;
		prim = index_nod;
	}
	else {
		urm[prec[before_this]] = index_nod;
		prec[index_nod] = prec[before_this];
		prec[before_this] = index_nod;
		urm[index_nod] = before_this;
	}
}
//O(n)
vector<TValoare> MDO::cauta(TCheie c) const {
	vector <TValoare> result;
	int poz = prim;
	while (poz != -1) {
		if (val[poz].first == c) {
			result.push_back(val[poz].second);
		}
		poz = urm[poz];
	}
	return result;
}
//O(n)
bool MDO::sterge(TCheie c, TValoare v) {
	int it = prim;
	while (it != -1) {
		if (val[it] == TElem(c, v)) {
			if (it == prim) {
				prim = urm[prim];
			}
			else {
				urm[prec[it]] = urm[it];
				if(urm[it]!=-1)
					prec[urm[it]] = prec[it];
			}
			dealoca(it);
			len--;
			return true;
		}
		it = urm[it];
	}
	return false;
}
//teta(1)
int MDO::dim() const {
	return len;
}
//teta(1)
bool MDO::vid() const {
	/* de adaugat */
	return len == 0;
}
//teta(1)
IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}
//teta(1)
MDO::~MDO() {
	delete[] val;
	delete[] urm;
	delete[] prec;
}
