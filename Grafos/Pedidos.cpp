#include <vector>
#include "grafoPMC.h"

using namespace std;

template <typename tCoste>
typename GrafoP<tCoste>::vertice
clienteMasCercano(const typename GrafoP<tCoste>::matriz& D,
                  typename GrafoP<tCoste>::vertice actual,
                  typename GrafoP<tCoste>::vertice almacen,
                  const vector<bool>& servido)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    tCoste minimo = GrafoP<tCoste>::INFINITO;
    vertice elegido = D.dimension();

    for (vertice v = 0; v < D.dimension(); ++v)
    {
        if (v != almacen && !servido[v] && D[actual][v] < minimo)
        {
            minimo = D[actual][v];
            elegido = v;
        }
    }

    return elegido;
}

template <typename tCoste>
tCoste repartoBebidas(const GrafoP<tCoste>& G,
                      typename GrafoP<tCoste>::vertice almacen,
                      unsigned capacidad)
{
    typedef typename GrafoP<tCoste>::vertice vertice;

    const size_t n = G.numVert();

    typename GrafoP<tCoste>::matriz D = Floyd(G);

    vector<bool> servido(n, false);
    servido[almacen] = true;

    unsigned pendientes = n - 1;
    unsigned carga = capacidad;

    vertice actual = almacen;
    tCoste distanciaTotal = 0;

    while (pendientes > 0)
    {
        vertice cliente =
            clienteMasCercano<tCoste>(D, actual, almacen, servido);

        distanciaTotal += D[actual][cliente];
        actual = cliente;

        unsigned pedido = Pedido();

        if (carga >= pedido)
        {
            carga -= pedido;
            servido[cliente] = true;
            pendientes--;
        }
        else
        {
            pedido -= carga;
            carga = 0;
        }

        if (carga == 0 && pendientes > 0)
        {
            distanciaTotal += D[actual][almacen];
            actual = almacen;
            carga = capacidad;
        }
    }

    return distanciaTotal;
}
