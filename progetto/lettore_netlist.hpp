#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "componente.hpp"

std::vector<Componente> leggi_netlist(const std::string& nome_file) {
    std::vector<Componente> circuito;
    std::ifstream ifs(nome_file);
    
    if ( !ifs.is_open() ) {
        std::cerr << "Errore: impossibile aprire il file " << nome_file << "\n";
        return circuito; 
    }

    char tipo;
    std::string sigla;
    double valore;
    int n1, n2;

    while (ifs >> tipo >> sigla >> valore >> n1 >> n2) {
        bool verso = (n1 < n2);
        Componente comp = {tipo, sigla, valore, n1, n2, verso};
        circuito.push_back(comp);
    }

    if ( ifs.fail() && !ifs.eof() ) {
        std::cerr << "Errore durante la lettura: formato del file non valido.\n";
    }

    return circuito;
}