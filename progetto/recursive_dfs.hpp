#pragma once
#include "unidirected_graph.hpp"
#include <map>

template <typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& src) {
    unidirected_graph<T> tree;
    std::map<T, bool> visited;
    
    for (const T& node : G.all_nodes()) {
        visited[node] = false;
    }

    auto dfs_visit = [&](auto& self, const T& u) -> void {
        visited[u] = true;
        for (const T& v : G.neighours(u)) {
            if (!visited[v]) {
                tree.add_edge(u, v);
                self(self, v);
            }
        }
    };

    dfs_visit(dfs_visit, src);
    return tree;
}