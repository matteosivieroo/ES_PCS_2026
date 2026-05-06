#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "sorts.hpp"
#include "randfiller.h"

int main() {
    randfiller rf;

    std::vector<int> dimensioni(100);
    rf.fill(dimensioni, 1, 200);
    
    //test su 100 vettori casuali
    for (int i = 0; i < 100; i++) {
        std::vector<int> v(dimensioni[i]);
        rf.fill(v, -500, 500); 
        
        quick_sort(v); 
        
        if (!is_sorted(v)) { 
            std::cerr << "Errore: il vettore numero " << i << " non è ordinato.\n";
            return EXIT_FAILURE;
        }
    }
    
    //test stringhe
    std::vector<std::string> s = {
        "lorem","ipsum","dolor","sit","amet","consectetur","adipiscing","elit","sed","do"
    };
    quick_sort(s);  
    if (!is_sorted(s)) {
        std::cerr << "Errore: il vettore di stringhe non è ordinato.\n";
        return EXIT_FAILURE;
    }
    
    std::cout << "Quick sort: test superati con successo.\n";
    return EXIT_SUCCESS;
}