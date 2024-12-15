#pragma once

#include <vector>

typedef int TCheie;
typedef int TValoare;

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

using namespace std;

class IteratorMDO;

typedef bool(*Relatie)(TCheie, TCheie);

struct Nod {
	TElem val;
	Nod* urm;
	Nod* prec;
};

typedef struct Nod* PNod;
typedef struct Nod nod;
#define NIL NULL;

class MDO {
	friend class IteratorMDO;
    private:
		PNod prim;
		PNod ultim;
		int size;
		Relatie r;
    public:

	// constructorul implicit al MultiDictionarului Ordonat
	//teta(1)
	MDO(Relatie r);

	// adauga o pereche (cheie, valoare) in MDO
	//O(n)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	//O(n)
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	//O(n)
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MDO 
	//teta(1)
	int dim() const;

	//verifica daca MultiDictionarul Ordonat e vid 
	//teta(1)
	bool vid() const;

	// se returneaza iterator pe MDO
	// iteratorul va returna perechile in ordine in raport cu relatia de ordine
	//teta(1)
	IteratorMDO iterator() const;

	// destructorul 
	// O(n)	
	~MDO();

};
