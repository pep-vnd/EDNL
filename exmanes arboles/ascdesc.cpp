#include <iostream>
#include "abin.h"

using namespace std;

template <typename T>
bool Descendiente(const Abin<T>& A, typename Abin<T>::nodo n, const T& e)
{
    if (n == Abin<T>::NODO_NULO)
        return true;

    if (A.elemento(n) < e)
        return false;

    return Descendiente(A, A.hijoIzqdo(n), e) && Descendiente(A, A.hijoDrcho(n), e);
}

template <typename T>
bool Ascendiente(const Abin<T>& A,
                 typename Abin<T>::nodo n,
                 const T& e)
{
    if (n == A.raiz())
        return true;

    typename Abin<T>::nodo p = A.padre(n);

    if (A.elemento(p) > e)
        return false;

    return Ascendiente(A, p, e);
}

template <typename T>
void eliminarSubarbol(Abin<T>& A, typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return;

    typename Abin<T>::nodo hi = A.hijoIzqdo(n);
    typename Abin<T>::nodo hd = A.hijoDrcho(n);

    eliminarSubarbol(A, hi);
    eliminarSubarbol(A, hd);

    if (n != A.raiz())
    {
        typename Abin<T>::nodo p = A.padre(n);

        if (A.hijoIzqdo(p) == n)
            A.eliminarHijoIzqdo(p);
        else
            A.eliminarHijoDrcho(p);
    }
}

template <typename T>
void AscDescRec(Abin<T>& A, typename Abin<T>::nodo n){
    if(Ascendiente(A, n, A.elemento(n)) && Descendiente(A, n, A.elemento(n)))
        eliminar(A, n);
    AscDescRec(A, A.hijoIzqdo(n));
    AscDescRec(A, A.hijoDrcho(n));
}

template <typename T>
void AscDesc(Abin<T>& A){
    if(!A.vacio())
        AscDescRec(A, A.raiz());

}