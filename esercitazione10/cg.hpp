#pragma once
#include <iostream>
#include <optional>
#include <Eigen/Dense>

std::optional<Eigen::VectorXd> cg(const Eigen::MatrixXd& A, const Eigen::VectorXd& b, const Eigen::VectorXd& x0, const double tol = 1e-12) 
{
    //controllo sulle dimensioni
    if (A.rows() != A.cols()) {
        std::cerr << "Errore: la matrice A non è quadrata \n";
        return std::nullopt;
    }
    if (A.rows() != b.size() || A.rows() != x0.size()) {
        std::cerr << "Errore: dimensioni incompatibili tra A, b e x0.\n";
        return std::nullopt;
    }

    //controllo che la matrice A sia simmetrica
    //con isApprox si tollerano piccoli errori di arrotondamento floating point
    if (!A.isApprox(A.transpose(), 1e-12)) {
        std::cerr << "Errore: la matrice A non è simmetrica.\n";
        return std::nullopt;
    }

    //controllo che la matrice A sia definita positiva
    Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> solver(A); //estrae autovalori e autovettori
    if (solver.eigenvalues().minCoeff() <= 1e-14) { //estrae l'autovalore più piccolo
        std::cerr << "Errore: la matrice A non è definita positiva.\n";
        return std::nullopt;
    }

    //inizializzazione algoritmo gradiente coniugato
    Eigen::VectorXd x = x0; //vettore soluzione
    Eigen::VectorXd r = b - A * x; //residuo iniziale
    Eigen::VectorXd p = r; //direzione di discesa
    
    const double r0_norm = r.norm(); //norma del residuo iniziale
    int k = 0; //contatore iterazioni
    const int k_max = 10 * A.rows(); //tetto massimo iterazioni

    while (k < k_max && r.norm() > tol * r0_norm) 
    {
        Eigen::VectorXd Ap = A*p;
        double alpha_k = p.dot(r)/p.dot(Ap);
        x = x + alpha_k*p; //aggiornamento della soluzione
        
        Eigen::VectorXd r_new = b - A * x;
        
        double beta_k = p.dot(A*r_new)/p.dot(Ap);
        
        p = r_new - beta_k*p; //aggiornamento direzione
        
        //iterazione successiva
        r = r_new;
        k++;
    }

    if (k == k_max) {
        std::cerr << "È stato raggiunto il limite massimo di iterazioni ("<< k_max <<") senza convergenza ottimale.\n";
    }
    return x;
}