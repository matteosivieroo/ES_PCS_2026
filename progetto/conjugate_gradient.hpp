#pragma once
#include <Eigen/Dense>
#include <utility>

inline std::pair<Eigen::VectorXd, int> conjugate_gradient(
    const Eigen::MatrixXd& A,
    const Eigen::VectorXd& b,
    Eigen::VectorXd x0,
    double tol,
    int max_it)
{
    Eigen::VectorXd x = x0;
    Eigen::VectorXd r = b - A * x;
    Eigen::VectorXd p = r;
    double r0_norm = r.norm();
    int k = 0;

    while (k < max_it && r.norm() > tol * r0_norm) {
        Eigen::VectorXd Ap = A * p;
        double pAp = p.transpose() * Ap;
        double alpha = (p.transpose() * r).value() / pAp;
        
        x = x + alpha * p;
        r = b - A * x;
        
        double beta = (p.transpose() * (A * r)).value() / pAp;
        p = r - beta * p;
        k++;
    }
    return {x, k};
}
