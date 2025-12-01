#ifndef NODE_H
#define NODE_H

#include "colors.h"

struct Node
{
private:
  Color color;
  int id;

public:
  Node(int id_, int maxColors) : color(maxColors), id(id_)
  {
  }

  bool compararValorNo(Node &node)
  {
    return node.id == this->id;
  }

  void removerCor(int cor)
  {
    this->color.removerCor(cor);
  }

  int pegarProximaCorDisponivel()
  {
    return this->color.pegarProximaCorDisponivel();
  }

  bool temCorValida()
  {
    return color.temCorValida();
  }

  void definirCor(int cor)
  {
    this->color.definirCor(cor);
  }

  int obterId() const
  {
    return this->id;
  }

  int obterCor() const
  {
    return this->color.obterCorAtual();
  }

  void resetarCor()
  {
    this->color.resetar();
  }

  friend std::ostream &operator<<(std::ostream &out, const Node &node);
};

std::ostream &operator<<(std::ostream &out, const Node &node)
{
  out << "id: " << node.id << " cor: " << node.color;
  return out;
}

#endif