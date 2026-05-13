#include <iostream>
#include <stdexcept>
#include "unidirected_graph.hpp"

int main() {
    //test unidirected edge
    unidirected_edge<int> e1(5, 2); //creo l'arco
    std::cout << "Arco e1 stampato: " << e1 << "\n"; //stampo l'arco
    std::cout << "Estremi separati (from, to): " << e1.from() << ", " << e1.to() << "\n\n"; //stampo i nodi singolarmente per verificare l'ordinamento


    //test popolamento grafo
    unidirected_graph<int> G1;
    //inserisco gli archi
    G1.add_edge(unidirected_edge<int>(1, 2));
    G1.add_edge(unidirected_edge<int>(2, 3));
    G1.add_edge(unidirected_edge<int>(3, 1));
    G1.add_edge(unidirected_edge<int>(3, 4));

    //stampa di tutti i nodi
    std::cout << "Nodi presenti in G1: ";
    for (int n : G1.all_nodes()) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    //stampa di tutti gli archi
    std::cout << "Archi presenti in G1: ";
    for (const auto& e : G1.all_edges()) {
        std::cout << e << " ";
    }
    std::cout << "\n\n";


    //test nodi vicini e ricerca indici
    //verifico i vicini del nodo 3
    std::cout << "Vicini del nodo 3: ";
    for (int n : G1.neighbours(3)) {
        std::cout << n << " ";
    }
    std::cout << "\n";

    //creo un arco target
    unidirected_edge<int> target(1, 3); 
    
    //ricerca dell'indice e dell'arco
    size_t id = G1.edge_number(target);
    std::cout << "L'arco target " << target << " si trova all'ID: " << id << "\n";
    std::cout << "Verifica inversa -> l'arco all'ID " << id << " è: " << G1.edge_at(id) << "\n\n";


    //test differenza tra grafi
    unidirected_graph<int> G2;
    //inserisco in G2 alcuni archi presenti in G1
    G2.add_edge(unidirected_edge<int>(1, 2));
    G2.add_edge(unidirected_edge<int>(2, 3));

    std::cout << "Archi presenti in G2: ";
    for (const auto& e : G2.all_edges()) {
        std::cout << e << " ";
    }
    std::cout << "\n";

    //calcolo la differenza
    unidirected_graph<int> G_diff = G1 - G2;
    std::cout << "Archi risultanti da (G1 - G2): ";
    for (const auto& e : G_diff.all_edges()) {
        std::cout << e << " ";
    }
    std::cout << "\n";

    return 0;
}