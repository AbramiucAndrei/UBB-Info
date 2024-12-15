#include <iostream>
#include "AB.h"
#include "IteratorAB.h"

// Complexitate: O(n)
IteratorInordine::IteratorInordine(const AB& _ab):ab(_ab) {
	/* de adaugat */
    curent = nullptr;
    IteratorInordine::prim();
}

// Complexitate: O(n)
void IteratorInordine::prim(){
	/* de adaugat */
    golireStiva(s);
    if (ab.rad != nullptr)
    {
        curent = ab.rad;
        while (curent != nullptr) {
            s.push(curent);
            curent = curent->st;
        }
        if (!s.empty())
            curent = s.top();
    }
}

// Complexitate: O(1)
bool IteratorInordine::valid(){
	/* de adaugat */
	return curent != nullptr;
}

// Complexitate: O(1)
TElem IteratorInordine::element() {
	/* de adaugat */
    if (! valid() )
        throw std::exception();
	return curent->e;
}

// Complexitate: O(n)
void IteratorInordine::urmator(){
	/* de adaugat */
    if (! valid() )
        throw std::exception();
    s.pop();
    if (curent->dr != nullptr)
    {
        curent = curent->dr;
        while (curent != nullptr)
        {
            s.push(curent);
            curent = curent->st;
        }
    }
    if (! s.empty() )
        curent = s.top();
    else
        curent = nullptr;
}

// Complexitate: O(n)
void IteratorInordine::golireStiva(stack<PNod> &s)  {
    while (! s.empty() )
        s.pop();
}


// Complexitate: O(n)
void IteratorPreordine::revinoKPasi(int k) {
    stack<PNod> tempStack;
    PNod previous = nullptr;
    PNod current = nullptr;

    tempStack.push(ab.rad);

    while (!tempStack.empty()) {
        previous = current;
        current = tempStack.top();
        tempStack.pop();

        if (current == curent) {
            if (k <= 0) return;

            for (int i = 0; i < k && previous != nullptr; ++i) {
                curent = previous;
                tempStack = s;
                while (!tempStack.empty()) {
                    PNod node = tempStack.top();
                    tempStack.pop();
                    if (node == previous) break;
                    if (node->dr != nullptr) tempStack.push(node->dr);
                    if (node->st != nullptr) tempStack.push(node->st);
                }
                previous = nullptr;
            }

            if (curent == ab.rad) {
                throw std::exception();
            }

            return;
        }

        if (current->dr != nullptr) tempStack.push(current->dr);
        if (current->st != nullptr) tempStack.push(current->st);
    }

    throw std::exception();
}

// Complexitate: O(n)
IteratorPreordine::IteratorPreordine(const AB& _ab):ab(_ab){
	/* de adaugat */
    curent = nullptr;
    IteratorPreordine::prim();
}

// Complexitate: O(n)
void IteratorPreordine::prim(){
 	/* de adaugat */
    golireStiva(s);
    if (ab.rad != nullptr)
    {
        s.push(ab.rad);
        curent = s.top();
    }
}

// Complexitate: O(1)
bool IteratorPreordine::valid(){
	/* de adaugat */
    return curent != nullptr;
}

// Complexitate: O(1)
TElem IteratorPreordine::element(){
	/* de adaugat */
    if (! valid() )
        throw std::exception();
	return curent->e;
}


// Complexitate: O(n)
void IteratorPreordine::urmator(){
	/* de adaugat */
    if (! valid() )
        throw std::exception();
    s.pop();
    if (curent->dr != nullptr)
        s.push(curent->dr);
    if (curent->st != nullptr)
        s.push(curent->st);
    if (! s.empty() )
        curent = s.top();
    else
        curent = nullptr;
}

// Complexitate: O(n)
void IteratorPreordine::golireStiva(stack<PNod>& s) {
    while (! s.empty() )
        s.pop();
}

// Complexitate: O(n)
IteratorPostordine::IteratorPostordine(const AB& _ab):ab(_ab){
	/* de adaugat */
    curent = nullptr;
    IteratorPostordine::prim();
}

// Complexitate: O(n)
void IteratorPostordine::prim(){
	/* de adaugat */
    golireStiva(s);
    if (ab.rad != nullptr)
    {
        curent = ab.rad;
        int k = 1;
        while (curent != nullptr) {
            s.push(NodPostordine{curent, 0});
            curent = curent->st;
        }
        if (!s.empty())
            curent = s.top().p, k = s.top().k;
        while (k == 0) {
            s.pop();
            s.push(NodPostordine{curent, 1});
            if (curent->dr != nullptr) {
                curent = curent->dr;
                while (curent != nullptr) {
                    s.push({curent, 0});
                    curent = curent->st;
                }
            }
            if (!s.empty())
                curent = s.top().p, k = s.top().k;
        }
    }
}

// Complexitate: O(1)
bool IteratorPostordine::valid(){
	/* de adaugat */
	return curent != nullptr;
}

// Complexitate: O(1)
TElem IteratorPostordine::element(){
 	/* de adaugat */
    if (! valid() )
        throw std::exception();
    return curent->e;
}

// Complexitate: O(n)
void IteratorPostordine::urmator(){
	/* de adaugat */
    if (! valid() )
        throw std::exception();
    s.pop();
    int k;
    if ( s.empty() )
        curent = nullptr;
    else
    {
        k = s.top().k;
        curent = s.top().p;
    }
    while (curent != nullptr && k == 0)
    {
        //curent = s.top().p, k = s.top().k;
        s.pop();
        s.push(NodPostordine{curent, 1});
        if (curent->dr != nullptr)
        {
            curent = curent->dr;
            while (curent != nullptr) {
                s.push({curent, 0});
                curent = curent->st;
            }
        }
        if ( ! s.empty() )
            curent = s.top().p, k = s.top().k;
    }
}

// Complexitate: O(n)
void IteratorPostordine::golireStiva(stack<NodPostordine> &s) {
    while (! s.empty() )
        s.pop();
}

// Complexitate: O(n)
IteratorLatime::IteratorLatime(const AB& _ab):ab(_ab){
	/* de adaugat */
    curent = nullptr;
    IteratorLatime::prim();
}

// Complexitate: O(n)
void IteratorLatime::prim(){
	/* de adaugat */
    golireCoada(q);
    if (ab.rad != nullptr)
    {
        q.push(ab.rad);
        curent = q.front();
    }
}


// Complexitate: O(1)
bool IteratorLatime::valid(){
	/* de adaugat */
    return curent != nullptr;
}

// Complexitate: O(1)
TElem IteratorLatime::element(){
	/* de adaugat */
	if (! valid())
        throw std::exception();
    return curent->e;
}

// Complexitate: O(n)
void IteratorLatime::urmator(){
	/* de adaugat */
    if (! valid())
        throw std::exception();
    q.pop();
    if (curent->st != nullptr)
        q.push(curent->st);
    if (curent->dr != nullptr)
        q.push(curent->dr);
    if ( ! q.empty() )
        curent = q.front();
    else
        curent = nullptr;
}

// Complexitate: O(n)
void IteratorLatime::golireCoada(queue<PNod> &q) {
    while (! q.empty() )
        q.pop();
}




