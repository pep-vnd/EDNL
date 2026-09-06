#include <iostream>
#include "TAD AGen/Agen_vec.h"

using namespace std;


template <typename T>
void reflejadoRec(const Agen<T>& A, typename Agen<T>::nodo nA,Agen<T>& B, typename Agen<T>::nodo nB)
{
    typename Agen<T>::nodo hijoA = A.hijoIzqdo(nA);

    while (hijoA != Agen<T>::NODO_NULO)
    {
        B.insertarHijoIzqdo(nB, A.elemento(hijoA));
        typename Agen<T>::nodo hijoB = B.hijoIzqdo(nB);
        reflejadoRec(A, hijoA, B, hijoB);
        hijoA = A.hermDrcho(hijoA);
    }
}


template <typename T>
Agen<T> reflejado(const Agen<T>& A)
{
    Agen<T> B;

    if (!A.vacio())
    {
        B.insertarRaiz(A.elemento(A.raiz()));
        reflejadoRec(A, A.raiz(), B, B.raiz());
    }

    return B;
}