#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <unordered_map>
using namespace std;

class graph
{
public:

        

        void insert_node(unsigned int id, string name);
        void remove_node(unsigned int id);
        void add_edge(unsigned int id_1, unsigned int id_2);
        void remove_edge(unsigned int id_1,  unsigned int id_2);
        bool are_related(node* a, node* b);


private:
        unordered_map<unsigned int, node*> vertices;
};


#endif // GRAPH_H_INCLUDED
