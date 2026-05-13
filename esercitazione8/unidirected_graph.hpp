#ifndef UNIDIRECTED_GRAPH_HPP
#define UNIDIRECTED_GRAPH_HPP
#include "unidirected_edge.hpp"
#include <set>
#include <list>
#include <map>
#include <unordered_map>
#include <stdexcept>

template <typename T>
class unidirected_graph {
private:
    std::set<T> m_nodes; //memorizza i nodi unici
    std::list<unidirected_edge<T>> m_edges_list; //conserva gli archi nell'ordine in cui vengono inseriti
    std::unordered_map<T, std::set<T>> m_adj_list; //lista di adiacenza
    
    //mappe per la numerazione
    std::map<unidirected_edge<T>, size_t> m_edge_to_id;
    std::unordered_map<size_t, unidirected_edge<T>> m_id_to_edge;
    size_t m_next_id; //contatore che incrementa ad ogni arco inserito assegnanfo un id univoco

public:
    unidirected_graph() : m_next_id(0) {} //costruttore di default (inizializzato a 0)

    unidirected_graph(const unidirected_graph& other) = default; //costruttore di copia

    //aggiunge un arco al grafo
    void add_edge(const unidirected_edge<T>& edge) {
        //se l'arco non esiste già nel grafo, lo inserisco
        if (m_edge_to_id.find(edge) == m_edge_to_id.end()) {
            m_edges_list.push_back(edge);
            
            //registrazione nodi
            m_nodes.insert(edge.from());
            m_nodes.insert(edge.to());
            
            //aggiornamento lista di adiacenza
            m_adj_list[edge.from()].insert(edge.to());
            m_adj_list[edge.to()].insert(edge.from());
            
            //gestione della numerazione
            m_edge_to_id[edge] = m_next_id;
            m_id_to_edge[m_next_id] = edge;
            m_next_id++;
        }
    }

    //restituisce i vicini di un nodo
    std::set<T> neighbours(const T& node) const {
        auto it = m_adj_list.find(node);
        if (it != m_adj_list.end()) {
            return it->second;
        }
        return {}; //se il nodo non esiste o è isolato restituisce un set vuoto
    }

    //restituisce tutti gli archi
    std::list<unidirected_edge<T>> all_edges() const {
        return m_edges_list;
    }

    //restituisce tutti i nodi
    std::set<T> all_nodes() const {
        return m_nodes;
    }

    //restituisce l'id di un arco
    size_t edge_number(const unidirected_edge<T>& edge) const {
        auto it = m_edge_to_id.find(edge);
        if (it != m_edge_to_id.end()) {
            return it->second;
        }
        throw std::invalid_argument("Errore: arco non presente nel grafo.");
    }

    //restituisce l'arco corrispondente a una dato id
    unidirected_edge<T> edge_at(size_t id) const {
        auto it = m_id_to_edge.find(id);
        if (it != m_id_to_edge.end()) {
            return it->second;
        }
        throw std::out_of_range("Errore: ID arco non valido.");
    }

    //operatore differenza
    unidirected_graph<T> operator-(const unidirected_graph<T>& other) const {
        unidirected_graph<T> result;
        for (const auto& edge : m_edges_list) {  //itera su tutti gli archi del grafo corrente (G)
            if (other.m_edge_to_id.find(edge) == other.m_edge_to_id.end()) { //se l'arco non è presente in G' (other), lo aggiunge al risultato
                result.add_edge(edge);
            }
        }
        return result;
    }
};

#endif