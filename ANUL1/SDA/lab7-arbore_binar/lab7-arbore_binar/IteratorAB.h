#pragma once
#include "AB.h"

#include <queue>
#include <stack>
using std::queue;
using std::stack;


class IteratorAB {
public:

	friend class AB;

	//operatii pe iterator
	virtual void prim()=0;

	virtual void urmator()=0;

	virtual TElem element() = 0;

	virtual bool valid() = 0;




    virtual ~IteratorAB() = default;
};

class IteratorPreordine: public IteratorAB{
    friend class AB;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container

	IteratorPreordine(const AB& _ab);

	//contine o referinta catre containerul pe care il itereaza

   	const AB& ab;
       
	/* aici e reprezentarea specifica a iteratorului*/
    stack<PNod> s;
    PNod curent;
    void golireStiva(stack<PNod>& s);


public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();

        void revinoKPasi(int k);
};


#include <exception>
class IteratorInordine: public IteratorAB{
   friend class AB;
private:
  //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
   IteratorInordine(const AB& _ab);

    void golireStiva(stack<PNod>& s);

  //contine o referinta catre containerul pe care il itereaza

   const AB& ab;
   /* aici e reprezentarea specifica a iteratorului*/

    stack<PNod> s;
    PNod curent;

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();



};

struct NodPostordine{
    PNod p;
    int k;
};

class IteratorPostordine: public IteratorAB{
   friend class AB;
private:

    //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
  	IteratorPostordine(const AB& _ab);
    //contine o referinta catre containerul pe care il itereaza

	const AB& ab;
	/* aici e reprezentarea specifica a itertorului*/

    stack<NodPostordine> s;
    PNod curent;
    void golireStiva(stack<NodPostordine>& s);

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();


};

class IteratorLatime: public IteratorAB{
   friend class AB;
private:

   //constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
   IteratorLatime(const AB& _ab);
   //contine o referinta catre containerul pe care il itereaza

   const AB& ab;
 	/* aici e reprezentarea pecifica a itratorului*/

    queue<PNod> q;
    PNod curent;
    void golireCoada(queue<PNod>& q);

public:

		//reseteaza pozitia iteratorului la inceputul containerului
		void prim();

		//muta iteratorul in container
		// arunca exceptie daca iteratorul nu e valid
		void urmator();

		//verifica daca iteratorul e valid (indica un element al containerului)
		bool valid();

		//returneaza valoarea elementului din container referit de iterator
		//arunca exceptie daca iteratorul nu e valid
		TElem element();


};


// Algoritm revinoKPasi(k)
// creeaza(tempStack)
// p <- ab.rad
// prec <- NIL

// cat timp (!vida(tempStack) sau p != NIL) executa
//     cat timp p != NIL executa
//         adauga(tempStack, p)
//         p <- [p].st
//     sf cattimp

//     sterge(tempStack, p)

//     daca p = it.curent atunci
//         daca k <= 0 atunci
//             return

//         pentru i de la 0 la k-1 executa
//             daca prec = NIL atunci
//                 @arunca exceptie
//             sf daca

//             it.curent <- prec
//             p <- ab.rad
//             tempStack.clear()

//             cat timp (!vida(tempStack) sau p != NIL) executa
//                 cat timp p != NIL executa
//                     adauga(tempStack, p)
//                     daca p = it.curent atunci
//                         p <- [p].st
//                         it.curent <- p
//                     sf daca
//                     p <- [p].st
//                 sf cattimp

//                 sterge(tempStack, p)
//                 daca p = prec atunci
//                     p <- [p].dr
//                     tempStack.clear()
//                     break
//                 sf daca
//                 daca [p].dr != NIL atunci
//                     adauga(tempStack, [p].dr)
//                 sf daca
//                 daca [p].st != NIL atunci
//                     adauga(tempStack, [p].st)
//                 sf daca
//             sf cattimp

//             prec <- NIL
//         sf pentru

//         daca it.curent = ab.rad atunci
//             @arunca exceptie
//         sf daca

//         return
//     sf daca

//     p <- [p].dr
// sf cattimp

// @arunca exceptie
// sf subalgoritm