#include <iostream>
#include "TAD AGen/Agen_vec.h"

template <typename T>
size_t numHijos(const Agen<T>& A, typename Agen<T>::nodo n)
{
    size_t cont = 0;

    typename Agen<T>::nodo h = A.hijoIzqdo(n);

    while (h != Agen<T>::NODO_NULO)
    {
        cont++;
        h = A.hermDrcho(h);
    }

    return cont;
}

template <typename T>
size_t tresNietosRec(const Agen<T>& A, typename Agen<T>::nodo n)
{
    if (n == Agen<T>::NODO_NULO)
        return 0;

    size_t nietos = 0;

    typename Agen<T>::nodo h = A.hijoIzqdo(n);

    while (h != Agen<T>::NODO_NULO)
    {
        nietos += numHijos(A, h);
        h = A.hermDrcho(h);
    }

    size_t suma = (nietos == 3) ? 1 : 0;

    h = A.hijoIzqdo(n);

    while (h != Agen<T>::NODO_NULO)
    {
        suma += tresNietosRec(A, h);
        h = A.hermDrcho(h);
    }

    return suma;
}

template <typename T>
size_t tresNietos(const Agen<T>& A)
{
    if (A.vacio())
        return 0;

    return tresNietosRec(A, A.raiz());
}