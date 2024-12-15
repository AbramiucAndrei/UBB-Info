#pragma once

#include "MDO.h"


class IteratorMDO{
	friend class MDO;
private:

	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorMDO(const MDO& dictionar);

	//contine o referinta catre containerul pe care il itereaza
	const MDO& dict;
	int index;
	PNod curent;
	/* aici e reprezentarea  specifica a iteratorului */


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		//teta(1)
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		//teta(1)
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		//teta(1)
		bool valid() const;

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		//teta(1)
		TElem element() const;

		//teta(k)
		void avanseaza(int k);
};

