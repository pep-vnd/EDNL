#include <string>
#include "abb.h"

using namespace std;

template <typename T>
T infimoRec(const Abb<T>& A,
            const T& x,
            const T& candidato)
{
    if (A.vacio())
        return candidato;

    if (A.elemento() == x)
        return x;

    if (A.elemento() < x)
    {
        return infimoRec(A.drcho(), x, A.elemento());
    }
    else
    {
        return infimoRec(A.izqdo(), x, candidato);
    }
}

template <typename T>
T minimo(const Abb<T>& A)
{
    if (A.izqdo().vacio())
        return A.elemento();
    return minimo(A.izqdo());
}

template <typename T>
T infimo(const Abb<T>& A, const T& x)
{
    return infimoRec(A, x, minimo(A));
}