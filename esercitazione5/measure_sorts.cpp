#include <iostream>
#include <vector>
#include <algorithm>
#include "sorts.hpp" 
#include "randfiller.h"
#include "timecounter.h"
#include <iomanip>

int main() {
    randfiller rf;
    timecounter tc;
    
    const int num_tests = 100;

    std::cout << "dimensione\tbubble\t\tinsertion\tselection\tmerge\t\tquick\t\thybrid_quick\tstd::sort\n";
    std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

    for (int k = 4; k <= 8192; k *= 2) {         
        std::vector<std::vector<int>> base_arrays(num_tests, std::vector<int>(k));
        for (int i = 0; i < num_tests; i++) {
            rf.fill(base_arrays[i], -10000, 10000); 
        }

        std::vector<std::vector<int>> v_bubble = base_arrays; 
        std::vector<std::vector<int>> v_insertion = base_arrays; 
        std::vector<std::vector<int>> v_selection = base_arrays; 
        std::vector<std::vector<int>> v_merge = base_arrays;
        std::vector<std::vector<int>> v_quick = base_arrays;
        std::vector<std::vector<int>> v_hybrid = base_arrays;
        std::vector<std::vector<int>> v_std = base_arrays; 
        
        //BUBBLE SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            bubble_sort(v_bubble[i]);
        }
        double t_bubble = tc.toc()/num_tests; //media

        //INSERTION SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            insertion_sort(v_insertion[i]);
        }
        double t_insert = tc.toc()/num_tests;

        //SELECTION SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            selection_sort(v_selection[i]);
        }
        double t_select = tc.toc()/num_tests;

        //MERGE SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            merge_sort(v_merge[i]);
        }
        double t_merge = tc.toc()/num_tests;

        //QUICK SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            quick_sort(v_quick[i]);
        }
        double t_quick = tc.toc()/num_tests;

        //HYBRID QUICK SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            hybrid_quicksort(v_hybrid[i]);
        }
        double t_hybrid = tc.toc()/num_tests;

        //STD::SORT
        tc.tic();
        for (int i = 0; i < num_tests; i++) {
            std::sort(v_std[i].begin(), v_std[i].end());
        }
        double t_std = tc.toc()/num_tests;


        std::cout << k << "\t\t" << t_bubble << "\t" << t_insert << "\t" << t_select << "\t" << t_merge << "\t" << t_quick << "\t" << t_hybrid << "\t" << t_std << "\n";
    }
    return 0;
}