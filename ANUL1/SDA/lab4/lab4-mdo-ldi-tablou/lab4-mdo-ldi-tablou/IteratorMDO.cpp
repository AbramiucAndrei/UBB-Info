#include "IteratorMDO.h"
#include "MDO.h"
//teta(1)
IteratorMDO::IteratorMDO(const MDO& d) : dict(d){
	
	prim();
}
//teta(1)
void IteratorMDO::prim(){
	index = dict.prim;
	poz = 0;
}
//teta(1)
void IteratorMDO::urmator(){
	if (!valid())
		throw exception("Nu se poate trece mai departe!");

	index = dict.urm[index];
	poz++;
}
//teta(1)
bool IteratorMDO::valid() const{
	return poz < dict.len;
}
//teta(1)
TElem IteratorMDO::element() const{
	if (!valid())
		throw exception("Nu e valid!");
	return dict.val[index];
}


