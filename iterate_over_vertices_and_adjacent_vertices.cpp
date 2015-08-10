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

//namespace is a dictionary which contains the def of terms used in our code eg cout, int, float etc
using namespace boost;
using namespace std;

/*The purpose of typedef is to form complex types from more-basic machine types[1]
and assign simpler names to such combinations.*/
typedef property<edge_weight_t, int> EdgeWeightProperty;
typedef boost::adjacency_list<listS, vecS, directedS, no_property, EdgeWeightProperty> mygraph;

int main(){
	mygraph g;
	add_edge (0, 1, 8, g);
    add_edge (0, 3, 18, g);
    add_edge (1, 2, 20, g);
    add_edge (2, 3, 2, g);
    add_edge (3, 1, 1, g);
	add_edge (1, 3, 7, g);

	//Here we are creating pointers which will refer to the indexes of the graph
	mygraph::vertex_iterator vertexIt, vertexEnd;
	mygraph::adjacency_iterator neighbourIt, neighbourEnd;

	/*Giving vertexIt and vertexEnd pointers values.
	Following vertices f() is a boost f()*/
	tie(vertexIt, vertexEnd) = vertices(g);

	//The following for loop will go from 0-3 since *vertexEnd = 4
	for (; vertexIt != vertexEnd; ++vertexIt)
	{
		cout << *vertexIt << " vertex is connected with ";

		//Following adjacent_vertices f() is a boost f()
		tie(neighbourIt, neighbourEnd) = adjacent_vertices(*vertexIt, g);

		for(; neighbourIt != neighbourEnd; ++neighbourIt)
			cout << *neighbourIt << " ";

		cout << "vertices \n";
	}
}




