#include "IteratorMDO.h"
#include "MDO.h"

IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	prim();
}

void IteratorMDO::prim(){
	curent = dict.prim;
	index = 0;
}

void IteratorMDO::urmator(){
	if (!valid())
		throw exception("Am ajuns la final!");

	index++;
	curent = curent->urm;
}

bool IteratorMDO::valid() const{
	
	return index < dict.size;
}

TElem IteratorMDO::element() const{
	if (!valid())
		throw exception("Elementul nu e valid!");

	return curent->val;
}

void IteratorMDO::avanseaza(int k) {
	if (k + index > dict.size)
		throw exception("Nu pot avansa k pasi!");

	for (int i = 1; i <= k; i++) {
		urmator();
	}
}


/*Subalgoritm avanseaza(k):
	ITERATOR it
	* Daca k+index > dimensiune(dict) atunci:
	*	@arunca exceptie
	* SfDaca
	* 
	PENTRU i <- 1,k EXECUTA:

		urmator(it)

	SfPentru
SfSubalgoritm
*/
