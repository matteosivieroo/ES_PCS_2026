#pragma once
#include <queue>  //per FIFO (BFS)
#include <stack>  //per LIFO (DFS)

//adapter per la coda (first in first out)
template<typename T>
class fifo {
private:
    std::queue<T> q;
    
public:
    fifo() = default;
    
    void put(const T& x) { //inserisce un elemento in fondo alla coda
        q.push(x); 
    }
    
    T get() {  //rimuove e restituisce il primo elemento inserito
        T x = q.front();
        q.pop();
        return x; 
    }
        
    bool empty() const {  //verifica se il contenitore è vuoto
        return q.empty(); 
    }
};

//adapter per la pila (last in first out)
template<typename T>
class lifo {
private: 
    std::stack<T> s;
    
public:
    lifo() = default;
    
    void put(const T& x) { //inserisce un elemento in cima allo stack
        s.push(x); 
    }
    
    
    T get() { //rimuove e restituisce l'ultimo elemento inserito
        T x = s.top();
        s.pop();
        return x; 
    }
        
    bool empty() const {  //verifica se il contenitore è vuoto
        return s.empty(); 
    }
};