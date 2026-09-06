
#include <iostream>
#include "abin.h"

template <typename T>
bool esABBRec(const Abin<T>& A,
              typename Abin<T>::nodo n,
              const T* min,
              const T* max)
{
    if (n == Abin<T>::NODO_NULO)
        return true;

    T e = A.elemento(n);

    if ((min != nullptr && e <= *min) ||
        (max != nullptr && e >= *max))
        return false;

    return esABBRec(A, A.hijoIzqdo(n), min, &e) &&
           esABBRec(A, A.hijoDrcho(n), &e, max);
}


template <typename T>
bool esABB(const Abin<T>& A)
{
    if (A.vacio())
        return true;

    return esABBRec(A, A.raiz(), nullptr, nullptr);
}