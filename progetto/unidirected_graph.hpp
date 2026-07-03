#pragma once
#include "unidirected_edge.hpp"
#include <set>
#include <map>
#include <stdexcept>

template <typename T>
class unidirected_graph {
private:
    std::set<T> m_nodes; //memorizza i nodi
    std::set<unidirected_edge<T>> m_edges; //memorizza gli archi
    std::map<T, std::set<T>> m_adj_list; //lista di adiacenza
    std::map<unidirected_edge<T>, size_t> m_edge_to_id; //converte un arco nel suo indice numerico
    std::map<size_t, unidirected_edge<T>> m_id_to_edge; //viceversa
    size_t m_next_id; //contatore

public:
    unidirected_graph() : m_next_id(0) {}
    unidirected_graph(const unidirected_graph& other) = default;

    void add_edge(const T& u, const T& v) { //metodo per inserire nuovo arco nel grafo
        unidirected_edge<T> edge(u, v);
        if (m_edges.find(edge) == m_edges.end()) { //se restituisce end l'arco non esiste
            m_edges.insert(edge);
            m_nodes.insert(u);
            m_nodes.insert(v);
            m_adj_list[u].insert(v);
            m_adj_list[v].insert(u);
            m_edge_to_id[edge] = m_next_id;
            m_id_to_edge.insert({m_next_id, edge});
            m_next_id++;
        }
    }

    std::set<T> neighours(const T& node) const { //metodo che restituisce i vicini di un nodo
        auto it = m_adj_list.find(node); //it iteratore a una coppia chiave-valore
        if (it != m_adj_list.end()) {
            return it->second; //second per restituire il valore associato alla chiave
        }
        return {};
    }

    std::set<unidirected_edge<T>> all_edges() const { return m_edges; }
    std::set<T> all_nodes() const { return m_nodes; }

    size_t edge_number(const unidirected_edge<T>& edge) const { //metodo per tradurre un arco nel suo id
        auto it = m_edge_to_id.find(edge);
        if (it != m_edge_to_id.end()) {
            return it->second;
        }
        throw std::invalid_argument("Arco non presente nel grafo");
    }

    unidirected_edge<T> edge_at(size_t id) const { //metodo per tradurre in id nell'arco corrispondente
        auto it = m_id_to_edge.find(id);
        if (it != m_id_to_edge.end()) {
            return it->second;
        }
        throw std::out_of_range("ID arco non valido");
    }

    unidirected_graph<T> operator-(const unidirected_graph<T>& other) const { //G-albero = coalbero
        unidirected_graph<T> result;
        for (const auto& edge : m_edges) {
            if (other.m_edges.find(edge) == other.m_edges.end()) {
                result.add_edge(edge.from(), edge.to());
            }
        }
        return result;
    }
};