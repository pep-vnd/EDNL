
#include <iostream>
#include "abin.h"

template <typename T>
size_t numNietos(const Abin<T>& A, typename Abin<T>::nodo n)
{
    size_t cont = 0;

    typename Abin<T>::nodo hi = A.hijoIzqdo(n);
    typename Abin<T>::nodo hd = A.hijoDrcho(n);

    if (hi != Abin<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(hi) != Abin<T>::NODO_NULO)
            cont++;

        if (A.hijoDrcho(hi) != Abin<T>::NODO_NULO)
            cont++;
    }

    if (hd != Abin<T>::NODO_NULO)
    {
        if (A.hijoIzqdo(hd) != Abin<T>::NODO_NULO)
            cont++;

        if (A.hijoDrcho(hd) != Abin<T>::NODO_NULO)
            cont++;
    }

    return cont;
}

template <typename T>
size_t contarTresNietosRec(const Abin<T>& A,
                           typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;

    size_t suma = 0;

    if (numNietos(A, n) == 3)
        suma = 1;

    return suma + contarTresNietosRec(A, A.hijoIzqdo(n)) + contarTresNietosRec(A, A.hijoDrcho(n));
}

template <typename T>
size_t TresNietos(const Abin<T>& A)
{
    if (A.vacio())
        return 0;

    return contarTresNietosRec(A, A.raiz());
}