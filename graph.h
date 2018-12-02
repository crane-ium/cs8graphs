#ifndef GRAPH_H
#define GRAPH_H

#include <cstdlib>
#include <vector>
#include <iostream>


/**
 * @brief class that uses graph theory
 * graph class is most simple
 */
template<class T>
class graph{
public:
    //CTOR
    graph(bool directed=false)
        : __directed(directed), __vertices(0), __capacity(0){}
    ~graph();
    //MEMBER FUNCS
    void add_vertex(const T& label);
    void add_edge(std::size_t v1, std::size_t v2);
    T& operator[](std::size_t index);
    void print() const;
private:
    static const std::size_t __growth=10; //amount the array grows by
    bool __directed;
    //edges represent a nxn matrix where if there is an edge between two vertices
    //  i and j, then __edges[i][j] is true
    std::vector<std::vector<bool> > __edges;
    std::vector<T> __items;
    std::size_t __vertices, __capacity; //# of vertices, capacity of arrays
};

template<class T>
graph<T>::~graph(){
//    for(std::size_t i = 0; i < __capacity; i++){
//        delete[] __edges[i];
//    }
//    delete[] __items;
}

template<class T>
void graph<T>::print() const{
    for(std::size_t i = 0; i < __vertices; i++){
        for(std::size_t j = 0; j < __vertices; j++){
            std::cout << __edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


template<class T>
void graph<T>::add_edge(std::size_t v1, std::size_t v2){
    if(v1 < __vertices && v2 < __vertices){
        __edges[v1][v2] = true;
        if(!__directed)
            __edges[v2][v1] = true;
    }
}

template<class T>
void graph<T>::add_vertex(const T &label){
    __vertices++;
    __items.push_back(label);
    for(std::size_t i = 0; i < __vertices-1; i++){
        __edges[i].push_back(false);
    }
    for(std::size_t i = 0; i < __vertices; i++){
        __edges.push_back(std::vector<bool>());
        __edges[__vertices-1].push_back(false);
    }
}

template<class T>
T& graph<T>::operator [](std::size_t index){
    if(index < __vertices)
        return __items[index];
    else{
        T empty = T();
        return empty;
    }

}

#endif // GRAPH_H
