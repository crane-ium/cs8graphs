#include <iostream>
#include "graph15_1.h"
#include "graph15_3.h"

using namespace std;

void test_graph15_1();
void test_graph15_3();

int main()
{
    test_graph15_3();

    test_graph15_1();

    return 0;
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
