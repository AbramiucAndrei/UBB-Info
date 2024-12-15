#include "AB.h"
#include "IteratorAB.h"
#include <exception>
#include <string>

Nod::Nod(TElem e, PNod st, PNod dr) {
    this->e = e;
    this->st = st;
    this->dr = dr;
}

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

void AB::distruge(PNod p) {
    if (p != nullptr)
    {
        distruge(p->st);
        distruge(p->dr);
        delete p;
    }
}

AB::AB() {
	/* de adaugat */
    this->rad = nullptr;
}

AB::AB(const AB& ab) {
	/* de adaugat */
    this->rad = copiere(ab.rad);
}

AB::AB(TElem e){
	/* de adaugat */
    this->rad = new Nod(e, nullptr, nullptr);
}

AB::AB(const AB& st, TElem e, const AB& dr){
    /* de adaugat */
    this->rad = new Nod(e, copiere(st.rad), copiere(dr.rad));
}


void AB::adaugaSubSt(const AB& st){
 	/* de adaugat */
     if (vid())
         throw std::exception();
    distruge(rad->st);
    rad->st = copiere(st.rad);
}

void AB::adaugaSubDr(const AB& dr){
	/* de adaugat */
    if (vid())
        throw std::exception();
    distruge(rad->dr);
    rad->dr = copiere(dr.rad);
}

TElem AB::element() const{
 	/* de adaugat */
	if (vid())
        throw std::exception();
    return rad->e;
}

AB AB::stang() const{
 	/* de adaugat */
     if (vid())
         throw std::exception();
     AB ab;
     ab.rad = copiere(rad->st);
    return ab;
}

AB AB::drept() const{
	/* de adaugat */
	if (vid())
        throw std::exception();
    AB ab;
    ab.rad = copiere(rad->dr);
    return ab;
}

AB::~AB() {
	/* de adaugat */
    distruge(rad);
}

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

