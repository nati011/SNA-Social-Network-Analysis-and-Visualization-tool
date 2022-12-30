#include <graph.h>
#include <node.h>
using namespace std;

//automatically generate node id
void graph::insert_node(unsigned int id, string Name)
{

    //check if node already exists

    if( !vertices.find(id) )
    {
        //duplicate nodes are not allowed
        for(int i = 0; i < vertices.size(); i++ )
        {
            if(vertices[i].name == Name)
            {
                cerr<<"Error: Duplicate Nodes aren't allowed";
                return;
            }
        }

        node* new_node = new node(id, Name);
        vertices.insert({id, new_node});
    }
    else
    {
        //regenerate id and try inserting again
    }
}

void graph::remove_node(unsigned int id)
{

    //if id exists
    if( !vertices.find(id) )
    {
        cerr<<"Error: node does not exist";
        return;
    }
    node* node_ptr = vertices[id];

    //remove all edges
    for(int i = 0; i < adjecent_nodes.size(); i++)
    {
        remove_edge( adjecent_nodes[i], node_ptr);
    }

    //remove from map
    vertices.erase(id);

}

void graph::add_edge(unsigned int id_1, unsigned int id_2)
{
    //nodes must be different
    if(id_1 == id_2)
    {
        cerr<<"Error: self-referential edge is not allowed!";
        return;
    }

    if( !vertices[id_1] && !vertices[id_2] )
    {
        cerr<<"Error: Either or both nodes do not exist!";
        return;
    }

    if( are_related( &vertices[id_1], &vertices[id_2] )
    {
        cerr<<"Error: edge already exist";
        return;
    }

}

void graph::remove_edge(node* a, node* b)
{
    if( !are_related( a, b)
    {
        cerr<<"Error: edge does not exist";
        return;
    }

    auto itrA = find(a.adjecent_nodes.begin(), a.adjecent_nodes.end(), b);

	if (itrA != a.adjecent_nodes.end())	// if found
	{
		// delete Node b from Node a's adjacency list
		a.adjecent_nodes.erase(itrA);
	}

	// remove node a from node b's Adjacency List.
	auto itrB = find(b.adjecent_nodes.begin(), b.adjecent_nodes.end(), a);
	if (itrB != b.adjecent_nodes.end())
	{
		// delete node a from node b's adjacency list
		b.adjecent_nodes.erase(itrB);
	}
}

void graph::remove_edge(unsigned int id_1,  unsigned int id_2)
{
    if( !are_related( &vertices[id_1], &vertices[id_2] )
    {
        cerr<<"Error: edge does not exist";
        return;
    }
    node* a = vertices[id_1];
    node* b = vertices[id_2];

    auto itrA = find(a.adjecent_nodes.begin(), a.adjecent_nodes.end(), b);

	if (itrA != a.adjecent_nodes.end())	// if found
	{
		// delete Node b from Node a's adjacency list
		a.adjecent_nodes.erase(itrA);
	}

	// remove node a from node b's Adjacency List.
	auto itrB = find(b.adjecent_nodes.begin(), b.adjecent_nodes.end(), a);
	if (itrB != b.adjecent_nodes.end())
	{
		// delete node a from node b's adjacency list
		b.adjecent_nodes.erase(itrB);
	}
}

bool graph::are_related(node* a, node* b)
{
	// Check if nodes exist
	if (!(a && b))
	{
		return false;
	}

	// Check if Nodes have relation
	auto itrA = find(a.adjecent_nodes.begin(), a.mAdjacent.end(), b);
	auto itrB = find(b.adjecent_nodes.begin(), b.mAdjacent.end(), a);

	if (itrA != a.adjecent_nodes.end() && itrB != b.adjecent_nodes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}
