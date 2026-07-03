#pragma once
#include "unidirected_graph.hpp"
#include <map>
#include <queue>
#include <vector>
#include <limits>
#include <algorithm>

inline std::vector<int> dijkstra_percorso(const unidirected_graph<int>& G_primo, int nodo_sorgente, int nodo_destinazione) {
    std::map<int, int> dist;
    std::map<int, int> parent; 
    const int INF = std::numeric_limits<int>::max();
    
    for (int nodo : G_primo.all_nodes()) dist[nodo] = INF;

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    dist[nodo_sorgente] = 0;
    pq.push({0, nodo_sorgente});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        
        if (d > dist[u]) continue;
        if (u == nodo_destinazione) break;

        for (int v : G_primo.neighours(u)) {
            int peso = 1; 
            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                parent[v] = u; 
                pq.push({dist[v], v});
            }
        }
    }

    std::vector<int> percorso;
    if (dist[nodo_destinazione] == INF) return percorso; 
    
    int corrente = nodo_destinazione;
    while (corrente != nodo_sorgente) {
        percorso.push_back(corrente);
        corrente = parent[corrente];
    }
    percorso.push_back(nodo_sorgente);
    std::reverse(percorso.begin(), percorso.end());
    return percorso;
}

inline std::vector<int> trova_ciclo_minimo(const unidirected_graph<int>& G_originale, const unidirected_graph<int>& G_primo, int offset) {
    std::vector<int> ciclo_migliore;
    size_t lunghezza_minima = std::numeric_limits<size_t>::max();
    for (int v : G_originale.all_nodes()) {
        int v_pos = v;
        int v_neg = v + offset;
        std::vector<int> percorso_attuale = dijkstra_percorso(G_primo, v_pos, v_neg);

        if (!percorso_attuale.empty() && percorso_attuale.size() < lunghezza_minima) {
            lunghezza_minima = percorso_attuale.size();
            ciclo_migliore = percorso_attuale;
        }
    }

    std::vector<int> ciclo_originale;
    for (int nodo_sdoppiato : ciclo_migliore) {
        if (nodo_sdoppiato > offset) {
            ciclo_originale.push_back(nodo_sdoppiato - offset); 
        } else {
            ciclo_originale.push_back(nodo_sdoppiato); 
        }
    }
    return ciclo_originale;
}