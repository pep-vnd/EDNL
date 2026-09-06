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
void hundirRec(Abin<T>& A,
               typename Abin<T>::nodo n,
               const T& e)
{
    if (n == Abin<T>::NODO_NULO)
        return;

    typename Abin<T>::nodo hi = A.hijoIzqdo(n);
    typename Abin<T>::nodo hd = A.hijoDrcho(n);

    if (hi == Abin<T>::NODO_NULO &&
        hd == Abin<T>::NODO_NULO)
    {
        return;
    }

    typename Abin<T>::nodo menor;

    if (hi == Abin<T>::NODO_NULO)
    {
        menor = hd;
    }
    else if (hd == Abin<T>::NODO_NULO)
    {
        menor = hi;
    }
    else
    {
        if (A.elemento(hi) <= A.elemento(hd))
            menor = hi;
        else
            menor = hd;
    }

    if (A.elemento(n) <= A.elemento(menor))
        return;

    T aux = A.elemento(menor);

    A.elemento(n) = aux;
    A.elemento(menor) = e;

    hundirRec(A, menor, e);
}


template <typename T>
void hundir(Abin<T>& A, const T& e)
{
    if (!A.vacio())
    {
        typename Abin<T>::nodo n = Abin<T>::NODO_NULO;

        Buscar(A, A.raiz(), e, n);

        if (n != Abin<T>::NODO_NULO)
            hundirRec(A, n, e);
    }
}