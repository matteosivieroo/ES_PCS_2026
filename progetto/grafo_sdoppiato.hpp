#pragma once
#include "unidirected_graph.hpp"
#include <vector>

inline unidirected_graph<int> costruisci_grafo_sdoppiato(
    const unidirected_graph<int>& G,
    const std::vector<int>& archi_attivi_Si)
{
    unidirected_graph<int> G_primo; 
    int max_nodo = 0;
    for (int nodo : G.all_nodes()) {
        if (nodo > max_nodo) max_nodo = nodo;
    }
    int offset = max_nodo + 1;

    for (const auto& arco : G.all_edges()) {
        int u = arco.from();
        int v = arco.to();

        int u_pos = u;
        int u_neg = u + offset;
        int v_pos = v;
        int v_neg = v + offset;

        if (archi_attivi_Si[G.edge_number(arco)] == 1) {
            G_primo.add_edge(u_pos, v_neg);
            G_primo.add_edge(u_neg, v_pos);
        } else {
            G_primo.add_edge(u_pos, v_pos);
            G_primo.add_edge(u_neg, v_neg);
        }
    }
    return G_primo;
}