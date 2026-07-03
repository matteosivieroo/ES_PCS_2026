#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class unidirected_edge {
private:
    T m_from;
    T m_to;
public:
    unidirected_edge(const T& u, const T& v) {
        if (u < v) { m_from = u; m_to = v; } 
        else { m_from = v; m_to = u; }
    }
    
    T from() const { return m_from; }
    T to() const { return m_to; }
    
    bool operator<(const unidirected_edge& other) const {
        if (m_from != other.m_from) return m_from < other.m_from;
        return m_to < other.m_to;
    }
    
    bool operator==(const unidirected_edge& other) const {
        return m_from == other.m_from && m_to == other.m_to;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const unidirected_edge& e) {
        os << "{" << e.m_from << ", " << e.m_to << "}";
        return os;
    }
};