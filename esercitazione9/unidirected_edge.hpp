#ifndef UNIDIRECTED_EDGE_HPP
#define UNIDIRECTED_EDGE_HPP
#include <iostream>
#include <algorithm>

template <typename T>
class unidirected_edge {
private:
    T m_from;
    T m_to;

public:
    //il costruttore garantisce m_from < m_to
    unidirected_edge(const T& u, const T& v) {
        if (u < v) {
            m_from = u;
            m_to = v;
        } else {
            m_from = v;
            m_to = u;
        }
    }

    //costruttore di default
    unidirected_edge() = default;

    //metodi di accesso -> restituiscono i nodi dell'arco
    T from() const { return m_from; }
    T to() const { return m_to; }


    //operatori di confronto

    //   < rende gli archi ordinabili
    bool operator<(const unidirected_edge& other) const {
        if (m_from != other.m_from) {
            return m_from < other.m_from;
        }
        return m_to < other.m_to;
    }

    //verifica l'uguaglianza tra due archi (due archi sono uguali se i loro membri corrispondenti sono identici)
    bool operator==(const unidirected_edge& other) const {
        return m_from == other.m_from && m_to == other.m_to;
    }

    //overload operatore di output
    friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& e) {
        os << "(" << e.m_from << ", " << e.m_to << ")";
        return os;
    }
};

#endif