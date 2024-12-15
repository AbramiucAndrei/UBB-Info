#pragma once

typedef int TElem;
typedef struct {
    int l,c;
    TElem value;
} triplet;

#define NULL_TELEMENT 0

class Matrice {

private:
	/* aici e reprezentarea */
    triplet *v;
    int cap,nr_elem;
    int linii,coloane;

public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice();

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	TElem element(int i, int j) const;


	// returnare numar linii
	int nrLinii() const;

	// returnare numar coloane
	int nrColoane() const;

	//returnare numar elemente din matrice
	int nrElemente() const;

	//functie de comparare a 2 triplete, pentru a
	//afla daca acestea trebuie inversate la inserare
	bool to_swap(triplet x,triplet y);

	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	TElem modifica(int i, int j, TElem e);

	//redimensioneaza matricea ,dubland capacitatea
	void redim();

	//transpusa
    void transpusa(Matrice& ot);

};







