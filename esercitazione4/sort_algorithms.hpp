#pragma once
#include <vector>
#include <algorithm> 

//funzione is_sorted
template <typename T>
bool is_sorted(const std::vector<T>& vec) {
    if (vec.size() < 2) {    //un vettore con zero elementi o un elemento è ordinato
        return true;
    }
    
    // controlliamo che ogni elemento sia minore o uguale al successivo.
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

// bubble sort
template <typename T>
void bubblesort(std::vector<T>& vec) {
    size_t n = vec.size();
    if (n < 2) return;

    // L'indice i rappresenta gli elementi già sistemati all'inizio
    for (size_t i = 0; i < n-1; i++) {
        // Il ciclo interno parte dal fondo e arriva fino a i+1.
        // Si confrontano A[j] e A[j-1].
        for (size_t j = n-1; j>i; j--) {
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
            }
        }
    }
}

// insertion sort
template <typename T>
void insertionsort(std::vector<T>& vec) {
    size_t n = vec.size();
    if (n < 2) return;

    for (size_t j = 1; j < n; j++) {
        T key = vec[j];
        int i = static_cast<int>(j) - 1; 
        
        while (i >= 0 && vec[i] > key) {
            vec[i+1] = vec[i];
            i--;
        }
        vec[i+1] = key;
    }
}

// selection sort

template <typename T>
void selectionsort(std::vector<T>& vec) {
    size_t n = vec.size();
    if (n < 2) return;

    for (size_t i = 0; i < n-1; i++) {
        size_t min_index = i;
        for (size_t j = i+1; j < n; j++) {
            if (vec[j] < vec[min_index]) {
                min_index = j;
            }
        }

        if (min_index != i) { 
            std::swap(vec[i], vec[min_index]);
        }
    }
}