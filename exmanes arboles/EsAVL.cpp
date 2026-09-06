#include <iostream>
#include "abin.h"
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
bool esAVLRec(const Abin<T>& A,
              typename Abin<T>::nodo n,
              const T* min,
              const T* max,
              int& altura)
{
    if (n == Abin<T>::NODO_NULO)
    {
        altura = -1;
        return true;
    }

    T e = A.elemento(n);

    if ((min != nullptr && e <= *min) ||
        (max != nullptr && e >= *max))
    {
        return false;
    }

    int alturaIzq;
    int alturaDer;

    bool izq = esAVLRec(A, A.hijoIzqdo(n), min, &e, alturaIzq);

    bool der = esAVLRec(A, A.hijoDrcho(n), &e, max, alturaDer);

    altura = 1 + max(alturaIzq, alturaDer);

    return izq && der && abs(alturaIzq - alturaDer) <= 1;
}

template <typename T>
bool esAVL(const Abin<T>& A)
{
    if (A.vacio())
        return true;

    int altura = 0;

    return esAVLRec(A,A.raiz(),nullptr,nullptr,altura);
}