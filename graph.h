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

  // Verifica se é seguro colorir o vértice 'nodeIndex' com a cor 'cor'
  bool corSegura(int nodeIndex, int cor)
  {
    int idAtual = nodes[nodeIndex].obterId();
    
    // Verifica todos os vizinhos do vértice
    for (const auto &edge : edges)
    {
      Node &node1 = edge.pegarPrimeiroNo();
      Node &node2 = edge.pegarSegundoNo();

      // Encontra o vizinho do vértice atual
      int idVizinho = -1;
      if (node1.obterId() == idAtual)
      {
        idVizinho = node2.obterId();
      }
      else if (node2.obterId() == idAtual)
      {
        idVizinho = node1.obterId();
      }

      // Se encontrou um vizinho, verifica se ele já foi colorido com a mesma cor
      if (idVizinho != -1)
      {
        // Encontra o nó correspondente no vector
        for (int i = 0; i < nodeIndex; i++)
        {
          if (nodes[i].obterId() == idVizinho)
          {
            // Se o vizinho já foi colorido com a mesma cor, não é seguro
            if (nodes[i].obterCor() == cor)
            {
              return false;
            }
            break;
          }
        }
      }
    }
    return true;
  }

  // Algoritmo de backtracking recursivo
  bool backtrackingColoring(int nodeIndex, int k)
  {
    // Se todos os vértices foram coloridos, sucesso
    if (nodeIndex == (int)nodes.size())
    {
      return true;
    }

    // Tenta cada cor de 0 a k-1
    for (int cor = 0; cor < k; cor++)
    {
      // Verifica se é seguro colorir este vértice com esta cor
      if (corSegura(nodeIndex, cor))
      {
        // Atribui a cor
        nodes[nodeIndex].definirCor(cor);

        // Recursivamente tenta colorir os próximos vértices
        if (backtrackingColoring(nodeIndex + 1, k))
        {
          return true;
        }

        // Se não funcionou, remove a cor (backtrack)
        nodes[nodeIndex].resetarCor();
      }
    }

    // Se nenhuma cor funcionou, retorna false
    return false;
  }

public:
  Graph(std::vector<Node> nodes_, std::vector<Edge> edges_) : nodes(nodes_), edges(edges_)
  {
  }

  bool verificarSeEKColorivel(int k)
  {
    if (nodes.size() == 0)
    {
      return true;
    }

    // Reseta todas as cores
    for (auto &node : nodes)
    {
      node.resetarCor();
    }

    // Inicia o backtracking a partir do primeiro vértice
    return backtrackingColoring(0, k);
  }

  void imprimirColoring()
  {
    std::cout << "Coloração encontrada:\n";
    for (const auto &node : nodes)
    {
      std::cout << "Vértice " << node.obterId() << ": Cor " << node.obterCor() << "\n";
    }
  }

  ~Graph() {}
};

#endif