#include <boost/config.hpp>
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/iteration_macros.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
#include <boost/graph/astar_search.hpp>

/*

To be able to distinguish the edges (source,target) from the (target,source)
"cost" column weights are set to 1 for (source,target)
"reverse_cost" column weights are set to 2 for (target,source)

*/
using namespace boost;

//----------------------------------------------------------------------------------------------
// FIRST SCENARIO (use this fig as a reference https://github.com/Zia-/Boost_CPP_Codes/issues/1)
template < typename DirectedGraph >
void simulation_undirected_in_directed_graph()
{
  const int V = 3;
  DirectedGraph digraph(V);
  typename graph_traits < DirectedGraph >::vertex_descriptor vd;
  typedef typename DirectedGraph::edge_property_type Weight;
  typename property_map < DirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, digraph);
  typename graph_traits < DirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < DirectedGraph >::edge_iterator ei;
  typename graph_traits < DirectedGraph >::vertex_iterator vi;

  std::deque< typename graph_traits < DirectedGraph >::vertex_descriptor > vert;
  std::cout << "UNDIRECTED ON BOOST::DIRECTED GRAPH DEMO\n";
  for (int i=0; i < 19; ++i) {
    vd = vertex(i, digraph);
    vert.push_back(vd);
  }

  /*We are using this data http://docs.pgrouting.org/2.0/en/doc/src/developer/sampledata.html#sampledata
  The 1 means that traversal is possible and -1 means impossible.
  So in the follwoing add_edge lines we have given 2 values as a reverse cost for those edges
  for which the traversal was possible. For -1 costs/reverser_cost edges we havnt even included the edge.
  Since in the sample data page we havnt defined which one will be our source and target and since we will
  be using directedS so inorder to simulate an undirected scenario inside a directed graph, we have considered
  two scenarios ie. first consider 1 as the source and 2 as the target and define the weights cost and reverse_cost,
  then again consider 1 as target and 2 as source and defined cost and reverse_cost again. Thus basically we are
  adding two graphs to cover all possibilities although only one scenario is gonna used at a time.

  We have two approaches to deal with an undirected graph. Either declare like undirectedS and enter cost
  and reverse cost edges accordingly (as in our undirected_graph_demo template)
  OR
  Declare a directed graph like directedS and then once consider first node in the sample page as the source
  and second as target and again first as the target and second as source (as in our simulation_undirected_in_directed_graph template)*/
  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), digraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), digraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), digraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), digraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), digraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), digraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), digraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), digraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), digraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), digraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), digraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), digraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), digraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), digraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), digraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), digraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), digraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), digraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), digraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), digraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), digraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), digraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), digraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), digraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), digraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), digraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), digraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), digraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), digraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), digraph); // id 18


  // the "cost" column (reversing)
  add_edge(vert[2],  vert[1],  Weight(1), digraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[5],  vert[2],  Weight(1), digraph); // id 4
  add_edge(vert[6],  vert[3],  Weight(1), digraph); // id 5
  add_edge(vert[8],  vert[7],  Weight(1), digraph); // id 6
  add_edge(vert[5],  vert[8],  Weight(1), digraph); // id 7
  add_edge(vert[6],  vert[5],  Weight(1), digraph); // id 8
  add_edge(vert[9],  vert[6],  Weight(1), digraph); // id 9
  add_edge(vert[10], vert[5], Weight(1), digraph); // id 10
  add_edge(vert[11], vert[6], Weight(1), digraph); // id 11
  add_edge(vert[11], vert[10], Weight(1), digraph); // id 12
  add_edge(vert[12], vert[11], Weight(1), digraph); // id 13
  add_edge(vert[13], vert[10], Weight(1), digraph); // id 14
  add_edge(vert[12], vert[9], Weight(1), digraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(1), digraph); // id 16
  add_edge(vert[15], vert[14], Weight(1), digraph); // id 17
  add_edge(vert[17], vert[16], Weight(1), digraph); // id 18

  // the "reverse_cost" column (reversing)
  add_edge(vert[1], vert[2], Weight(2), digraph); // id 1
  add_edge(vert[2], vert[3], Weight(2), digraph); // id 2
  add_edge(vert[3], vert[4], Weight(2), digraph); // id 3
  add_edge(vert[2], vert[5], Weight(2), digraph); // id 4
  // id 5 has -1
  add_edge(vert[7], vert[8], Weight(2), digraph); // id 6
  add_edge(vert[8], vert[5], Weight(2), digraph); // id 7
  add_edge(vert[5], vert[6], Weight(2), digraph); // id 8
  add_edge(vert[6], vert[9], Weight(2), digraph); // id 9
  add_edge(vert[5], vert[10], Weight(2), digraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[10], vert[13], Weight(2), digraph); // id 14
  add_edge(vert[9],  vert[12], Weight(2), digraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(2), digraph); // id 16
  add_edge(vert[14], vert[15], Weight(2), digraph); // id 17
  add_edge(vert[16], vert[17], Weight(2), digraph); // id 18

  /*The preprocessor runs before the compiler when used #if.
  Since the following #if 0 then this portion of code  will never be executed*/
#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif

  for (vi = vertices(digraph).first; vi!=vertices(digraph).second; ++vi) {
    /*For the below for loop u have to consider both the graphs which we have added.
    Say for example consider 2nd node. We have these many cases
        considering 2 as source and 5 as target
          2-5 = 1 and 5-2 = 2
      considering 5 as source and 2 as source
          2-5 = 2 and 5-2 = 1
      considering 2 as source and 1 as target
        2-1 = 1 and 1-2 = 2
      considering 1 as source and 2 as target
        2-1 = 2 and 1-2 = 1
      considering 2 as source and 3 as target
          2-3 = not possible and 3-2 = 2
      considering 3 as source and 2 as target
          2-3 = 2 and 3-2 = not possible

    First node having number 0 is dunno which node.*/
    std::cout << "out_edges(" << *vi << "):";
    for (boost::tie(out, out_end) = out_edges(*vi, digraph); out != out_end; ++out) {
      std::cout << ' ' << *out << "=" << get(weight, *out);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

}

//----------------------------------------------------------------------------------------------
// SECOND SCENARIO (use this fig as a reference https://github.com/Zia-/Boost_CPP_Codes/issues/1)
template < typename DirectedGraph >
void directed_graph_demo()
{
  const int V = 3;
  DirectedGraph digraph(V);
  typename graph_traits < DirectedGraph >::vertex_descriptor vd;
  typedef typename DirectedGraph::edge_property_type Weight;
  typename property_map < DirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, digraph);
  typename graph_traits < DirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < DirectedGraph >::edge_iterator e, ei;
  typename graph_traits < DirectedGraph >::vertex_iterator vi;

  std::deque< typename graph_traits < DirectedGraph >::vertex_descriptor > vert;
  std::cout << "DIRECTED GRAPH DEMO\n";

  /*Just enter some random value greater than the number of vertices in the for loop below.
  Those extra nodes will simply float independently as a trivial graph*/
  for (int i=0; i < 19; ++i) {
    vd = vertex(i, digraph);
    vert.push_back(vd);
  }

  /*We are using this data http://docs.pgrouting.org/2.0/en/doc/src/developer/sampledata.html#sampledata
   * Now we have asssumed that the first coordinate given in the sample page is the source node and second the target one.
   * And also since we are using directedS so we are good.
   * So we will end up with only one graph insertion scenario.*/
  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), digraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), digraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), digraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), digraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), digraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), digraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), digraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), digraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), digraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), digraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), digraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), digraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), digraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), digraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), digraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), digraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), digraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), digraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), digraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), digraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), digraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), digraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), digraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), digraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), digraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), digraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), digraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), digraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), digraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), digraph); // id 18


// Non executable code
#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif

  for (vi = vertices(digraph).first; vi!=vertices(digraph).second; ++vi) {
    /*Look at this output which we got after running this code:
        out_edges(3): (3,6)=1 (3,2)=2
    Here (3,2) = 2 coz we have defined it like that in the sample page.
    Means there we have declared an edge from 2 to 3 with only reverse path possible.
    It means that path 3-2 is possible and since we have assumed reverse cost to be 2,
    hence (3,2) = 2.
    Consult the snapshot in the issue*/
    std::cout << "out_edges(" << *vi << "):";
    for (boost::tie(out, out_end) = out_edges(*vi, digraph); out != out_end; ++out) {
      std::cout << ' ' << *out << "=" << get(weight, *out);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

}

//----------------------------------------------------------------------------------------------
// THIRD SCENARIO (use this fig as a reference https://github.com/Zia-/Boost_CPP_Codes/issues/1)
template < typename UndirectedGraph >
void undirected_graph_demo()
{
  const int V = 3;
  UndirectedGraph undigraph(V);
  typename graph_traits < UndirectedGraph >::vertex_descriptor vd;
  typedef typename UndirectedGraph::edge_property_type Weight;
  typename property_map < UndirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, undigraph);
  typename graph_traits < UndirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < UndirectedGraph >::edge_iterator e, ei;
  typename graph_traits < UndirectedGraph >::vertex_iterator vi;

  std::deque< typename graph_traits < UndirectedGraph >::vertex_descriptor > vert;
  std::cout << "UNDIRECTED GRAPH DEMO\n";
  for (int i=0; i < 19; ++i) {
    vd = vertex(i, undigraph);
    vert.push_back(vd);
  }

  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), undigraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), undigraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), undigraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), undigraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), undigraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), undigraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), undigraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), undigraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), undigraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), undigraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), undigraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), undigraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), undigraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), undigraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), undigraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), undigraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), undigraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), undigraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), undigraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), undigraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), undigraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), undigraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), undigraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), undigraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), undigraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), undigraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), undigraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), undigraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), undigraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), undigraph); // id 18

#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif

  for (vi = vertices(undigraph).first; vi!=vertices(undigraph).second; ++vi) {
    std::cout << "out_edges(" << *vi << "):";
    for (boost::tie(out, out_end) = out_edges(*vi,undigraph); out != out_end; ++out) {
      std::cout << ' ' << *out << "=" << get(weight, *out);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

}

//----------------------------------------------------------------------------------------------
//ZIA PART - dijkstrea_shortest_path for undirected graph
template < typename UndirectedGraph >
void undirected_graph_dijkstra_shortest_path()
{
  const int V = 3;
  UndirectedGraph undigraph(V);
  //When using typedef then we are giving the whole definition of the data type a new name
  typedef typename graph_traits < UndirectedGraph >::vertex_descriptor verdis;
  //Now we are using this new name to make our object.
  verdis vd;
  typedef typename UndirectedGraph::edge_property_type Weight;
  typename property_map < UndirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, undigraph);
  //We have to use typename whenever wanna use during another template initiation or for typedef
  typename graph_traits < UndirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < UndirectedGraph >::edge_iterator e, ei;
  typename graph_traits < UndirectedGraph >::vertex_iterator vi, vend;

  std::deque< typename graph_traits < UndirectedGraph >::vertex_descriptor > vert;
  std::cout << "DIJKSTRA SHORTEST PATH UNDIRECTED GRAPH DEMO\n";
  std::cout << "Starting node is 1\n";

  for (int i=0; i < 19; ++i) {
    vd = vertex(i, undigraph);
    vert.push_back(vd);
  }

  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), undigraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), undigraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), undigraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), undigraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), undigraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), undigraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), undigraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), undigraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), undigraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), undigraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), undigraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), undigraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), undigraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), undigraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), undigraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), undigraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), undigraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), undigraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), undigraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), undigraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), undigraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), undigraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), undigraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), undigraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), undigraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), undigraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), undigraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), undigraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), undigraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), undigraph); // id 18

/*
#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif
*/

  std::vector<verdis> p(num_vertices(undigraph));
  std::vector<int> d(num_vertices(undigraph));
  verdis s = vertex(1, undigraph);

  dijkstra_shortest_paths(undigraph, s,
                            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, undigraph))).
                            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, undigraph))));

  for (boost::tie(vi, vend) = vertices(undigraph); vi != vend; ++vi){
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "predecessor(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------
//ZIA PART - dijkstrea_shortest_path for directed graph
template < typename DirectedGraph >
void directed_graph_dijkstra_shortest_path()
{
  const int V = 3;
  DirectedGraph digraph(V);
  typedef typename graph_traits < DirectedGraph >::vertex_descriptor verdis;
  verdis vd;
  typedef typename DirectedGraph::edge_property_type Weight;
  typename property_map < DirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, digraph);
  typename graph_traits < DirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < DirectedGraph >::edge_iterator e, ei;
  typename graph_traits < DirectedGraph >::vertex_iterator vi, vend;

  std::deque< typename graph_traits < DirectedGraph >::vertex_descriptor > vert;
  std::cout << "DIJKSTRA SHORTEST PATH DIRECTED GRAPH DEMO\n";
  std::cout << "Starting node is 1\n";

  /*Just enter some random value greater than the number of vertices in the for loop below.
  Those extra nodes will simply float independently as a trivial graph*/
  for (int i=0; i < 19; ++i) {
    vd = vertex(i, digraph);
    vert.push_back(vd);
  }

  /*We are using this data http://docs.pgrouting.org/2.0/en/doc/src/developer/sampledata.html#sampledata
   * Now we have asssumed that the first coordinate given in the sample page is the source node and second the target one.
   * And also since we are using directedS so we are good.
   * So we will end up with only one graph insertion scenario.*/
  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), digraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), digraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), digraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), digraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), digraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), digraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), digraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), digraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), digraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), digraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), digraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), digraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), digraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), digraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), digraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), digraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), digraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), digraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), digraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), digraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), digraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), digraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), digraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), digraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), digraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), digraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), digraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), digraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), digraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), digraph); // id 18

/*
#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif
*/

  std::vector<verdis> p(num_vertices(digraph));
  std::vector<int> d(num_vertices(digraph));
  verdis s = vertex(1, digraph);

  dijkstra_shortest_paths(digraph, s,
                            predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, digraph))).
                            distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, digraph))));

  for (boost::tie(vi, vend) = vertices(digraph); vi != vend; ++vi){
    std::cout << "distance(" << *vi << ") = " << d[*vi] << ", ";
    std::cout << "predecessor(" << *vi << ") = " << p[*vi] << std::endl;
  }
  std::cout << std::endl;
}

//----------------------------------------------------------------------------------------------
//ZIA PART - aStar_shortest_path for undirected graph
//We need this struct to store our coordinates whic we are gonna use inside astar algo
struct location
{
  float y, x; // lat, long
};
//Cost data type will be passed inside astar algo
typedef float cost;
// euclidean distance heuristic
/*This is the most imp template as this will assist aStar algo
to keep itself directed towards the target node by exploiting
the coordinate values of each node within the graph*/
template <class Graph, class CostType, class LocMap>
class distance_heuristic : public astar_heuristic<Graph, CostType>
{
public:
  typedef typename graph_traits<Graph>::vertex_descriptor Vertex;
  distance_heuristic(LocMap l, Vertex goal)
  : m_location(l), m_goal(goal) {}
  CostType operator()(Vertex u)
  {
  CostType dx = m_location[m_goal].x - m_location[u].x;
  CostType dy = m_location[m_goal].y - m_location[u].y;
  return ::sqrt(dx * dx + dy * dy);
  }
private:
  LocMap m_location;
  Vertex m_goal;
};
// visitor that terminates when we find the goal
/*This visitor will be called after each iteration. If the
next new node is equal to the target node then the value of that
new node will be printed out*/
template <class Vertex>
class astar_goal_visitor : public boost::default_astar_visitor
{
public:
  astar_goal_visitor(Vertex t) : m_goal(t) {}
  template <class Graph>
  void examine_vertex(Vertex u, Graph& undigraph) {
  if(u == m_goal)
    std::cout<< u << std::endl;
  }
private:
  Vertex m_goal;
};
//Actual template we are gonna use inside the main
template < typename UndirectedGraph >
void undirected_graph_astar_shortest_path()
{
  const int V = 3;
  UndirectedGraph undigraph(V);
  //When using typedef then we are giving the whole definition of the data type a new name
  typedef typename graph_traits < UndirectedGraph >::vertex_descriptor verdis;
  //Now we are using this new name to make our object.
  verdis vd;
  typedef typename UndirectedGraph::edge_property_type Weight;
  typename property_map < UndirectedGraph, edge_weight_t >::type
    weight = get(edge_weight, undigraph);
  //We have to use typename whenever wanna use during another template initiation or for typedef
  typename graph_traits < UndirectedGraph >::out_edge_iterator out, out_end;
  typename graph_traits < UndirectedGraph >::edge_iterator e, ei;
  typename graph_traits < UndirectedGraph >::vertex_iterator vi, vend;

  std::deque< typename graph_traits < UndirectedGraph >::vertex_descriptor > vert;
  std::cout << "ASTAR SHORTEST PATH UNDIRECTED GRAPH DEMO\n";
  std::cout << "Starting node is 1 and terminal is 12\n";

  for (int i=0; i < 19; ++i) {
    vd = vertex(i, undigraph);
    vert.push_back(vd);
  }

  // the "cost" column
  add_edge(vert[1],  vert[2],  Weight(1), undigraph); // id 1
  // id 2 has -1
  // id 3 has -1
  add_edge(vert[2],  vert[5],  Weight(1), undigraph); // id 4
  add_edge(vert[3],  vert[6],  Weight(1), undigraph); // id 5
  add_edge(vert[7],  vert[8],  Weight(1), undigraph); // id 6
  add_edge(vert[8],  vert[5],  Weight(1), undigraph); // id 7
  add_edge(vert[5],  vert[6],  Weight(1), undigraph); // id 8
  add_edge(vert[6],  vert[9],  Weight(1), undigraph); // id 9
  add_edge(vert[5],  vert[10], Weight(1), undigraph); // id 10
  add_edge(vert[6],  vert[11], Weight(1), undigraph); // id 11
  add_edge(vert[10], vert[11], Weight(1), undigraph); // id 12
  add_edge(vert[11], vert[12], Weight(1), undigraph); // id 13
  add_edge(vert[10], vert[13], Weight(1), undigraph); // id 14
  add_edge(vert[9],  vert[12], Weight(1), undigraph); // id 15
  add_edge(vert[4],  vert[9],  Weight(1), undigraph); // id 16
  add_edge(vert[14], vert[15], Weight(1), undigraph); // id 17
  add_edge(vert[16], vert[17], Weight(1), undigraph); // id 18

  // the "reverse_cost" column
  add_edge(vert[2],  vert[1], Weight(2), undigraph); // id 1
  add_edge(vert[3],  vert[2], Weight(2), undigraph); // id 2
  add_edge(vert[4],  vert[3], Weight(2), undigraph); // id 3
  add_edge(vert[5],  vert[2], Weight(2), undigraph); // id 4
  // id 5 has -1
  add_edge(vert[8],  vert[7], Weight(2), undigraph); // id 6
  add_edge(vert[5],  vert[8], Weight(2), undigraph); // id 7
  add_edge(vert[6],  vert[5], Weight(2), undigraph); // id 8
  add_edge(vert[9],  vert[6], Weight(2), undigraph); // id 9
  add_edge(vert[10], vert[5], Weight(2), undigraph); // id 10
  // id 11 has -1
  // id 12 has -1
  // id 13 has -1
  add_edge(vert[13], vert[10], Weight(2), undigraph); // id 14
  add_edge(vert[12], vert[9],  Weight(2), undigraph); // id 15
  add_edge(vert[9],  vert[4],  Weight(2), undigraph); // id 16
  add_edge(vert[15], vert[14], Weight(2), undigraph); // id 17
  add_edge(vert[17], vert[16], Weight(2), undigraph); // id 18

  location locations[] = { // lat/long
          {42.73, 73.68}, {44.28, 73.99}, {44.70, 73.46},
          {44.93, 74.89}, {43.97, 75.91}, {43.10, 75.23},
          {43.04, 76.14}, {43.17, 77.61}, {42.89, 78.86},
          {42.44, 76.50}, {42.10, 75.91}, {42.04, 74.11},
          {40.67, 73.94}, {45.28, 73.99}, {44.70, 74.46},
      {41.67, 73.94}, {44.28, 72.99}
    };

/*
#if 0
  std::cout << "all edges:\n";
  for (ei = edges(digraph).first; ei!=edges(digraph).second; ++ei)
    std::cout << ' ' << *ei << get(weight, *ei) <<  std::endl;
  std::cout << std::endl;
#endif
*/

  std::vector<verdis> p(num_vertices(undigraph));
  std::vector<int> d(num_vertices(undigraph));
  //Here we are declaring the source and target node
  verdis s = vertex(1, undigraph);
  verdis t = vertex(12, undigraph);

  //We need this array data type to record the distance value from the source to the target node
  typename boost::graph_traits< UndirectedGraph >::vertices_size_type distances[17];

  //aStar algo
  /*Here we can use two kind of visitors (one has been commented out).
  One will print the target node value. The other one will print out the
  sum of distance value between source and target (although dont know how to print).*/
  astar_search_tree
          (undigraph, s,
            distance_heuristic<UndirectedGraph, cost, location*>
            (locations, t),
           predecessor_map(make_iterator_property_map(p.begin(), get(vertex_index, undigraph))).
           distance_map(make_iterator_property_map(d.begin(), get(vertex_index, undigraph))).
           visitor(astar_goal_visitor<verdis>(t)));
       //visitor(make_astar_visitor(record_distances(distances,on_tree_edge()))));

}

int main()
{
  typedef property < edge_weight_t, double >Weight;
  typedef adjacency_list < listS, vecS, undirectedS,
    no_property, Weight > UndirectedGraph;
  typedef adjacency_list < listS, vecS, directedS,
    no_property, Weight > DirectedGraph;

  //undirected_graph_demo < UndirectedGraph > ();
  //directed_graph_demo < DirectedGraph > ();
  //simulation_undirected_in_directed_graph < DirectedGraph > ();
  //undirected_graph_dijkstra_shortest_path < UndirectedGraph > ();
  //directed_graph_dijkstra_shortest_path < DirectedGraph > ();
  undirected_graph_astar_shortest_path < UndirectedGraph > ();
  return 0;
}
