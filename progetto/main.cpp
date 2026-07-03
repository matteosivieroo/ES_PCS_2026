#include <iostream>
#include <vector>
#include <string>
#include <Eigen/Dense>

#include "componente.hpp"
#include "lettore_netlist.hpp"
#include "unidirected_graph.hpp"
#include "recursive_dfs.hpp"
#include "cicli_base.hpp"
#include "de_pina.hpp"
#include "sistema_lineare.hpp"
#include "conjugate_gradient.hpp"

unidirected_graph<int> costruisci_grafo(const std::vector<Componente>& circuito) {
    unidirected_graph<int> G;
    for (const Componente& comp : circuito) {
        G.add_edge(comp.n1, comp.n2); // unidirected_edge ordinerà automaticamente
    }
    return G;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        std::cerr << "Errore: file netlist non specificato.\n";
        std::cerr << "Uso: ./risolutore_circuiti <nome_file.txt>\n";
        return 1;
    }

    std::string nome_file = argv[1];

    std::cout << "Lettura del circuito da: " << nome_file << "...\n";
    std::vector<Componente> circuito = leggi_netlist(nome_file);

    if (circuito.empty()) {
        std::cerr << "Il circuito è vuoto o c'è stato un errore di lettura.\n";
        return 1;
    }

    unidirected_graph<int> G = costruisci_grafo(circuito);
    std::cout << "Grafo costruito: " << G.all_nodes().size() << " nodi, "
              << G.all_edges().size() << " archi.\n";

    int nodo_sorgente = *(G.all_nodes().begin());
    
    //DFS
    unidirected_graph<int> albero = recursive_dfs(G, nodo_sorgente);
    unidirected_graph<int> coalbero = G - albero;
    std::vector<std::vector<int>> maglie_base = trova_maglie_base(albero, coalbero);

    //De Pina
    std::vector<std::vector<int>> maglie_minime = algoritmo_de_pina(G, coalbero);
    SistemaKirchhoff sys = costruisci_sistema(circuito, maglie_minime);

    double tolleranza = 1e-10;
    int max_iterazioni = 1000;
    Eigen::VectorXd correnti_iniziali = Eigen::VectorXd::Zero(sys.A.cols());

    auto risultato_cg = conjugate_gradient(sys.A, sys.v, correnti_iniziali, tolleranza, max_iterazioni);
    Eigen::VectorXd correnti_di_maglia = risultato_cg.first;
    

    Eigen::VectorXd correnti_resistori = sys.B * correnti_di_maglia;
    Eigen::VectorXd tensioni_resistori = sys.R * correnti_resistori;

    std::cout << "Risultati finali:\n";
    int indice_matrice = 0; 
    for (const Componente& comp : circuito) {
        if (comp.tipo == 'R') {
            std::cout << comp.tipo << comp.sigla << ": "
                      << "V = " << tensioni_resistori(indice_matrice) << " volts, "
                      << "I = " << correnti_resistori(indice_matrice) << " amps.\n";
            indice_matrice++; 
        }
    }

    return 0;
}