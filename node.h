#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <string>
#include <vector>

class node
{
public:
        vector<node*>adjecent_nodes;

        node(unsigned int id, unsigned int Name)
        {
            _id = id;
            _Name = Name;
        }

        unsigned int _id;
        string _Name;

};

#endif // NODE_H_INCLUDED
