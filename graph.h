#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <string>
#include <unordered_map>
#include <vector>
#include "C:\\Users\\Nati\\Desktop\\SNA\\node.h"
using namespace std;
extern int node_count = -1;

class graph
{
public:

        //todo: Implement map

        void insert_node(string name);
        void remove_node(unsigned int id);
        void add_edge(unsigned int id_1, unsigned int id_2);
        void add_edge(node* nd_1, node* nd_2);
        void remove_edge(unsigned int id_1,  unsigned int id_2);
        void remove_edge(node* a, node* b);
        bool are_related(node* a, node* b);
        void list_adjecent_nodes(int id);
        void list_adjecent_nodes(string Name);
        void list_common_friends(int id_1, int id_2);
        void list_common_friends(string name_1,string name_2);
        vector<unsigned int> list_common_friends_vector(node* nd_1, node* nd_2);

        void list_nodes_names();
        vector<node*> list_nodes_vector();


private:


        unordered_map<unsigned int, node*> vertices;

};


#endif // GRAPH_H_INCLUDED
