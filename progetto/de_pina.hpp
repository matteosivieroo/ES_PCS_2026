#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include "unidirected_graph.hpp"
#include "grafo_sdoppiato.hpp"
#include "cammino_minimo.hpp"

inline int prodotto_scalare_z2(const std::vector<int>& v1, const std::vector<int>& v2) {
    int sum = 0;
    for (size_t i = 0; i < v1.size(); ++i) sum += v1[i] * v2[i];
    return sum % 2; 
}

inline std::vector<int> differenza_simmetrica_xor(const std::vector<int>& v1, const std::vector<int>& v2) {
    std::vector<int> risultato(v1.size());
    for (size_t i = 0; i < v1.size(); ++i) {
        risultato[i] = v1[i] ^ v2[i];
    }
    return risultato;
}

inline std::vector<std::vector<int>> algoritmo_de_pina(const unidirected_graph<int>& G,
                                                const unidirected_graph<int>& coalbero) {
    int m = G.all_edges().size();
    int k = coalbero.all_edges().size();

    std::vector<std::vector<int>> S(k, std::vector<int>(m, 0));
    int indice_maglia = 0;
    for (const auto& arco_coalbero : coalbero.all_edges()) {
        int indice_arco_in_G = G.edge_number(arco_coalbero);
        S[indice_maglia][indice_arco_in_G] = 1;
        indice_maglia++;
    }

    std::vector<std::vector<int>> base_cicli_minimi;

    for (int i = 0; i < k; ++i) {
        unidirected_graph<int> G_primo = costruisci_grafo_sdoppiato(G, S[i]);

        int max_nodo = 0;
        for (int nodo : G.all_nodes()) {
            if (nodo > max_nodo) max_nodo = nodo;
        }
        int offset = max_nodo + 1;

        std::vector<int> ciclo_nodi = trova_ciclo_minimo(G, G_primo, offset);
        base_cicli_minimi.push_back(ciclo_nodi);

        if (ciclo_nodi.empty()) {
            std::cerr << "Errore: Impossibile chiudere il ciclo.\n";
            continue;
        }

        std::vector<int> C_i(m, 0);
        for (size_t n = 0; n < ciclo_nodi.size() - 1; ++n) {
            unidirected_edge<int> arco_del_ciclo(ciclo_nodi[n], ciclo_nodi[n+1]);
            int idx = G.edge_number(arco_del_ciclo);
            C_i[idx] ^= 1;
        }

        for (int j = i + 1; j < k; ++j) {
            if (prodotto_scalare_z2(C_i, S[j]) == 1) {
                S[j] = differenza_simmetrica_xor(S[j], S[i]);
            }
        }
    }
    return base_cicli_minimi;
}