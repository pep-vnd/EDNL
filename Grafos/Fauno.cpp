#include <vector>
#include "grafoPMC.h"

using namespace std;

struct Casilla
{
    size_t fila;
    size_t col;
};

size_t casillaANodo(size_t i, size_t j, size_t M)
{
    return i * M + j;
}

template <typename tCoste>
void anularNodo(GrafoP<tCoste>& G,
                typename GrafoP<tCoste>::vertice v)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    for (vertice i = 0; i < G.numVert(); ++i)
    {
        G[v][i] = GrafoP<tCoste>::INFINITO;
        G[i][v] = GrafoP<tCoste>::INFINITO;
    }
}

template <typename tCoste>
tCoste MatrizFauno(size_t N,
                   size_t M,
                   const vector<Casilla>& trampas,
                   const vector<Casilla>& caballeros,
                   bool& posible)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t total = N * M;
    GrafoP<tCoste> G(total);

    const int df[8] = {-2,-2,-1,-1,1,1,2,2};
    const int dc[8] = {-1,1,-2,2,-2,2,-1,1};

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < M; ++j)
        {
            vertice u = casillaANodo(i, j, M);

            for (int k = 0; k < 8; ++k)
            {
                int ni = static_cast<int>(i) + df[k];
                int nj = static_cast<int>(j) + dc[k];

                if (ni >= 0 && ni < static_cast<int>(N) &&
                    nj >= 0 && nj < static_cast<int>(M))
                {
                    vertice v =
                        casillaANodo(ni, nj, M);

                    G[u][v] = 1;
                }
            }
        }
    }

    for (size_t k = 0; k < trampas.size(); ++k)
    {
        vertice v =
            casillaANodo(trampas[k].fila,
                         trampas[k].col,
                         M);

        anularNodo(G, v);
    }

    const int alrededorF[8] = {-1,-1,-1,0,0,1,1,1};
    const int alrededorC[8] = {-1,0,1,-1,1,-1,0,1};

    for (size_t k = 0; k < caballeros.size(); ++k)
    {
        int f = static_cast<int>(caballeros[k].fila);
        int c = static_cast<int>(caballeros[k].col);

        for (int d = 0; d < 8; ++d)
        {
            int ni = f + alrededorF[d];
            int nj = c + alrededorC[d];

            if (ni >= 0 && ni < static_cast<int>(N) &&
                nj >= 0 && nj < static_cast<int>(M))
            {
                vertice v =
                    casillaANodo(ni, nj, M);

                anularNodo(G, v);
            }
        }
    }

    vertice origen = casillaANodo(0, 0, M);
    vertice destino = casillaANodo(N - 1, M - 1, M);

    vector<vertice> P;
    vector<tCoste> D = Dijkstra(G, origen, P);

    if (D[destino] == GrafoP<tCoste>::INFINITO)
    {
        posible = false;
        return GrafoP<tCoste>::INFINITO;
    }

    posible = true;
    return D[destino];
}
