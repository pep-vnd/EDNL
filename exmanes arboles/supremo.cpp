#include <string>
#include "abb.h"

using namespace std;

template <typename T>
T supremoRec(const Abb<T>& A,
             const T& x,
             const T& candidato)
{
    if (A.vacio())
        return candidato;

    if (A.elemento() == x)
        return x;

    if (A.elemento() > x)
        return supremoRec(A.izqdo(), x, A.elemento());
    else
        return supremoRec(A.drcho(), x, candidato);
}

template <typename T>
T maximo(const Abb<T>& A)
{
    if (A.drcho().vacio())
        return A.elemento();

    return maximo(A.drcho());
}

template <typename T>
T supremo(const Abb<T>& A, const T& x)
{
    return supremoRec(A, x, maximo(A));
}