#ifndef GRAPH_WEIGHTED_H
#define GRAPH_WEIGHTED_H


#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip>
#include <set>
#include <queue>
#include <stack>

/**
 * @brief 15-1: class that uses graph theory
 * graph class is most simple
 */
template<class T>
class graph_weighted{
public:
    //CTOR
    graph_weighted(bool directed=false)
        : __directed(directed), __edges(nullptr),
          __items(nullptr), __vertices(0), __capacity(0){}
    ~graph_weighted();
    //MEMBER FUNCS
    void add_vertex(const T& label=T());
    void add_edge(std::size_t v1, std::size_t v2, std::size_t weight);
    void remove_edge(std::size_t v1, std::size_t v2);
    T& operator[](std::size_t index);
    void print() const;
    bool resize(std::size_t new_size);

    //Dijkstra's Algorithms used in shortest_path/distance
    std::stack<std::size_t> shortest_path(std::size_t v0, std::size_t vf); //return shortest path stack
    int shortest_distance(std::size_t v0, std::size_t vf); //return shortest distance
protected:
    static const std::size_t __growth=100; //amount the array grows by
    bool __directed;
    //edges represent a nxn matrix where if there is an edge between two vertices
    //  i and j, then __edges[i][j] is true
    int** __edges;
    T* __items;
    std::size_t __vertices, __capacity; //# of vertices, capacity of arrays
};

template<class T>
graph_weighted<T>::~graph_weighted(){
    if(__edges != nullptr)
    for(std::size_t i = 0; i < __capacity; i++){
        delete[] __edges[i];
    }
    delete[] __items;
}

template<class T>
void graph_weighted<T>::print() const{
    for(std::size_t i = 0; i < __vertices; i++){
        for(std::size_t j = 0; j < __vertices; j++){
            std::cout << std::setw(3) << __edges[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


template<class T>
void graph_weighted<T>::add_edge(std::size_t v1, std::size_t v2, std::size_t weight){
    if(v1 < __vertices && v2 < __vertices){
        __edges[v1][v2] = weight;
        if(!__directed)
            __edges[v2][v1] = weight;
    }
}

template<class T>
void graph_weighted<T>::remove_edge(std::size_t v1, std::size_t v2){
    if(v1 < __vertices && v2 < __vertices && __edges[v1][v2]){
        __edges[v1][v2] = 0;
        if(!__directed)
            __edges[v2][v1] = 0;
    }
}
template<class T>
void graph_weighted<T>::add_vertex(const T &label){
    __vertices++;
    if(__vertices > __capacity){
        //Increase the size of the arrays and copy over the previous data
        resize(__capacity+__growth);
    }

    //Add into the data
    __items[__vertices-1] = label;
    for(std::size_t i = 0; i < __vertices-1; i++){
        __edges[i][__vertices-1] = 0;
    }
    for(std::size_t i = 0; i < __vertices; i++){
        __edges[__vertices-1][i] = 0;
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
T& graph_weighted<T>::operator [](std::size_t index){
    if(index < __vertices)
        return __items[index];
    else{
        T empty = T();
        return empty;
    }

}
template<class T>
bool graph_weighted<T>::resize(std::size_t new_size){
    if(__capacity > new_size) //CURRENTLY, don't let them do this
        return false;
    __capacity = new_size;

    int** temp = new int*[__capacity];
    for(std::size_t i = 0; i < __capacity; i++){
        temp[i] = new int[__capacity];
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
std::stack<std::size_t> graph_weighted<T>::shortest_path(std::size_t v0, std::size_t vf){
    std::set<std::size_t> unvisited;

    //Will display the vertices in the shortest path
    //Shortest path is based on # of vertices traveled
    int distance[__vertices];
    std::size_t previous[__vertices]; //stores the previous vertex
    //initialize distances to infinity
    for(std::size_t i = 0 ; i < __vertices; i++){
        distance[i] = -1;
        previous[i] = -1; //store the vertex at previous[n] to travel to distance[n] at vertex n
        unvisited.insert(i);
    }
    //Setup to begin dijkstra
    distance[v0] = 0;
    std::size_t next = v0;
    bool nochange = false;
    //So if v0 = 0, our distance is: [0, inf, ..., inf];
    while(!unvisited.empty() && !nochange){
        nochange = true;
        unvisited.erase(unvisited.find(next));

        //loop through unvisited, and update the shortest distances
        for(auto it = unvisited.begin(); it != unvisited.end(); it++){
            if(__edges[next][(*it)]){ //there is a connection
                if(distance[(*it)] == -1 || distance[next] +
                        __edges[next][(*it)] < distance[(*it)]){
                    //distance == -1 is infinity
                    distance[(*it)] = distance[next] +
                            __edges[next][(*it)];
                    previous[(*it)] = next;
                }
            }
        }
        std::size_t smallest = ULONG_MAX; //or -1
        //choose next vertex to visit, by choosing the shortest unvisited path
        for(auto it = unvisited.begin(); it != unvisited.end(); it++){
            if(distance[(*it)] < smallest){
                smallest = distance[*it];
                next = *it;
                nochange = false;
            }
        }
    }
    if (distance[vf] == -1)
        return std::stack<std::size_t>();
    std::stack<std::size_t> shortest;
    for(std::size_t i = vf; i != v0; i = previous[i]){
        shortest.push(i);
    }
    shortest.push(v0);
    return shortest;
}

template<class T>
int graph_weighted<T>::shortest_distance(std::size_t v0, std::size_t vf){
    std::set<int> unvisited;

    //Will display the vertices in the shortest path
    //Shortest path is based on # of vertices traveled
    int distance[__vertices];
//    std::size_t previous[__vertices]; //stores the closest vertex
    //initialize distances to infinity
    for(std::size_t i = 0 ; i < __vertices; i++){
        distance[i] = -1;
//        previous[i] = -1;
        unvisited.insert(i);
    }
    //Setup to begin dijkstra
    distance[v0] = 0;
    std::size_t next = v0;
    bool nochange = false; //check if there are still accessible vertices
    //So if v0 = 0, our distance is: [0, inf, ..., inf];
    while(!unvisited.empty() && !nochange){
        nochange = true;
        unvisited.erase(unvisited.find(next));

        //loop through unvisited, and update the shortest distances
        for(auto it = unvisited.begin(); it != unvisited.end(); it++){
            if(__edges[next][(*it)]){ //there is a connection
                if(distance[(*it)] == -1 || distance[next] +
                        __edges[next][(*it)] < distance[(*it)]){
                    //distance == -1 is infinity
                    distance[(*it)] = distance[next] +
                            __edges[next][(*it)];
                }
            }
        }
        std::size_t smallest = ULONG_MAX; //or -1
        //choose next vertex to visit, by choosing the shortest unvisited path
        for(auto it = unvisited.begin(); it != unvisited.end(); it++){
            if(distance[(*it)] < smallest){
                smallest = distance[*it];
                next = *it;
                nochange = false;
            }
        }
    }

    return distance[vf];
}


#endif // GRAPH_WEIGHTED_H
