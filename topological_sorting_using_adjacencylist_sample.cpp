//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include <deque>                // to store the vertex ordering
#include <vector>
#include <list>
#include <iostream>
#include <boost/graph/vector_as_graph.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/adjacency_list.hpp>

int
main()
{
	//declaring the boost namespace
  using namespace boost;
  //making character array to point to a character list
  const char * tasks[] = {
    "pick up kids from school",
    "buy groceries (and snacks)",
    "get cash at ATM",
    "drop off kids at soccer practice",
    "cook dinner",
    "pick up kids from soccer",
    "eat dinner"
  };

  //sizeof(char *) = 8 coz 8 bit character. sizeof(tasks) = 8 multiplied by number of items in the array.
  const int n_tasks = sizeof(tasks) / sizeof(char *);

  /*making an adjacency_list object. listS means that list
  will be used for storing edge list. vecS means the backbone of
  adjacency_list is vector. Since we are using vector we can
  use integers to refer to a particular list object into the container.*/
  adjacency_list < listS, vecS, directedS > g(n_tasks);

  add_edge(0, 3, g);
  add_edge(1, 3, g);
  add_edge(1, 4, g);
  add_edge(2, 1, g);
  add_edge(3, 5, g);
  add_edge(4, 6, g);
  add_edge(5, 6, g);


  /*making a double sided queue (deque) to store output data structure.
  why double sided queue coz topological_sort f() will output results in
  reversed order, so we need a double sided variable so that we will export
  the required order from the other side*/
  std::deque < int >topo_order;

/*  inserting the topological_sort results into topo_order variable.
 * we are using vertex_index_map(identity_property_map()) as the coloring stuff
 * to marking those vertices which are done. Plus we are passing g graph.*/
  topological_sort(g, std::front_inserter(topo_order),
                   vertex_index_map(identity_property_map()));

/*  making another deque iterator pointer i and inserting topo_order.begin
 * address value into it. Inside the for loop we will dereference the i pointer*/
  for (std::deque < int >::iterator i = topo_order.begin();
       i != topo_order.end(); ++i)
    std::cout << tasks[*i] << " " << *i << std::endl;

  return EXIT_SUCCESS;
}

