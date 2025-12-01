#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include "node.h"
#include "edge.h"

class Graph
{
private:
  std::vector<Node> nodes;
  std::vector<Edge> edges;

  struct TreeNode
  {
    Node &node;
    std::vector<TreeNode> children;
  };

  bool imprimirTreeNode(const TreeNode &tn, int nivel = 0)
  {
    std::string indent(nivel * 2, ' ');
    std::cout << indent << tn.node << "\n";

    bool resultado = tn.node.temCorValida();

    for (const TreeNode &filho : tn.children)
    {
      resultado = resultado && imprimirTreeNode(filho, nivel + 1);
    }

    return resultado;
  }

  void preencherArvore(TreeNode &etn)
  {
    std::vector<std::reference_wrapper<Edge>> edges;
    edges.reserve(this->edges.size());

    std::copy_if(this->edges.begin(), this->edges.end(), std::back_inserter(edges), [&etn](Edge &edge)
                 { return edge.pegarPrimeiroNo().compararValorNo(etn.node); });

    for (const auto &edge : edges)
    {
      TreeNode tn{edge.get().pegarSegundoNo()};
      preencherArvore(tn);

      etn.children.emplace_back(std::move(tn));
    }
  }

  void selecionarCores(TreeNode &etn)
  {
    int cor = etn.node.pegarProximaCorDisponivel();

    for (const auto &child : etn.children)
    {
      child.node.removerCor(cor);
    }

    for (auto &child : etn.children)
    {
      selecionarCores(child);
    }
  }

public:
  Graph(std::vector<Node> nodes_, std::vector<Edge> edges_) : nodes(nodes_), edges(edges_)
  {
  }

  bool verificarSeEKColorivel()
  {
    if (this->nodes.size() == 0)
    {
      return true;
    }

    TreeNode tn = {this->nodes[0]};
    preencherArvore(tn);
    selecionarCores(tn);
    return imprimirTreeNode(tn);
  }

  ~Graph() {}
};

#endif