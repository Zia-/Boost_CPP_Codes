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

  //making a vector g of list items.
  std::vector < std::list < int > > g(n_tasks);
  //defining all the directed edges. for ex first edge is going from 0 to 3.
  g[0].push_back(3);
  g[1].push_back(3);
  g[1].push_back(4);
  g[2].push_back(1);
  g[3].push_back(5);
  g[4].push_back(6);
  g[5].push_back(6);

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

