#ifndef EDGE_H
#define EDGE_H

#include "node.h"

class Edge
{
private:
  Node &node1;
  Node &node2;

public:
  Edge(Node &node1_, Node &node2_) : node1(node1_), node2(node2_) {}

  Node &pegarPrimeiroNo()
  {
    return this->node1;
  }

  Node &pegarSegundoNo()
  {
    return this->node2;
  }
};

#endif