#include <iostream>
#include <vector>
#include <algorithm> // Necessario per std::sort

#include "sort_algorithms.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main() {
    randfiller rf;
    timecounter tc;

    std::cout << "dimensione \t bubblesort[s] \t insertionsort[s] \t selectionsort[s] \t std::sort[s]\n"; 

    for (int k = 4; k <= 8192; k *= 2) { 
        
        std::vector<int> vec(k);
        rf.fill(vec, -10000, 10000); 

        std::vector<int> v_bubble = vec; 
        std::vector<int> v_insert = vec; 
        std::vector<int> v_select = vec; 
        std::vector<int> v_std    = vec; 
        
        // bubble sort
        tc.tic();
        bubblesort(v_bubble);
        double t_bubble = tc.toc();

        // insertion sort
        tc.tic();
        insertionsort(v_insert);
        double t_insert = tc.toc();

        // selection sort
        tc.tic();
        selectionsort(v_select);
        double t_select = tc.toc();

        // libreria standard (std::sort)
        tc.tic();
        std::sort(v_std.begin(), v_std.end());
        double t_std = tc.toc();


        std::cout << "\t" << k << "\t" << t_bubble << "\t" << t_insert << "\t" << "\t" << t_select << "\t" << "\t" << t_std << "\n";
    }

    return 0;
}