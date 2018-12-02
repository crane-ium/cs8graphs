#ifndef GRAPH15_4_H
#define GRAPH15_4_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <set>
#include <queue>

/**
 * @brief 15-4: class that uses graph theory
 * Adds a new function that returns T/F if
 *  there exists a path on graph G from v0, vf of V set
 */
template<class T>
class graph{
public:
    //CTOR
    graph(bool directed=true)
        : __directed(directed), __edges(nullptr),
          __items(nullptr), __vertices(0), __capacity(0){}
    ~graph();
    //MEMBER FUNCS
    void add_vertex(const T& label);
    void add_edge(std::size_t v1, std::size_t v2);
    T& operator[](std::size_t index);
    void print() const;
    bool resize(std::size_t new_size);

    //NEW FUNCTION HERE!!!
    //Returns if there exists a path between v0 to vf
    bool exists_path(std::size_t v0, std::size_t vf);
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
graph<T>::~graph(){
    if(__edges != nullptr)
    for(std::size_t i = 0; i < __capacity; i++){
        delete[] __edges[i];
    }
    delete[] __items;
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
T& graph<T>::operator [](std::size_t index){
    if(index < __vertices)
        return __items[index];
    else{
        T empty = T();
        return empty;
    }

}
template<class T>
bool graph<T>::resize(std::size_t new_size){
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

template<class T>
bool graph<T>::exists_path(std::size_t v0, std::size_t vf){
    //Use set to manage visited vertices
    std::set<std::size_t> visited;
    std::queue<std::size_t> vqueue; //queue of to-visit vertices

    //Breadth-first Search
    vqueue.push(v0);
    while(!vqueue.empty()){
        visited.insert(vqueue.front());
        for(std::size_t i = 0; i < __vertices; i++){
            if(__edges[vqueue.front()][i]){
                if(visited.find(i) == visited.end()){
                    vqueue.push(i);
                    visited.insert(i);
                }
            }
        }
        vqueue.pop();
    }
    //visited.find() returns an iterator to end() if it dne
    if(visited.find(vf) != visited.end())
        return true;
    else
        return false;
}
#endif // GRAPH15_4_H
