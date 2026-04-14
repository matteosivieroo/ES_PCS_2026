#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#include "sort_algorithms.hpp"
#include "randfiller.h"

int main() {
    randfiller rf;

    std::vector<int> dimensioni(100);
    rf.fill(dimensioni, 1, 200);
    
    for (int i = 0; i<100; i++) {
        std::vector<int> v(dimensioni[i]);
        rf.fill(v, -500, 500);
        
        bubblesort(v);
        
        if (!is_sorted(v)) { 
            std::cerr << "Errore: il vettore non è ordinato.\n";
            return EXIT_FAILURE;
        }
    }
    
    // test sulle stringhe
    std::vector<std::string> s = {
        "lorem","ipsum","dolor","sit","amet","consectetur","adipiscing","elit","sed","do"
    };
    
    bubblesort(s);
    
    if (!is_sorted(s)) {
        std::cerr << "Errore: il vettore di stringhe non è ordinato\n";
        return EXIT_FAILURE;
    }
    
    std::cout <<  "Bubble sort: tutti i test superati con successo.\n";
    return EXIT_SUCCESS;
}