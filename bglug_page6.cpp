#include <iostream>
#include <boost/graph/adjacency_list.hpp>

using namespace boost;
using namespace std;

typedef boost::adjacency_list<listS, vecS, undirectedS> mygraph;

template <typename Graph>
bool is_self_loop(typename graph_traits<Graph>::edge_descriptor e, const Graph& g)
{
	typename graph_traits<Graph>::vertex_descriptor u, v;
	u = source(e, g);
	v = target(e, g);
	return u == v;
}

int main(){
	mygraph g;
	add_edge(0,1,g);
	add_edge(0,3,g);
	add_edge(1,2,g);
	add_edge(2,3,g);

	is_self_loop<mygraph>(mygraph, g);
}
