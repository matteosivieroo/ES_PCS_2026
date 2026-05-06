#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

template <typename T>
bool is_sorted(const std::vector<T>& vec) {
    if (vec.size() < 2) return true;
    for (size_t i = 0; i < vec.size() - 1; ++i) {
        if (vec[i] > vec[i + 1]) {
            return false;
        }
    }
    return true;
}

// bubble sort
template <typename T>
void bubble_sort(std::vector<T>& vec) {
    size_t n = vec.size();
    if (n < 2) return;

    for (size_t i = 0; i < n-1; i++) {
        for (size_t j = n-1; j>i; j--) {
            if (vec[j] < vec[j-1]) {
                std::swap(vec[j], vec[j-1]);
            }
        }
    }
}

// selection sort
template <typename T>
void selection_sort(std::vector<T>& vec) {
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

// insertion sort
template <typename T>
void insertion_sort(std::vector<T>& vec) {
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

// insertion sort (subarray)
template <typename T>
void insertion_sort_subarray(std::vector<T>& vec, int p, int r) {
    for (int i = p+1; i <= r; ++i) {
        T key = vec[i];
        int j = i-1;
        while (j >= p && vec[j] > key) {
            vec[j+1] = vec[j];
            j--;
        }
        vec[j + 1] = key;
    }
}


// merge sort
template <typename T>
void merge(std::vector<T>& vec, int p, int q, int r) {
    int n1 = q-p+1; //dimensione array dx
    int n2 = r-q; //dimensione array sx

    std::vector<T> L(n1); //array temporaneo sx
    std::vector<T> R(n2); //array temporaneo dx

    for (int i = 0; i < n1; ++i) L[i] = vec[p + i];
    for (int j = 0; j < n2; ++j) R[j] = vec[q + 1 + j];

    int i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    //se un array si è svuotato prima dell'altro
    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

template <typename T>
void merge_sort_recursive(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        int q = p + (r-p)/2; //evita l'overflow rispetto a (p+r)/2
        merge_sort_recursive(vec, p, q);//prima metà
        merge_sort_recursive(vec, q + 1, r);//seconda metà
        merge(vec, p, q, r);//unisco i risultati
    }
}

//per richiamare il metodo passando solo il vettore
template <typename T>
void merge_sort(std::vector<T>& vec) {
    if (vec.size() > 1) {
        merge_sort_recursive(vec, 0, vec.size()-1);
    }
}


// quick sort
template <typename T>
int partition(std::vector<T>& vec, int p, int r) {
    T pivot = vec[r]; //ultimo elemento come pivot
    int i = p-1;

    for (int j = p; j < r; ++j) {
        if (vec[j] <= pivot) {
            i++;
            std::swap(vec[i], vec[j]);
        }
    }
    std::swap(vec[i+1], vec[r]);
    return i+1;
}

template <typename T>
void quicksort_recursive(std::vector<T>& vec, int p, int r) {
    if (p < r) {
        int q = partition(vec, p, r); //q è la posizione esatta in cui è finito il pivot
        quicksort_recursive(vec, p, q - 1); //quicksort a sx del pivot
        quicksort_recursive(vec, q + 1, r); ////quicksort a dx del pivot
    }
}

//per richiamare il metodo passando solo il vettore
template <typename T>
void quick_sort(std::vector<T>& vec) {
    if (vec.size() > 1) {
        quicksort_recursive(vec, 0, vec.size()-1);
    }
}

// hybrid quick sort
template <typename T>
void hybrid_quicksort_recursive(std::vector<T>& vec, int p, int r) {
    const int THRESHOLD = 256; 

    if (r-p+1 <= THRESHOLD) {
        insertion_sort_subarray(vec, p, r);
    } 
    else if (p < r) {
        int q = partition(vec, p, r);
        hybrid_quicksort_recursive(vec, p, q-1);
        hybrid_quicksort_recursive(vec, q+1, r);
    }
}

template <typename T>
void hybrid_quicksort(std::vector<T>& vec) {
    if (vec.size() > 1) {
        hybrid_quicksort_recursive(vec, 0, static_cast<int>(vec.size()-1));
    }
}