#include <iostream>
#include <string>
#include "C:\\Users\\Nati\\Desktop\\SNA\\graph.h"
#include "C:\\Users\\Nati\\Desktop\\SNA\\graph.cpp"
using namespace std;

//driver
int main()
{
    graph g;
    g.insert_node("a");
    g.insert_node("Natnael");
    g.insert_node("Paul");
    g.insert_node("Abel");
    g.list_nodes_names();
}
