#include <iostream>
#include "abin.h"

template <typename T>
bool reflejo(const Abin<T>& A, typename Abin<T>::nodo n1, typename Abin<T>::nodo n2)
{
    if (n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;

    if (n1 == Abin<T>::NODO_NULO || n2 == Abin<T>::NODO_NULO)
        return false;

    return A.elemento(n1) == A.elemento(n2) && reflejo(A, A.hijoIzqdo(n1), A.hijoDrcho(n2)) && reflejo(A, A.hijoDrcho(n1), A.hijoIzqdo(n2));
}
template <typename T>
size_t ArbolReflejadoRec(const Abin<T>& A,
                         typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;

    size_t suma = 0;

    typename Abin<T>::nodo hi = A.hijoIzqdo(n);
    typename Abin<T>::nodo hd = A.hijoDrcho(n);

    if (hi != Abin<T>::NODO_NULO && hd != Abin<T>::NODO_NULO && reflejo(A, hi, hd))
    {
        suma = 1;
    }

    return suma + ArbolReflejadoRec(A, hi) + ArbolReflejadoRec(A, hd);
}

size_t ArbolReflejado(const Abin<T>& A){
    if(A.vacio()){
        return 0;
    }

    return ArbolReflejadoRec(A, A.raiz());
}

