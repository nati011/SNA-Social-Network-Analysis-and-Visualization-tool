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

        person new_node;
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

    person* node_ptr = vertices[id];
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

    if( vertices[id_1] == nullptr || vertices[id_2] == nullptr )
    {
        cerr<<"Error: either or both nodes do not exist!";
        return;
    }

    if( are_related( id_1, id_2 ) )
    {
        cerr<<"Error: edge already exist";
        return;
    }

    person* nd_1 = vertices[id_1];
    person* nd_2 = vertices[id_2];
    //add respective ids to nodes
    nd_1->adjecent_nodes.push_back(vertices[id_2]->_id);
    nd_2->adjecent_nodes.push_back(vertices[id_1]->_id);
}

void graph::add_edge(person* nd_1, person* nd_2)
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

void graph::remove_edge(person* a, person* b)
{

    if( !are_related(a, b) )
    {
        cerr<<"Error: edge does not exist";
        return;
    }

    //find and remove from a
    for(int i=0; i<a->adjecent_nodes.size(); i++)
    {
        if(a->adjecent_nodes[i] == b->_id)
        {
            a->adjecent_nodes.erase(a->adjecent_nodes.begin() + i);
            break;
        }
    }
    //find and remove from b
    for(int i=0; i<b->adjecent_nodes.size(); i++)
    {
        if(b->adjecent_nodes[i] == a->_id)
        {
            b->adjecent_nodes.erase(b->adjecent_nodes.begin() + i);
            break;
        }
    }

}

void graph::remove_edge(unsigned int id_1, unsigned int id_2)
{
    person* a = vertices[id_1];
    person* b = vertices[id_2];

    if( !are_related( a, b) )
    {
        cerr<<"Error: edge does not exist";
        return;
    }

     //find and remove from a
    for(int i=0; i<a->adjecent_nodes.size(); i++)
    {
        if(a->adjecent_nodes[i] == b->_id)
        {
            a->adjecent_nodes.erase(a->adjecent_nodes.begin() + i);
            break;
        }
    }
    //find and remove from b
    for(int i=0; i<b->adjecent_nodes.size(); i++)
    {
        if(b->adjecent_nodes[i] == a->_id)
        {
            b->adjecent_nodes.erase(b->adjecent_nodes.begin() + i);
            break;
        }
    }
}

bool graph::are_related(person* a, person* b)
{
	// Check if nodes exist
	if (!(a && b))
	{
		return false;
	}

	bool flag_1 = false;
	bool flag_2 = false;
	// Check if Nodes have relation

    for(int i=0; i<a->adjecent_nodes.size(); i++)
    {
        if(a->adjecent_nodes[i] == b->_id)
        {
            flag_1 = true;
            break;
        }
    }

    for(int i=0; i<b->adjecent_nodes.size(); i++)
    {
        if(b->adjecent_nodes[i] == a->_id)
        {
            flag_2 = true;
            break;
        }
    }
	if (flag_1 && flag_2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool graph::are_related(unsigned int i_a, unsigned int i_b)
{

	person* a = vertices[i_a];
	person* b = vertices[i_b];
	// Check if nodes exist

	if (!(a && b))
	{
		return false;
	}

	bool flag_1 = false;
	bool flag_2 = false;
	// Check if Nodes have relation

    for(int i=0; i<a->adjecent_nodes.size(); i++)
    {
        if(a->adjecent_nodes[i] == b->_id)
        {
            flag_1 = true;
            break;
        }
    }

    for(int i=0; i<b->adjecent_nodes.size(); i++)
    {
        if(b->adjecent_nodes[i] == a->_id)
        {
            flag_2 = true;
            break;
        }
    }
	if (flag_1 && flag_2)
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

    person* node_ptr = vertices[id];
    for(int j = 0; j < node_ptr->adjecent_nodes.size(); j++)
    {
        cout<<" "<<node_ptr->adjecent_nodes[j]<<" |";
    }
    cout<<" ]";

}

void graph::list_adjecent_nodes(string Name)
{

    person* node_ptr = nullptr;

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
    person* node_ptr_1 = vertices[id_1];
    person* node_ptr_2 = vertices[id_2];
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

vector<unsigned int> graph::list_common_friends_vector(person* node_ptr_1, person* node_ptr_2)
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

    person* node_ptr_1 = nullptr;

    for(int i = vertices.size(); i>=0; i--)
    {
        node_ptr_1 = vertices[i];
        if( node_ptr_1->_Name == Name_1)
        {
            break;
        }
    }

    person* node_ptr_2 = nullptr;

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

void graph::list_nodes_name()
{
    cout<<"nodes:"<<endl<<"[";
    for(int i=0; i <= vertices.size(); i++)
    {

    cout<<" "<<vertices[i]->_Name<<" |";
    }
}

vector<person*> graph::list_nodes_vector()
{
    vector<person*> nds;

    for(int i=0; i<= vertices.size(); i++)
    {
        nds.push_back(vertices[i]);
    }

    return nds;
}

