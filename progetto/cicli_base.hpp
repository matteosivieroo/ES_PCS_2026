#pragma once
#include <vector>
#include <map>
#include "unidirected_graph.hpp"

inline bool trova_percorso(const unidirected_graph<int>& T, int u, int v,
                    std::map<int, bool>& visitato, std::vector<int>& percorso) {
    visitato[u] = true;
    percorso.push_back(u);      
    if (u == v) return true;

    for (int vicino : T.neighours(u)) {
        if (!visitato[vicino]) {
            if (trova_percorso(T, vicino, v, visitato, percorso)) return true;
        }
    }
    percorso.pop_back();
    return false;
}

inline std::vector<std::vector<int>> trova_maglie_base(
    const unidirected_graph<int>& albero,
    const unidirected_graph<int>& coalbero)
{
    std::vector<std::vector<int>> maglie_trovate;
    
    for (const auto& arco : coalbero.all_edges()) {
        int u = arco.from();
        int v = arco.to();
        
        std::map<int, bool> visitato;
        for (int nodo : albero.all_nodes()) visitato[nodo] = false;
        
        std::vector<int> percorso_ciclo;
        if (trova_percorso(albero, u, v, visitato, percorso_ciclo)) {
            maglie_trovate.push_back(percorso_ciclo);
        }
    }
    return maglie_trovate;
}