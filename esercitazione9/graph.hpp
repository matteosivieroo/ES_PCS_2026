#pragma once 
#include "containers.hpp"
#include "unidirected_graph.hpp"
#include <set>
#include <map> 
#include <queue> //per priority_queue 

// BFS/DFS iterativa
template<typename T, typename container>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& G, const T& n, container& c) {
    unidirected_graph<T> tree; //inizializza albero vuoto
    std::set<T> visited; //traccia i nodi già visitati
    
    visited.insert(n); //segno sorgente come già visitata
    c.put(n); //e la inserisco nel contenitore
    
    while(!c.empty()) {
        T u = c.get(); //estrae il nodo
        
        for (const auto& v : G.neighbours(u)) {
            if (visited.find(v) == visited.end()) { //controllo se il vicino è già stato visitato	
                visited.insert(v); //segno come visitato
                c.put(v); //inserisco nel contenitore
                tree.add_edge(unidirected_edge<T>(u, v)); //creo l'arco e lo aggiungo all'albero
            }
        }
    } 
    return tree;
}

//DFS RICORSIVA
template <typename T> 
void dfs_visit(const unidirected_graph<T>& G, const T& n, std::set<T>& visited, unidirected_graph<T>& result) {
    visited.insert(n); //segno il nodo corrente come visitato
    
    for (const auto& v : G.neighbours(n)) { //controllo i vicini
        if (visited.find(v) == visited.end()) {
            result.add_edge(unidirected_edge<T>(n, v)); //aggiungo l'arco all'albero
            dfs_visit(G, v, visited, result); //richiamo il DFS sul vicino
        }
    } 
}

template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& node) {
    unidirected_graph<T> result; 
    std::set<T> visited;
    
    dfs_visit(G, node, visited, result); //chiamata ricorsiva
    return result;
}

// DIJKSTRA
template <typename T>
struct nodo_pq {
    T nodo;
    int distanza;
    
    //per estrarre prima il nodo a distanza minore
    bool operator>(const nodo_pq& other) const {
        return distanza > other.distanza; //se verificato restituisce true
    }
};

template <typename T>
void dijkstra(const unidirected_graph<T>& G, const T& s, std::map<T, int>& dist, std::map<T, T>& pred) {
    for (const auto& node: G.all_nodes()) {
        pred[node] = node; 
        dist[node] = -1; 
    }
    
    pred[s] = s;
    dist[s] = 0;
    
    //{tipo di dato, contenitore sottostante, comparazione(greater)}
    std::priority_queue<nodo_pq<T>, std::vector<nodo_pq<T>>, std::greater<nodo_pq<T>>> pq;
    pq.push({s, 0});
    
    while(!pq.empty()) {
        nodo_pq<T> attuale = pq.top(); //legge l'elemento con distanza minima
        pq.pop(); //e lo rimuove
        
        T u = attuale.nodo;
        int d = attuale.distanza;
        
        //ignoriamo nodi "vecchi" rimasti in coda se abbiamo già trovato un percorso più breve verso di loro
        if (d > dist[u]) { continue; }
        
        for (const auto& w : G.neighbours(u)) {
            //controlla se non è mai stato visitato (-1) o se abbiamo trovato un percorso migliore
            if (dist[w] == -1 || dist[w] > dist[u] + 1) {
                dist[w] = dist[u] + 1;
                pred[w] = u;
                pq.push({w, dist[w]});
            }
        }
    }
}