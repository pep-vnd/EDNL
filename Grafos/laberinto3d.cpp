#include <vector>
#include "grafoPMC.h"

using namespace std;

struct Casilla3D
{
    size_t i, j, k;
};

struct Pared
{
    Casilla3D a;
    Casilla3D b;
};

size_t casillaANodo(size_t i, size_t j, size_t k, size_t N)
{
    return i * N * N + j * N + k;
}

Casilla3D nodoACasilla(size_t v, size_t N)
{
    Casilla3D c;

    c.i = v / (N * N);
    v %= (N * N);
    c.j = v / N;
    c.k = v % N;

    return c;
}

template <typename tCoste>
tCoste Laberinto3D(size_t N,
                   const vector<Pared>& paredes,
                   const Casilla3D& entrada,
                   const Casilla3D& salida,
                   vector<Casilla3D>& camino)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t total = N * N * N;
    GrafoP<tCoste> G(total);

    const int di[6] = {1, -1, 0, 0, 0, 0};
    const int dj[6] = {0, 0, 1, -1, 0, 0};
    const int dk[6] = {0, 0, 0, 0, 1, -1};

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            for (size_t k = 0; k < N; ++k)
            {
                vertice u = casillaANodo(i, j, k, N);

                for (int d = 0; d < 6; ++d)
                {
                    int ni = static_cast<int>(i) + di[d];
                    int nj = static_cast<int>(j) + dj[d];
                    int nk = static_cast<int>(k) + dk[d];

                    if (ni >= 0 && ni < static_cast<int>(N) &&
                        nj >= 0 && nj < static_cast<int>(N) &&
                        nk >= 0 && nk < static_cast<int>(N))
                    {
                        vertice v = casillaANodo(ni, nj, nk, N);
                        G[u][v] = 1;
                    }
                }
            }
        }
    }

    for (size_t p = 0; p < paredes.size(); ++p)
    {
        vertice a = casillaANodo(
            paredes[p].a.i,
            paredes[p].a.j,
            paredes[p].a.k,
            N
        );

        vertice b = casillaANodo(
            paredes[p].b.i,
            paredes[p].b.j,
            paredes[p].b.k,
            N
        );

        G[a][b] = GrafoP<tCoste>::INFINITO;
        G[b][a] = GrafoP<tCoste>::INFINITO;
    }

    vertice origen =
        casillaANodo(entrada.i, entrada.j, entrada.k, N);

    vertice destino =
        casillaANodo(salida.i, salida.j, salida.k, N);

    vector<vertice> P;
    vector<tCoste> D = Dijkstra(G, origen, P);

    if (D[destino] == GrafoP<tCoste>::INFINITO)
        return GrafoP<tCoste>::INFINITO;

    vector<vertice> inverso;

    vertice v = destino;

    while (v != origen)
    {
        inverso.push_back(v);
        v = P[v];
    }

    inverso.push_back(origen);

    camino.clear();

    for (int i = static_cast<int>(inverso.size()) - 1; i >= 0; --i)
        camino.push_back(nodoACasilla(inverso[i], N));

    return D[destino];
}
