//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

//dont know the usage of this include
#include <boost/config.hpp>
//this iostream is necessary for almost all codes
#include <iostream>
//to reading and saving files to output
#include <fstream>
//graph_traits is necessary to call iterators for each graph type
#include <boost/graph/graph_traits.hpp>
//adjacency_list to define the graph
#include <boost/graph/adjacency_list.hpp>
//to include dijkstra shortest path f()
#include <boost/graph/dijkstra_shortest_paths.hpp>
//to define property map which hold the properties of vertices and edges
#include <boost/property_map/property_map.hpp>

//adding boost namespace dictionary to include boost defined variables
using namespace boost;

/*passing arguments into main is not necessary.
The first parameter gives you the number of command line arguments,
and the second gives you the actual arguments.
Not sure though exactly whats the use of them.*/
int main(int, char *[])
{
	/*renaming the adjacency_list to something readable and usable ie graph_t.
	listS argument means that the edges will be stored in the list containers.
	vecS means the graph will be based on the vector container.
	no_property means vertices have no property.
	property < edge_weight_t, int > means that edges will have property. We are using template. edge_weight_t is a defined term.
To make the graph undirected just rename directedS to undirectedS and it will work fine.*/
  typedef adjacency_list < listS, vecS, directedS, no_property, property < edge_weight_t, int > > graph_t;
/*  we are using graph_traits class template to make an object of its vertex_descriptor type and giving it some proper name.
 * we are passing adjacency_list object which we just defined above to it as template parameter. */
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
/*giving proper name to std's pair template by passing int template parameters.
 * we are thus saying that edges will be defined using two integer numbers*/
  typedef std::pair<int, int> Edge;

/*  num_nodes means number of nodes */
  const int num_nodes = 5;
/*  enum means that we have defined a new data type which will hold only A,B,C,D,E values*/
  enum nodes { A, B, C, D, E };
  char name[] = "ABCDE";
/*  making the edge type array which will hold the edge elements inside the array*/
  Edge edge_array[] = { Edge(A, C), Edge(B, B), Edge(B, D), Edge(B, E),
    Edge(C, B), Edge(C, D), Edge(D, E), Edge(E, A), Edge(E, B)
  };
  int weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
/*  sizeof(Edge) is 8 and sizeof(edge_array) is 8 multiplied by number of items in the array.
 * num_arcs means number of edges*/
  int num_arcs = sizeof(edge_array) / sizeof(Edge);

/*  declaring the graph*/
  graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);
  /*declaring the type of a property map by passing graph_t and edge_weight_t template parameters.
  here we are making it an edge weight type */
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
/*  the following two objects will be used inside the dijkstra f()*/
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
/*  making a vertex using vertex_descriptor which will be used as an starting point */
  vertex_descriptor s = vertex(A, g);

/*  the distance_map will store the distance values wrt to the starting point (which is A)
 * later on in order to retrieve those distance values we have to use vertex_iterators.
 * predecessor_map will store the second last node from where the route reached to the final
 * destination. We have to dereference all these pointers which we will get from these iterators
 * in order to obtain the data.*/
  dijkstra_shortest_paths(g, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

  std::cout << "distances and parents:" << std::endl;
/*  vertex_iterator will be used of graph_traits class to iterate through all the vertices.
 * below we are just initializing a vertex_iterator object. they will be declared inside the for loop*/
  graph_traits < graph_t >::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::
      endl;
  }
  std::cout << std::endl;

  /*
  // The following code is used to output resulting graph into the disk
  std::ofstream dot_file("dijkstra-eg.dot");

  dot_file << "digraph D {\n"
    << "  rankdir=LR\n"
    << "  size=\"4,3\"\n"
    << "  ratio=\"fill\"\n"
    << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

  graph_traits < graph_t >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    graph_traits < graph_t >::edge_descriptor e = *ei;
    graph_traits < graph_t >::vertex_descriptor
      u = source(e, g), v = target(e, g);
    dot_file << name[u] << " -> " << name[v]
      << "[label=\"" << get(weightmap, e) << "\"";
    if (p[v] == u)
      dot_file << ", color=\"black\"";
    else
      dot_file << ", color=\"grey\"";
    dot_file << "]";
  }
  dot_file << "}";
  */
  return EXIT_SUCCESS;
}

