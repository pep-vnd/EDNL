#include <iostream>
#include "TAD AGen/Agen_vec.h"

template <typename T>
size_t Multiplosde3Rec(const Agen<T>& A, typename Agen<T>::nodo nodo, size_t& total)
{
    if (nodo == Agen<T>::NODO_NULO)
        return 0;

    size_t multiplos = 0;

    typename Agen<T>::nodo h = A.hijoIzqdo(nodo);

    while (h != Agen<T>::NODO_NULO)
    {
        total++;

        if (A.elemento(h) % 3 == 0)
            multiplos++;

        multiplos += Multiplosde3Rec(A, h, total);

        h = A.hermDrcho(h);
    }

    return multiplos;
}

template <typename T>
double Multiplosde3(const Agen<T>& A)
{
    if (A.vacio())
        return 0.0;

    size_t total = 0;

    size_t multiplos =
        Multiplosde3Rec(A, A.raiz(), total);

    if (total == 0)
        return 0.0;

    return 100.0 * multiplos / total;
}