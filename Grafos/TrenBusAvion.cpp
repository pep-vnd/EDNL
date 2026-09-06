#include <vector>
#include "grafoPMC.h"

using namespace std;

template <typename tCoste>
tCoste Transporte(
    const GrafoP<tCoste>& tren,
    const GrafoP<tCoste>& bus,
    const GrafoP<tCoste>& avion,
    typename GrafoP<tCoste>::vertice origen,
    typename GrafoP<tCoste>::vertice destino,
    tCoste taxiTrenBus,
    tCoste taxiAeropuerto,
    vector<typename GrafoP<tCoste>::vertice>& camino)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t N = tren.numVert();

    const vertice ORIGEN = 3 * N;
    const vertice DESTINO = 3 * N + 1;

    GrafoP<tCoste> G(3 * N + 2);

    // Tren
    for (vertice i = 0; i < N; ++i)
        for (vertice j = 0; j < N; ++j)
            G[i][j] = tren[i][j];

    // Autobús
    for (vertice i = 0; i < N; ++i)
        for (vertice j = 0; j < N; ++j)
            G[N + i][N + j] = bus[i][j];

    // Avión
    for (vertice i = 0; i < N; ++i)
        for (vertice j = 0; j < N; ++j)
            G[2 * N + i][2 * N + j] = avion[i][j];

    // Cambios de transporte
    for (vertice i = 0; i < N; ++i)
    {
        // tren <-> bus
        G[i][N + i] = taxiTrenBus;
        G[N + i][i] = taxiTrenBus;

        // tren <-> avión
        G[i][2 * N + i] = taxiAeropuerto;
        G[2 * N + i][i] = taxiAeropuerto;

        // bus <-> avión
        G[N + i][2 * N + i] = taxiAeropuerto;
        G[2 * N + i][N + i] = taxiAeropuerto;
    }

    // Desde el origen se puede empezar en cualquier medio
    G[ORIGEN][origen] = 0;
    G[ORIGEN][N + origen] = 0;
    G[ORIGEN][2 * N + origen] = 0;

    // En el destino podemos terminar en cualquier medio
    G[destino][DESTINO] = 0;
    G[N + destino][DESTINO] = 0;
    G[2 * N + destino][DESTINO] = 0;

    vector<vertice> P;

    vector<tCoste> D = Dijkstra(G, ORIGEN, P);

    if (D[DESTINO] == GrafoP<tCoste>::INFINITO)
        return GrafoP<tCoste>::INFINITO;

    // Reconstruir camino
    vector<vertice> inverso;

    vertice v = DESTINO;

    while (v != ORIGEN)
    {
        inverso.push_back(v);
        v = P[v];
    }

    inverso.push_back(ORIGEN);

    camino.clear();

    for (int i = static_cast<int>(inverso.size()) - 1; i >= 0; --i)
        camino.push_back(inverso[i]);

    return D[DESTINO];
}
