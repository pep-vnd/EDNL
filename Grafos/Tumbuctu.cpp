#include <vector>
#include <cmath>
#include <limits>
#include "grafo.h"

using namespace std;

struct Ciudad
{
    double x, y;
};

struct LineaAerea
{
    size_t ciudad1;
    size_t ciudad2;
    double distancia;
};

double distancia(const Ciudad& a, const Ciudad& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return sqrt(dx * dx + dy * dy);
}

void dfs(const Grafo& G,
         size_t v,
         vector<int>& isla,
         int numIsla)
{
    isla[v] = numIsla;

    for (size_t w = 0; w < G.numVert(); ++w)
    {
        if (G[v][w] && isla[w] == -1)
            dfs(G, w, isla, numIsla);
    }
}

vector<LineaAerea> Tombuctu2(const Grafo& G, const vector<Ciudad>& ciudades)
{
    const size_t N = G.numVert();

    vector<int> isla(N, -1);
    int numIslas = 0;

    for (size_t v = 0; v < N; ++v)
    {
        if (isla[v] == -1)
        {
            dfs(G, v, isla, numIslas);
            numIslas++;
        }
    }

    vector<LineaAerea> lineas;

    for (int a = 0; a < numIslas; ++a)
    {
        for (int b = a + 1; b < numIslas; ++b)
        {
            double minimo = numeric_limits<double>::infinity();

            size_t ciudadA = 0;
            size_t ciudadB = 0;

            for (size_t i = 0; i < N; ++i)
            {
                if (isla[i] == a)
                {
                    for (size_t j = 0; j < N; ++j)
                    {
                        if (isla[j] == b)
                        {
                            double d =
                                distancia(ciudades[i], ciudades[j]);

                            if (d < minimo)
                            {
                                minimo = d;
                                ciudadA = i;
                                ciudadB = j;
                            }
                        }
                    }
                }
            }

            lineas.push_back({ciudadA, ciudadB, minimo});
        }
    }

    return lineas;
}
