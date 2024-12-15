#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

//teta(1)
Nod::Nod(TElem e, PNod st, PNod dr) {
    this->e = e;
    this->st = st;
    this->dr = dr;
}

//teta(n)
PNod AB::copiere(PNod p) const {
    if (p != nullptr)
    {
        PNod pNew = new Nod(p->e, nullptr, nullptr);
        pNew->st = copiere(p->st);
        pNew->dr = copiere(p->dr);
        return pNew;
    }
    return nullptr;
}
//teta(n)
void AB::distruge(PNod p) {
    if (p != nullptr)
    {
        distruge(p->st);
        distruge(p->dr);
        delete p;
    }
}
//teta(1)
AB::AB() {
	/* de adaugat */
    this->rad = nullptr;
}
//teta(n)
AB::AB(const AB& ab) {
	/* de adaugat */
    this->rad = copiere(ab.rad);
}
//teta(1)
AB::AB(TElem e){
	/* de adaugat */
    this->rad = new Nod(e, nullptr, nullptr);
}
//teta(n)
AB::AB(const AB& st, TElem e, const AB& dr){
    /* de adaugat */
    this->rad = new Nod(e, copiere(st.rad), copiere(dr.rad));
}

//teta(n)
void AB::adaugaSubSt(const AB& st){
 	/* de adaugat */
     if (vid())
         throw std::exception();
    distruge(rad->st);
    rad->st = copiere(st.rad);
}

//teta(n)
void AB::adaugaSubDr(const AB& dr){
	/* de adaugat */
    if (vid())
        throw std::exception();
    distruge(rad->dr);
    rad->dr = copiere(dr.rad);
}

//teta(1)
TElem AB::element() const{
 	/* de adaugat */
	if (vid())
        throw std::exception();
    return rad->e;
}
//teta(n)
AB AB::stang() const{
 	/* de adaugat */
     if (vid())
         throw std::exception();
     AB ab;
     ab.rad = copiere(rad->st);
    return ab;
}
//teta(n)
AB AB::drept() const{
	/* de adaugat */
	if (vid())
        throw std::exception();
    AB ab;
    ab.rad = copiere(rad->dr);
    return ab;
}
//teta(n)
AB::~AB() {
	/* de adaugat */
    distruge(rad);
}
//teta(1)
bool AB::vid() const{
	/* de adaugat */
	if (rad == nullptr)
        return true;
    return false;
}


IteratorAB* AB::iterator(string s) const {
	if (s=="preordine")
		return new IteratorPreordine(*this);
	if (s=="inordine")
		return new IteratorInordine(*this);
	if (s=="postordine")
		return new IteratorPostordine(*this);
	if (s=="latime")
		return new IteratorLatime(*this);
	return nullptr;
}

