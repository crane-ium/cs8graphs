#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    graph<string> undir;
    undir.add_vertex("v1");
    undir.add_vertex("v2");
    undir.add_vertex("v2");
    undir.add_edge(1, 2);
    undir.print();
    return 0;
}
