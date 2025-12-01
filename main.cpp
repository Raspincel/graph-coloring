#include <iostream>
#include "graph.h"
#include "node.h"
#include "edge.h"

int main()
{
  std::cout << "Escolha o valor de k: ";
  int k;

  std::cin >> k;

  std::vector<Node> Nodes{{{1, k}, {2, k}, {3, k}, {4, k}, {5, k}, {6, k}}};
  std::vector<Edge> Edges{{
      {Nodes[0], Nodes[1]},
      {Nodes[0], Nodes[2]},
      {Nodes[0], Nodes[3]},
      {Nodes[1], Nodes[2]},
      {Nodes[1], Nodes[4]},
      {Nodes[2], Nodes[4]},
      {Nodes[4], Nodes[5]},
  }};

  Graph graph(Nodes, Edges);

  auto resultado = graph.verificarSeEKColorivel(k);

  std::cout << std::boolalpha;
  std::cout << "É k-colorível: " << resultado << "\n";
  
  if (resultado)
  {
    graph.imprimirColoring();
  }

  return 0;
}