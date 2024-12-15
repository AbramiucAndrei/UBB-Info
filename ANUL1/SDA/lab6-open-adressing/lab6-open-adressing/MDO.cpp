#include "IteratorMDO.h"
#include "MDO.h"
#include <vector>
#include <cmath>
#include <exception>

using namespace std;
//teta(m)
MDO::MDO(Relatie r)
{
	this->m=maxcap;
    this->r=r;
    this->lg=0;
    this->prim=-1;
    int i;
    for(i=0;i<this->m;i++)
         this->e[i]=null;
}
//teta(1)
int MDO::d(TCheie c, int i) const
{
    int rez=c%this->m + 0*i+pow(-1,i)*i*i;
    return rez%this->m;
}
//O(m)
void MDO::adauga(TCheie c, TValoare v)
{
    int i=0;
    bool done=false;
    TElem x= make_pair(c,v);
    do
    {
       int j=this->d(c,i);
       if((this->e[j]==null||this->e[j]==sters)&&j>=0)
       {
            this->e[j]=x;
            if(this->vid())
                this->prim=j;
            this->lg++;
            done=true;
       }
       else
           i++;
    }while(i<this->m&&!done);
}
//O(m)
vector<TValoare> MDO::cauta(TCheie c) const
{
	vector<TValoare> v;
    if(c>=0)
    {
        int i=0,j;
        do
        {
            j=this->d(c,i);
            if(this->e[j].first==c&&j>=0)
                v.push_back(this->e[j].second);
            i++;
        }while(i<this->m&&this->e[j]!=null);
    }
    return v;
}
//O(m)
bool MDO::sterge(TCheie c, TValoare v)
{
    TElem x=make_pair(c,v);
    int i=0;
    while(i<this->m)
    {
        if(this->e[i]==x)
        {
            this->e[i]=sters;
            this->lg--;
            return true;
        }
        else i++;
    }
    return false;
}
//teta(1)
int MDO::dim() const
{
	return this->lg;
}
//teta(1)
bool MDO::vid() const
{
	return this->lg==0;
}

IteratorMDO MDO::iterator() const
{
	return IteratorMDO(*this);
}

MDO::~MDO() {
	/* de adaugat */
}
//O(m)
int MDO::eliminaAparitiiCheie(int x, TCheie c)
{
    int i = 0;
    int nr_sterse = 0;
    while (i < this->m and nr_sterse<x) {
        if (this->e[i].first == c) {
            this->e[i] = sters;
            this->lg--;
            nr_sterse++;
        }

        i++;
    }
    return nr_sterse;
}

//Subalgoritm eliminaAparitiiCheie(x,c)
//    nr_sterse<-0
//    i<-0
//    cat timp i<dimensiune(dict) si nr_sterse<x executa
//        Daca cheie(dict.e[i]) = c atunci
//            @sterge elementul de pe pozitia i
//            dict.lungime<-dict.lungime-1
//            nr_sterse-<nr_sterse+1
//        Sfdaca
//        i<-i+1
//    SfCatTimp
//
//    eliminaAparitiiCheie<-nr_sterse
//SfSubAlg