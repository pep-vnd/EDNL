#include <iostream>
#include "TAD AGen/Agen_vec.h"

using namespace std;

template <typename T>
bool esSimilarRec(const Agen<T>& A,typename Agen<T>::nodo nA, const Agen<T>& B, typename Agen<T>::nodo nB){

    while(nA != Agen<T>::NODO_NULO && nN != Agen<T>::NODO_NULO){
        if(A.elemento(nA) != B.elemento(nB))
            return false;
        if(!esSimilarRec(A, A.hijoIzqdo(nA), B, B.hijoIzqdo(nB)))
            return false;
        nA = A.hermDrcho(nA);
        nB = B.hermDrcho(nB);
    }
    if(nA == Agen<T>::NODO_NULO && nB == Agen<T>::NODO_NULO)
        return true;
    return false;

}

template <typename T>
bool esSimilar(const Agen<T>& A, const Agen<T>& B){
    if (A.vacio() && B.vacio())
        return true;
    if (A.vacio() || B.vacio())
        return false;
    return esSimilarRec(A, A.raiz(), B, B.raiz());

}