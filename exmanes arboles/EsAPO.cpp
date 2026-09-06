#include <iostream>
#include "abin.h"
#include <cmath>
#include <algorithm>

using namespace std;

template <typename T>
bool esCompleto(const Abin<T>& A)
{
    if (A.vacio())
        return true;

    Cola<typename Abin<T>::nodo> c;
    bool nuloPrevio = false;

    c.push(A.raiz());

    while (!c.vacia())
    {
        typename Abin<T>::nodo actual = c.frente();
        c.pop();

        if (actual == Abin<T>::NODO_NULO)
        {
            nuloPrevio = true;
        }
        else
        {
            if (nuloPrevio)
                return false;

            c.push(A.hijoIzqdo(actual));
            c.push(A.hijoDrcho(actual));
        }
    }

    return true;
}

template <typename T>
bool ordenAPO(const Abin<T>& A,
              typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return true;

    typename Abin<T>::nodo hi = A.hijoIzqdo(n);
    typename Abin<T>::nodo hd = A.hijoDrcho(n);

    if (hi != Abin<T>::NODO_NULO && A.elemento(hi) < A.elemento(n))
        return false;

    if (hd != Abin<T>::NODO_NULO && A.elemento(hd) < A.elemento(n))
        return false;

    return ordenAPO(A, hi) && ordenAPO(A, hd);
}

template <typename T>
bool esAPO(const Abin<T>& A)
{
    if (A.vacio())
        return true;

    return esCompleto(A) && ordenAPO(A, A.raiz());
}