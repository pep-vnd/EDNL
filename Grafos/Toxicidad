#include <vector>
#include <algorithm>
#include "grafoPMC.h"

using namespace std;

template <typename tCoste>
typename GrafoP<tCoste>::matriz
Toxicidad(const GrafoP<tCoste>& G,
                typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t n = G.numVert();
    typename GrafoP<tCoste>::matriz A = G;

    for (vertice i = 0; i < n; ++i)
        A[i][i] = 0;

    for (vertice k = 0; k < n; ++k)
    {
        if (k == capital)
            continue;

        for (vertice i = 0; i < n; ++i)
        {
            for (vertice j = 0; j < n; ++j)
            {
                tCoste nuevo = suma(A[i][k], A[k][j]);

                if (nuevo < A[i][j])
                    A[i][j] = nuevo;
            }
        }
    }

    return A;
}
