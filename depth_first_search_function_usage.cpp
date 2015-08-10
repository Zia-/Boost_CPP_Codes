//============================================================================
// Name        : boost_test.cpp
// Author      : Zia
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//#include is to add files having f()s which we may need here
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/depth_first_search.hpp>

//namespace is a dictionary which contains the def of terms used in our code eg cout, int, float etc
using namespace boost;
using namespace std;

/*The purpose of typedef is to form complex types from more-basic machine types[1]
and assign simpler names to such combinations.*/
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<listS, vecS, undirectedS, no_property, EdgeWeightProperty> mygraph;

/*Here we are making a derived class from boost default_dfs_visitor class
 * to create out visitor object later on. We are not making object
 * directly from the default_dfs_visitor class we want to modify
 * discover_vertex and examine_edge class methods to handle proper cout.
 * Pay proper attention to the template usage in the custom_dfs_visitor class*/
class custom_dfs_visitor : public boost::default_dfs_visitor
{
public:
	template <typename Vertex, typename Graph>
	void discover_vertex(Vertex u, const Graph& g)
	const {std::cout << "At "<< u << std::endl;}

	template <typename Edge, typename Graph>
	void examine_edge(Edge e, const Graph& g)
	const {std::cout << "Examining edges " << e << std::endl;}
};

int main(){
	mygraph g;
	add_edge (0, 1, g);
    add_edge (1, 3, g);
    add_edge (3, 2, g);
    add_edge (2, 0, g);
    //add_edge (3, 1, g);
	//add_edge (1, 3, g);

    //creating custom visitor object
	custom_dfs_visitor vis;
	/*passing graph and visitor object into depth_first_search function.
	 we are using visitor wrapper funtion to pass vis coz we are using
	 named version of the depth_first_search f(). in non-named parameters
	 version of the same f() we have to pass on all the possible parameters.
	 thus f() will auto know which parameter is my visitor object*/
	depth_first_search(g, visitor(vis));
}




