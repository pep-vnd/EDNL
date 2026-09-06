#include "/home/pep/Projects/EDNL/Guía para aprobar EDNL/TADs/TAD Abin/Abin_celdas_enlz.h"

#include <iostream>

using namespace std;

template <typename T>
void Buscar(const Abin<T>& A,
            typename Abin<T>::nodo n,
            const T& e,
            typename Abin<T>::nodo& encontrado)
{
    if (n == Abin<T>::NODO_NULO)
        return;

    if (A.elemento(n) == e)
    {
        encontrado = n;
        return;
    }

    Buscar(A, A.hijoIzqdo(n), e, encontrado);

    if (encontrado == Abin<T>::NODO_NULO)
        Buscar(A, A.hijoDrcho(n), e, encontrado);
}

template <typename T>
void FlotarNodoRec(Abin<T>& A,
            typename Abin<T>::nodo n,
            const T& e)
{
    if (n == A.raiz() || A.elemento(A.padre(n)) <= e)
        return;
    else{
        T aux = A.elemento(A.padre(n));
        A.elemento(A.padre(n)) = e;
        A.elemento(n) = aux;
        FlotarNodoRec(A, A.padre(n), e);
    }
}

template <typename T>
void FlotarNodo(Abin<T>& A, const T& e){
    if(!A.vacio()){
        typename Abin<T>::nodo n = Abin<T>::NODO_NULO;
        
        Buscar(A, A.raiz(), e, n);
        if (n != Abin<T>::NODO_NULO)
            FlotarNodoRec(A, n, e);
    }
}


