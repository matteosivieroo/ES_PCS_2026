#include <iostream>
#include <fstream>
#include <string>
#include "unidirected_graph.hpp"
#include "graph.hpp"

//file DOT
template <typename T>
void to_dot(const unidirected_graph<T>& g, const std::string& filename) {
    std::ofstream file(filename);
    file << "graph G {\n";
    for (const auto& e : g.all_edges()) {
        file << "  " << e.from() << " -- " << e.to() << ";\n";
    }
    file << "}\n";
    std::cout << "File DOT generato con successo: " << filename << "\n\n\n";
}

int main() {
    //grafo di esempio non pesato
    unidirected_graph<int> G;
    G.add_edge(unidirected_edge<int>(1, 2)); 
    G.add_edge(unidirected_edge<int>(1, 3));
    G.add_edge(unidirected_edge<int>(1, 4));
    G.add_edge(unidirected_edge<int>(1, 6));
    G.add_edge(unidirected_edge<int>(2, 4));
    G.add_edge(unidirected_edge<int>(2, 5));
    G.add_edge(unidirected_edge<int>(2, 7));
    G.add_edge(unidirected_edge<int>(3, 6));
    G.add_edge(unidirected_edge<int>(4, 6));
    G.add_edge(unidirected_edge<int>(4, 7));
    G.add_edge(unidirected_edge<int>(5, 7));
    G.add_edge(unidirected_edge<int>(6, 7));
    G.add_edge(unidirected_edge<int>(6, 8));
    G.add_edge(unidirected_edge<int>(7, 9));
    G.add_edge(unidirected_edge<int>(8, 9));
    
    std::cout << "Grafo originale\n" << G << "\n";
    to_dot(G, "original.dot");
    
    //BFS (visita in ampiezza) (FIFO)
    std::cout << "BFS (ampiezza da nodo 1)\n";
    fifo<int> q;
    auto bfsG = graph_visit(G, 1, q); 
	std::cout << bfsG << "\n";
    to_dot(bfsG, "bfs.dot");

    //DFS iterativa (visita in profondità) (LIFO)
    std::cout << "DFS iterativa (profondità da nodo 1)\n";
    lifo<int> s;
    auto dfsG = graph_visit(G, 1, s); 
	std::cout << dfsG << "\n";
    to_dot(dfsG, "dfs.dot");
    
    //DFS ricorsiva
    std::cout << "DFS ricorsiva (da nodo 1)\n";
    auto rdfsG = recursive_dfs(G, 1); 
	std::cout << rdfsG << "\n";
    to_dot(rdfsG, "dfs_recursive.dot");
    
    //Dijkstra
    std::cout << "Dijkstra (cammini minimi da nodo 1)\n";
    std::map<int, int> dist;
    std::map<int, int> pred;

    dijkstra(G, 1, dist, pred);  
    for (const auto& d : dist) {
        if (d.second == -1) { 
            std::cout << "Nodo: " << d.first << " -> Non raggiungibile \n"; 
        } else {
            std::cout << "Nodo: " << d.first 
                      << " Distanza: " << d.second
                      << " Predecessore: " << pred[d.first]
                      << "\n";
        }
    }
    
    //grafo dei cammini minimi
    unidirected_graph<int> dijkstraG;
    for (const auto& p : pred) {
        int v = p.first;
        int prec = p.second;
        if (v != prec) { 
            dijkstraG.add_edge(unidirected_edge<int>(prec, v)); 
        }
    }
    to_dot(dijkstraG, "dijkstra.dot");
    
    return 0;
}