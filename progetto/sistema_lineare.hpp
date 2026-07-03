#pragma once
#include <vector>
#include <Eigen/Dense>
#include <algorithm>
#include "componente.hpp"

struct SistemaKirchhoff {
    Eigen::MatrixXd A; 
    Eigen::VectorXd v; 
    Eigen::MatrixXd R; 
    Eigen::MatrixXd B; 
};

inline SistemaKirchhoff costruisci_sistema(const std::vector<Componente>& circuito,
                                    const std::vector<std::vector<int>>& maglie) {
    
    std::vector<Componente> resistori;
    std::vector<Componente> generatori;
    
    for (const Componente& comp : circuito) {
        if (comp.tipo == 'R') resistori.push_back(comp);
        else if (comp.tipo == 'V') generatori.push_back(comp);
    }

    int m = resistori.size();
    int n = maglie.size();

    Eigen::MatrixXd R = Eigen::MatrixXd::Zero(m, m);
    Eigen::MatrixXd B = Eigen::MatrixXd::Zero(m, n);
    Eigen::VectorXd v = Eigen::VectorXd::Zero(n);

    for (int i = 0; i < m; ++i) {
        R(i, i) = resistori[i].valore;
    }

    //Costruiamo B e v
    for (int j = 0; j < n; ++j) {
        const std::vector<int>& ciclo = maglie[j];

        for (size_t k = 0; k < ciclo.size(); ++k) {
            int nodo_partenza = ciclo[k];
            int nodo_arrivo = ciclo[(k + 1) % ciclo.size()];

            for (int i = 0; i < m; ++i) {
                int r_from = std::min(resistori[i].n1, resistori[i].n2);
                int r_to = std::max(resistori[i].n1, resistori[i].n2);

                if (r_from == nodo_partenza && r_to == nodo_arrivo) {
                    B(i, j) = 1;  
                } else if (r_to == nodo_partenza && r_from == nodo_arrivo) {
                    B(i, j) = -1; 
                }
            }

            for (size_t g = 0; g < generatori.size(); ++g) {
                if (generatori[g].n1 == nodo_partenza && generatori[g].n2 == nodo_arrivo) {
                    v(j) -= generatori[g].valore;
                } else if (generatori[g].n1 == nodo_arrivo && generatori[g].n2 == nodo_partenza) {
                    v(j) += generatori[g].valore;
                }
            }
        }
    }

    Eigen::MatrixXd A = B.transpose() * R * B;
    return {A, v, R, B};
}