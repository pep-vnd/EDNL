#include <vector>
#include "grafoPMC.h"

using namespace std;

template <typename tCoste>
struct Carretera
{
    typename GrafoP<tCoste>::vertice origen;
    typename GrafoP<tCoste>::vertice destino;
};

template <typename tCoste>
typename GrafoP<tCoste>::matriz
CiudadesRebeldes(
    const GrafoP<tCoste>& G,
    const vector<typename GrafoP<tCoste>::vertice>& rebeldes,
    const vector<Carretera<tCoste>>& cortadas,
    typename GrafoP<tCoste>::vertice capital)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t n = G.numVert();

    GrafoP<tCoste> Z = G;

    for (size_t k = 0; k < rebeldes.size(); ++k)
    {
        vertice r = rebeldes[k];

        for (vertice i = 0; i < n; ++i)
        {
            Z[r][i] = GrafoP<tCoste>::INFINITO;
            Z[i][r] = GrafoP<tCoste>::INFINITO;
        }
    }

    for (size_t k = 0; k < cortadas.size(); ++k)
        Z[cortadas[k].origen][cortadas[k].destino] =
            GrafoP<tCoste>::INFINITO;

    vector<vertice> P1, P2;

    vector<tCoste> desdeCapital =
        Dijkstra(Z, capital, P1);

    vector<tCoste> hastaCapital =
        DijkstraInv(Z, capital, P2);

    typename GrafoP<tCoste>::matriz M(n);

    for (vertice i = 0; i < n; ++i)
    {
        for (vertice j = 0; j < n; ++j)
        {
            M[i][j] =
                suma(hastaCapital[i], desdeCapital[j]);
        }
    }

    return M;
}
