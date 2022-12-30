#include "C:\\Users\\Nati\\Desktop\\SNA\\graph.h"
#include "C:\\Users\\Nati\\Desktop\\SNA\\node.h"
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;



void graph::insert_node(string Name)
{

    //automatically generate node id
    int id = node_count + 1;

    //check if node already exists
    if( vertices[id] != nullptr )
    {
        //duplicate nodes are not allowed
        for(int i = 0; i < vertices.size(); i++ )
        {
            if(vertices[i]->_Name == Name)
            {
                cerr<<"Error: Duplicate Nodes aren't allowed";
                return;
            }
        }

        node new_node;
        new_node._id = id;
        new_node._Name = Name;
        vertices.insert({id, &new_node});
    }
    else
    {
        //handle collusion and re invoke function
        id++;
        insert_node(Name);
    }
}

void graph::remove_node(unsigned int id)
{

    //if id exists
    if( vertices[id] == nullptr )
    {
        cerr<<"Error: node does not exist";
        return;
    }

    node* node_ptr = vertices[id];
    int key;
    //remove all edges
    for(int i = 0; i < node_ptr->adjecent_nodes.size(); i++)
    {

        remove_edge( node_ptr->adjecent_nodes[i], node_ptr->_id);
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
        cerr<<"Error: either or both nodes do not exist!";
        return;
    }

    if( are_related( vertices[id_1], vertices[id_2] ) )
    {
        cerr<<"Error: edge already exist";
        return;
    }
}

void graph::add_edge(node* nd_1, node* nd_2)
{
    //nodes must be different
    if( nd_1 == nd_2 )
    {
        cerr<<"Error: self-referential edge is not allowed!";
        return;
    }

    if( nd_1 == nullptr || nd_2 == nullptr )
    {
        cerr<<"Error: either or both nodes do not exist!";
        return;
    }

    if( are_related( nd_1, nd_2 ) )
    {
        cerr<<"Error: edge already exist";
        return;
    }
    //add respective ids to nodes
    nd_1->adjecent_nodes.push_back(nd_2->_id);
    nd_2->adjecent_nodes.push_back(nd_1->_id);
}

void graph::remove_edge(node* a, node* b)
{
    if( !are_related(a, b) )
    {
        cerr<<"Error: edge does not exist";
        return;
    }

    auto itrA = std::find(a->adjecent_nodes.begin(), a->adjecent_nodes.end(), b);

	if (itrA != a->adjecent_nodes.end())	// if found
	{
		// delete Node b from Node a's adjacency list
		a->adjecent_nodes.erase(itrA);
	}

	// remove node a from node b's Adjacency List.
	auto itrB = find(b->adjecent_nodes.begin(), b->adjecent_nodes.end(), a);
	if (itrB != b->adjecent_nodes.end())
	{
		// delete node a from node b's adjacency list
		b->adjecent_nodes.erase(itrB);
	}
}

void graph::remove_edge(unsigned int id_1, unsigned int id_2)
{
    node* a = vertices[id_1];
    node* b = vertices[id_2];

    if( !are_related( a, b) )
    {
        cerr<<"Error: edge does not exist";
        return;
    }

    auto itrA = find(a->adjecent_nodes.begin(), a->adjecent_nodes.end(), b);

	if (itrA != a->adjecent_nodes.end())	// if found
	{
		// delete Node b from Node a's adjacency list
		a->adjecent_nodes.erase(itrA);
	}

	// remove node a from node b's Adjacency List.
	auto itrB = find(b->adjecent_nodes.begin(), b->adjecent_nodes.end(), a);
	if (itrB != b->adjecent_nodes.end())
	{
		// delete node a from node b's adjacency list
		b->adjecent_nodes.erase(itrB);
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
	auto itrA = find(a->adjecent_nodes.begin(), a->adjecent_nodes.end(), b);
	auto itrB = find(b->adjecent_nodes.begin(), b->adjecent_nodes.end(), a);

	if (itrA != a->adjecent_nodes.end() && itrB != b->adjecent_nodes.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void graph::list_adjecent_nodes(int id)
{

    node* node_ptr = vertices[id];
    for(int j = 0; j < node_ptr->adjecent_nodes.size(); j++)
    {
        cout<<" "<<node_ptr->adjecent_nodes[j]<<" |";
    }
    cout<<" ]";

}

void graph::list_adjecent_nodes(string Name)
{

    node* node_ptr = nullptr;

    for(int i = vertices.size(); i>=0; i--)
    {
        node_ptr = vertices[i];
        if( node_ptr->_Name == Name)
        {
            break;
        }
    }
    cout<<"[";
    for(int j = 0; j < node_ptr->adjecent_nodes.size(); j++)
    {
        cout<<" "<<node_ptr->adjecent_nodes[j]<<" |";
    }
    cout<<" ]";
}

void graph::list_common_friends(int id_1, int id_2)
{
    node* node_ptr_1 = vertices[id_1];
    node* node_ptr_2 = vertices[id_2];
    unsigned int key;

    cout<<"Common friends:"<<endl<<"[";

    for(int i=0; i < node_ptr_1->adjecent_nodes.size(); i++)
    {
        for(int j=0; j < node_ptr_2->adjecent_nodes.size(); j++)
        {
            if(node_ptr_1->adjecent_nodes[i] == node_ptr_2->adjecent_nodes[j])
            {
                key = node_ptr_1->adjecent_nodes[i];

                cout<<" "<<vertices[key]->_Name<<" |";
            }
        }
    }
}

vector<unsigned int> graph::list_common_friends_vector(node* node_ptr_1, node* node_ptr_2)
{
    vector<unsigned int> ids;
    unsigned int key;

    for(int i=0; i < node_ptr_1->adjecent_nodes.size(); i++)
    {
        for(int j=0; j < node_ptr_2->adjecent_nodes.size(); j++)
        {
            if(node_ptr_1->adjecent_nodes[i] == node_ptr_2->adjecent_nodes[j])
            {
                key = node_ptr_1->adjecent_nodes[i];

                ids.push_back(key);
            }
        }
    }

    return ids;
}

void graph::list_common_friends(string Name_1,string Name_2)
{

    node* node_ptr_1 = nullptr;

    for(int i = vertices.size(); i>=0; i--)
    {
        node_ptr_1 = vertices[i];
        if( node_ptr_1->_Name == Name_1)
        {
            break;
        }
    }

    node* node_ptr_2 = nullptr;

    for(int i = vertices.size(); i>=0; i--)
    {
        node_ptr_2 = vertices[i];
        if( node_ptr_2->_Name == Name_2)
        {
            break;
        }
    }

    unsigned int key;

    cout<<"Common friends:"<<endl<<"[";
    for(int i=0; i < node_ptr_1->adjecent_nodes.size(); i++)
    {
        for(int j=0; j < node_ptr_2->adjecent_nodes.size(); j++)
        {
            if(node_ptr_1->adjecent_nodes[i] == node_ptr_2->adjecent_nodes[j])
            {
                key = node_ptr_1->adjecent_nodes[i];

                cout<<" "<<vertices[key]->_Name<<" |";
            }
        }
    }
}

void graph::list_nodes_names()
{
    cout<<"nodes:"<<endl<<"[";
    for(int i=0; i <= vertices.size(); i++)
    {
        cout<<" "<<vertices[i]->_Name<<" |";
    }
}

vector<node*> graph::list_nodes_vector()
{
    vector<node*> nds;

    for(int i=0; i<= vertices.size(); i++)
    {
        nds.push_back(vertices[i]);
    }

    return nds;
}

