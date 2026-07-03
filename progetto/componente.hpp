#pragma once
#include <string>

//struttura dati per rappresentare un componente del circuito
struct Componente {
    char tipo;             //memorizza carattere 'R' per resistori, 'V' per generatori
    std::string sigla;     
    double valore;         //valore in Ohm o Volt
    int n1;                //nodo di partenza
    int n2;                //nodo di arrivo
    bool verso_positivo;   
};