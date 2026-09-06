#include <iostream>
#include "TAD AGen/Agen_vec.h"

template <typename T>
size_t GradoRec(const Agen<T>& A,
                typename Agen<T>::nodo nodo,
                size_t& hojas)
{
    if (nodo == Agen<T>::NODO_NULO)
        return 0;

    size_t hijos = 0;
    size_t gradoMaxSubarbol = 0;

    typename Agen<T>::nodo h = A.hijoIzqdo(nodo);

    if (h == Agen<T>::NODO_NULO)
        hojas++;

    while (h != Agen<T>::NODO_NULO)
    {
        hijos++;

        size_t gradoHijo = GradoRec(A, h, hojas);

        if (gradoHijo > gradoMaxSubarbol)
            gradoMaxSubarbol = gradoHijo;

        h = A.hermDrcho(h);
    }

    return std::max(hijos, gradoMaxSubarbol);
}

template <typename T>
double Densidad(const Agen<T>& A)
{
    if (A.vacio())
        return 0.0;

    size_t hojas = 0;

    size_t gradoMax = GradoRec(A, A.raiz(), hojas);

    if (hojas == 0)
        return 0.0;

    return static_cast<double>(gradoMax) / hojas;
}