//Problem 15-3 from the database textbook
//Give label names for edges too
#ifndef GRAPH15_3_H
#define GRAPH15_3_H

#include "graph15_1.h"

template<class T>
class graph_edge_labels : public simple_graph<T>{
public:
    //CTORS
    graph_edge_labels(bool directed=false)
        : simple_graph<T>(directed), __edges(nullptr){}
    ~graph_edge_labels();
    //MEMBER FUNCS
    //Add an edge with an associated label
    void add_vertex(const T& label);
    void add_edge(std::size_t v1, std::size_t v2, const T& edge_label);
    T& get_edge(std::size_t v1, std::size_t v2); //return label
    bool resize(std::size_t new_size);
    void print() const;
    std::size_t size()const;
private:
    using simple_graph<T>::resize;
    using simple_graph<T>::add_vertex;
    using simple_graph<T>::add_edge; //make the old function private
    T** __edges; //Recreate it, but now it stores labels
};

template<class T>
graph_edge_labels<T>::~graph_edge_labels(){
    for(std::size_t i = 0; i < this->__capacity; i++){
        delete[] __edges[i];
    }
    delete[] __edges;
//    delete[] this->__items;
}
template<class T>
void graph_edge_labels<T>::add_edge(std::size_t v1, std::size_t v2, const T &edge_label){
    if(v1 < this->__vertices && v2 < this->__vertices){
        __edges[v1][v2] = edge_label;
        if(!this->__directed)
            __edges[v2][v1] = edge_label;
    }
}
template<class T>
void graph_edge_labels<T>::print() const{
    for(std::size_t i = 0; i < this->__vertices; i++){
        for(std::size_t j = 0; j < this->__vertices; j++){
            std::cout << (__edges[i][j] != T() ? 1 : 0) << " ";
        }
        std::cout << std::endl;
    }
}
template<class T>
void graph_edge_labels<T>::add_vertex(const T &label){
    this->__vertices++;
    if(this->__vertices > this->__capacity)
        resize(this->__capacity+this->__growth);

    //Add the vertex
    this->__items[this->__vertices-1] = label;
    for(std::size_t i = 0; i < this->__vertices-1; i++){
        __edges[i][this->__vertices-1] = T();
    }
    for(std::size_t i = 0; i < this->__vertices-1; i++){
        __edges[this->__vertices-1][i] = T();
    }
}
template<class T>
bool graph_edge_labels<T>::resize(std::size_t new_size){
    if(this->__capacity > new_size)
        return false;

    this->__capacity = new_size;

    T** temp = new T*[this->__capacity];
    for(std::size_t i = 0; i < this->__capacity; i++){
        temp[i] = new T[this->__capacity];
    }
    for(std::size_t i = 0; i < this->__vertices-1; i++){
        for(std::size_t j = 0; j < this->__vertices-1; j++){
            temp[i][j] = __edges[i][j];
        }
        delete[] __edges[i];
        __edges[i] = temp[i];
    }
    delete[] __edges;
    __edges = temp;

    T* templ = new T[this->__capacity];
    for(std::size_t i = 0; i < this->__vertices-1; i++){
        templ[i] = this->__items[i];
    }
    delete[] this->__items;
    this->__items = templ;
    return true;
}
template<class T>
T& graph_edge_labels<T>::get_edge(std::size_t v1, std::size_t v2){
    if(v1 < this->__vertices && v2 < this->__vertices){
        return __edges[v1][v2];
    }else{
        assert(false);
    }

}
template<class T>
std::size_t graph_edge_labels<T>::size()const{
    return this->__vertices;
}

#endif // GRAPH15_3_H
