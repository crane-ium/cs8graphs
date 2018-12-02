#include <iostream>
#include "graph15_1.h"
#include "graph15_3.h"
#include "graph15_4.h"
#include "graph_weighted.h"

using namespace std;

void test_graph15_1();//Simple graph test
void test_graph15_3();//Inherits simple_graph and has edge labels
void test_graph15_4();//Checks if path exists between two vertices
void test_graph15_5();//Dijkstra's Algorithm implementation

//to easily display stack info of the vertices
ostream& operator <<(ostream& outs, stack<std::size_t> s){

    outs << "(";
    while(!s.empty()){
        outs << s.top();
        s.pop();
        if(s.size() != 0)
            outs << ", ";
    }
    outs << ")";
    return outs;
}

int main()
{
    //Tests dijkstra's algorithm implementations
    test_graph15_5();

//    test_graph15_4();

//    test_graph15_3();

//    test_graph15_1();

    return 0;
}

void test_graph15_5(){
    graph_weighted<int> g(false); //directed graph

    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();
    g.add_vertex();

    //create a pathway (mapped already on paper)
    g.add_edge(0 , 1, 6);
    g.add_edge(0 , 2, 4);
    g.add_edge(0 , 4, 20);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 5);
    g.add_edge(2, 1, 1);
    g.add_edge(2, 3, 8);
    g.add_edge(2, 4, 10);
    g.add_edge(3, 1, 5);
    g.add_edge(3, 2, 8);
    g.add_edge(3, 5, 4);
    g.add_edge(4, 0, 20);
    g.add_edge(4, 2, 10);
    g.add_edge(4, 5, 1);
    g.add_edge(5, 3, 4);
    g.add_edge(5, 4, 1);

    g.print();

    //test a connected path
    cout << "Shortest distance is " << g.shortest_distance(0, 5) << endl;
    cout << "Shortest path is " << g.shortest_path(0, 5) << endl;

    //test a different path
    g.remove_edge(3, 5);
    cout << "Shortest distance is " << g.shortest_distance(0, 5) << endl;
    cout << "Shortest path is " << g.shortest_path(0, 5) << endl;

    //test a disconnected path
    g.remove_edge(4, 5);
    cout << "Shortest distance is " << g.shortest_distance(0, 5) << endl;
    cout << "Shortest path is " << g.shortest_path(0, 5) << endl;


    cout << endl;
}

void test_graph15_4(){
    graph<string> g;
    g.add_vertex("v1");
    g.add_vertex("v2");
    g.add_vertex("v3");
    g.add_vertex("v4");
    g.add_vertex("v5");
    g.add_vertex("v6");
    //reflexivity
    g.add_edge(0, 0);
    g.add_edge(1, 1);
    g.add_edge(2, 2);
    g.add_edge(3, 3);
    g.add_edge(4, 4);
    g.add_edge(5, 5);
    //add a path
    g.add_edge(0,2);
    g.add_edge(1, 0);
    g.add_edge(1, 4);
    g.add_edge(2, 0);
    g.add_edge(2, 1);
    g.add_edge(3, 4);
    g.add_edge(3, 5);
    g.add_edge(4, 3);
    g.add_edge(5, 2);
    g.add_edge(5, 1);

    g.print();
    cout << (g.exists_path(0, 5) ? "There is a path!" : "There is not a path :(");
    cout << endl;
    cout << endl;
}

void test_graph15_3(){
    graph_edge_labels<string> undir(true);
    undir.add_vertex("v1");
    undir.add_vertex("v2");
    undir.add_vertex("v3");
    undir.add_vertex("v4");
    cout << "Vertices: ";
    for(std::size_t i = 0; i < undir.size(); i++){
        cout << undir[i];
        if(i < undir.size()-1)
            cout << ", ";
    }
    undir.add_edge(1, 2, "e1");
    undir.add_edge(3, 2, "e2");
    cout << endl;
    cout << "Edge at (1, 2): " << undir.get_edge(1, 2) << endl;

    undir.print();
    cout << endl;
}

void test_graph15_1(){
    //Test undirected graph of problem 15-1
    simple_graph<string> undir(false);
    undir.add_vertex("v1");
    undir.add_vertex("v2");
    undir.add_vertex("v3");
    undir.add_edge(1, 2);
    undir.print();
}
