#include <iostream>
#include <Eigen/Dense>
#include "cg.hpp"

using namespace std;

int main() {
    const double tol = 1e-12;

    //test su matrice simmetrica e definita positiva
    Eigen::MatrixXd A1(3, 3); //matrice 3x3
    A1 << 4.0, 1.0, 0.0,
          1.0, 3.0, 1.0,
          0.0, 1.0, 2.0;

    Eigen::VectorXd b1(3);
    b1 << 5.0, 5.0, 3.0; //definisco il vettore dei termini noti in modo da avere il vettore unitario come soluzione
    Eigen::VectorXd x_esatta = Eigen::VectorXd::Ones(3);
    Eigen::VectorXd x0 = Eigen::VectorXd::Zero(3); //vettore iniziale

    auto sol1 = cg(A1, b1, x0, tol);

    if (sol1.has_value()) {
        double errore_rel = (sol1.value() - x_esatta).norm() / x_esatta.norm();
        cout << "Soluzione calcolata:\n" << sol1.value() << "\n";
        cout << "Errore relativo: " << scientific << errore_rel << "\n";
    } else {
        cout << "Errore: l'algoritmo ha fallito.\n";
    }
    cout << "\n";


    //test matrice non simmetrica
    Eigen::MatrixXd A2 = A1;
    A2(0,1) = 15.0; //modifico la matrice A1 per avere matrice A2 non simmetrica

    auto sol2 = cg(A2, b1, x0, tol);
    if (!sol2.has_value()) {
        cout << "La matrice non simmetrica è stata correttamente rifiutata.\n";
    } else {
        cout << "Errore: è stata accettata una matrice non simmetrica\n";
    }
    cout << "\n";

    //test matrice non definita positiva
    Eigen::MatrixXd A3 = A1;
    A3(0, 0) = -5.0; //inserendo un elemento negativo sulla diagonale rompo la def. positività

    auto sol3 = cg(A3, b1, x0, tol);
    if (!sol3.has_value()) {
        cout << "La matrice non definita positiva è stata correttamente rifiutata.\n";
    } else {
        cout << "Errore: è stata accettata una matrice non definita positiva\n";
    }
    return EXIT_SUCCESS;
}