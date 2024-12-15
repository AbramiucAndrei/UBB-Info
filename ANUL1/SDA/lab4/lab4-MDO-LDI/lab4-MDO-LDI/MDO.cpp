#include "IteratorMDO.h"
#include "MDO.h"
#include <iostream>
#include <vector>

#include <exception>
using namespace std;

MDO::MDO(Relatie r) {
	this->r = r;
	prim = NULL;
	ultim = NULL;
	size = 0;
}


void MDO::adauga(TCheie c, TValoare v) {
	PNod before, curent;
	before = NULL; curent = prim;
	PNod new_nod = new nod;
	new_nod->val = pair<TCheie, TValoare>(c, v);

	while (curent != NULL and r(curent->val.first, new_nod->val.first) == true) {
		before = curent;
		curent = curent->urm;
	}

	new_nod->prec = before;
	new_nod->urm = curent;

	//daca lista e goala,nu fac nimic
	if (curent == NULL and before == NULL) {
		prim = ultim = new_nod;
	}

	//intre doua noduri
	else if (curent != NULL and before != NULL) {
		before->urm = new_nod;
		curent->prec = new_nod;
	}
	//la final,dupa toate
	else if (curent == NULL and before != NULL) {
		before->urm = new_nod;
		ultim = new_nod;
	}
	//la inceput,inainte de toate
	else if (before == NULL and curent != NULL) {
		curent->prec = new_nod;
		prim = new_nod;
	}


	size++;
}

vector<TValoare> MDO::cauta(TCheie c) const {
	vector<TValoare> valori_gasite;

	IteratorMDO it = iterator();
	while (it.valid()) {
		if (it.element().first == c) {
			valori_gasite.push_back(it.element().second);
		}
		it.urmator();
	}
	return valori_gasite;
}

bool MDO::sterge(TCheie c, TValoare v) {
	
	PNod it = prim;
	while (it != NULL) {
		if (it->val == pair<TCheie, TValoare>(c, v)) {
			//am gasit un nod bun
			if (prim == ultim) {
				delete it;
				prim = ultim = NULL;
			}
			else{
				if (it->prec != NULL and it->urm != NULL) {
					//stanga si dreapta sunt noduri
					it->prec->urm = it->urm;
					it->urm->prec = it->prec;
				}
				else if (it->urm == NULL) {
					//it e ultimul din lista, dreapta null
					ultim = it->prec;
					it->prec->urm = NULL;
				}
				else if (it->prec == NULL) {
					//it e primul din lista,stanga e null
					it->urm->prec = NULL;
					prim = it->urm;
				}
				delete it;
			}
			size--;
			return true;
		}
		it = it->urm;
	}

	return false;
}

int MDO::dim() const {
	return this->size;
}

bool MDO::vid() const {
	return this->size == 0;
}

IteratorMDO MDO::iterator() const {
	return IteratorMDO(*this);
}

MDO::~MDO() {
	PNod curent = prim;
	while (curent != NULL) {
		PNod to_delete = curent;
		curent = curent->urm;

		delete to_delete;
	}
}
