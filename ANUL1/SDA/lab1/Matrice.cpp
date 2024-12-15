#include "Matrice.h"
#include <iostream>
#include <exception>

using namespace std;

Matrice::Matrice(int m, int n) {	/*
        Complexitate teta(1)
	 */
	if (m<=0 or n<=0)
        throw exception();

	this->v=new triplet[1];
	this->cap=1;
	this->nr_elem=0;

	this->linii=m;
	this->coloane=n;
}

Matrice::~Matrice(){
    //Complexitate teta(1)
    delete[]this->v;
}

void Matrice::redim() {
    //Complexitate teta(nr_elem)
    triplet *w=new triplet[2*this->cap];
    for(int i=0;i<this->nr_elem;i++){
        w[i]=v[i];
    }

    delete[]this->v;
    v=w;
    this->cap=2*this->cap;

}

int Matrice::nrLinii() const{	/* de adaugat */
	//complexitate teta(1)
	return this->linii;
}

int Matrice::nrColoane() const{	/* de adaugat */
	//complexitate teta(1)
	return this->coloane;
}
int Matrice::nrElemente() const{
    //complexitate teta(1)
    return this->nr_elem;
}

TElem Matrice::element(int i, int j) const{	/* de adaugat */
	//Complexitate O(nrElemente)
	//caz defavorabil: perechea cautata nu se afla in matrice
	//caz favorabil:perechea cautata se afla pe prima pozitie in matrice
	if (i<0 or j<0 or i>=this->nrLinii() or j>=this->nrColoane())
        throw exception();

    for(int k=0;k<(this->nrElemente());k++){
        if(this->v[k].l==i)
            if(this->v[k].c==j)
                return this->v[k].value;
    }

    return NULL_TELEMENT;
}
bool Matrice::to_swap(triplet x,triplet y){
    //complexitate teta(1)
    if(y.l<x.l) return 1;
    else if(y.l>x.l) return 0;
    else{
        //x.l==y.l
        if(y.c<x.c) return 1;
        else return 0;
    }
}
TElem Matrice::modifica(int i, int j, TElem e) {
	/* de adaugat */
	//COMPLEXITATE TOTALA O(nrElem)

	//O(nrElem)
	for(int k=0;k<(this->nrElemente());k++)
        if(this->v[k].l==i and this->v[k].c==j){
            int val=this->v[k].value;
            this->v[k].value=e;
            return val;//deja existent
        }

    //inexistent
    //teta(nrElem)
    if(this->nrElemente()==this->cap)
        this->redim();


    //O(nrElem)
    triplet new_tr={i,j,e};
    this->v[this->nrElemente()]=new_tr;
    this->nr_elem++;

    for(int k=(this->nrElemente()-1);k>=1 && to_swap(this->v[k],this->v[k-1]);k--)
            swap(this->v[k],this->v[k-1]);

    //return this->v[this->nrElemente()-1].value;//adaugat dupa
    return -1;
}

void Matrice::transpusa(Matrice& ot){
    //teta(nrElem) * O(nrElem) => O(n^2)

    if (!(this->nrLinii() == ot.nrColoane() && this->nrColoane() == ot.nrLinii()))
        throw exception();
    for(int k=0;k<ot.nrElemente();k++){
        triplet x=ot.v[k];

        this->modifica(x.c,x.l,x.value);
    }

}

