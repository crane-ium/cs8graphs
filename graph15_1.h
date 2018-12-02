#ifndef GRAPH15_1_H
#define GRAPH15_1_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <cassert>


/**
 * @brief 15-1: class that uses graph theory
 * graph class is most simple
 */
template<class T>
class simple_graph{
public:
    //CTOR
    simple_graph(bool directed=false)
        : __directed(directed), __edges(nullptr),
          __items(nullptr), __vertices(0), __capacity(0){}
    ~simple_graph();
    //MEMBER FUNCS
    void add_vertex(const T& label);
    void add_edge(std::size_t v1, std::size_t v2);
    T& operator[](std::size_t index);
    void print() const;
    bool resize(std::size_t new_size);
protected:
    static const std::size_t __growth=100; //amount the array grows by
    bool __directed;
    //edges represent a nxn matrix where if there is an edge between two vertices
    //  i and j, then __edges[i][j] is true
    bool** __edges;
    T* __items;
    std::size_t __vertices, __capacity; //# of vertices, capacity of arrays
};

template<class T>
simple_graph<T>::~simple_graph(){
    if(__edges != nullptr)
    for(std::size_t i = 0; i < __capacity; i++){
        delete[] __edges[i];
    }
    delete[] __items;
}

template<class T>
void simple_graph<T>::print() const{
    for(std::size_t i = 0; i < __vertices; i++){
        for(std::size_t j = 0; j < __vertices; j++){
            std::cout << __edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


template<class T>
void simple_graph<T>::add_edge(std::size_t v1, std::size_t v2){
    if(v1 < __vertices && v2 < __vertices){
        __edges[v1][v2] = true;
        if(!__directed)
            __edges[v2][v1] = true;
    }
}

template<class T>
void simple_graph<T>::add_vertex(const T &label){
    __vertices++;
    if(__vertices > __capacity){
        //Increase the size of the arrays and copy over the previous data
        resize(__capacity+__growth);
    }

    //Add into the data
    __items[__vertices-1] = label;
    for(std::size_t i = 0; i < __vertices-1; i++){
        __edges[i][__vertices-1] = false;
    }
    for(std::size_t i = 0; i < __vertices; i++){
        __edges[__vertices-1][i] = false;
    }

    //CODE FOR VECTORS
//    __items.push_back(label);
//    for(std::size_t i = 0; i < __vertices-1; i++){
//        __edges[i].push_back(false);
//    }
//    for(std::size_t i = 0; i < __vertices; i++){
//        __edges.push_back(std::vector<bool>());
//        __edges[__vertices-1].push_back(false);
//    }
}

template<class T>
T& simple_graph<T>::operator [](std::size_t index){
    if(index < __vertices)
        return __items[index];
    else{
        assert(false);
    }
}
template<class T>
bool simple_graph<T>::resize(std::size_t new_size){
    if(__capacity > new_size) //CURRENTLY, don't let them do this
        return false;
    __capacity = new_size;

    bool** temp = new bool*[__capacity];
    for(std::size_t i = 0; i < __capacity; i++){
        temp[i] = new bool[__capacity];
    }
    for(std::size_t i = 0; i < __vertices-1; i++){
        for(std::size_t j = 0; j < __vertices-1; j++){
            temp[i][j] = __edges[i][j];
        }
        delete[] __edges[i];
        __edges[i] = temp[i];
    }
    delete[] __edges;
    __edges = temp;

    T* templ = new T[__capacity];
    for(std::size_t i = 0; i < __vertices-1; i++){
        templ[i] = __items[i];
    }
    delete[] __items;
    __items = templ;
    return true;
}

#endif // GRAPH15_1_H0
