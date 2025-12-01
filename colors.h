#ifndef COLOR_H
#define COLOR_H

#include <vector>

class Color
{
private:
  std::vector<bool> availableColors;
  int corAtribuida; // Armazena a cor atribuída explicitamente (-1 se nenhuma)

public:
  Color(int maxColors) : availableColors(maxColors, true), corAtribuida(-1) {};

  void removerCor(int cor)
  {
    if (cor < 0)
      return;
    availableColors[cor] = false;
  }

  int pegarProximaCorDisponivel()
  {
    auto it = std::find_if(this->availableColors.begin(), this->availableColors.end(), [](const auto &c)
                           { return c; });

    if (it != this->availableColors.end())
    {
      return std::distance(this->availableColors.begin(), it);
    }

    return -1;
  }

  bool temCorValida()
  {
    auto it = std::find_if(this->availableColors.begin(), this->availableColors.end(), [](const auto &c)
                           { return c; });

    return it != this->availableColors.end();
  }

  void definirCor(int cor)
  {
    if (cor >= 0 && cor < (int)availableColors.size())
    {
      corAtribuida = cor;
    }
    else
    {
      corAtribuida = -1;
    }
  }

  int obterCorAtual() const
  {
    return corAtribuida;
  }

  bool corDisponivel(int cor)
  {
    if (cor < 0 || cor >= (int)availableColors.size())
      return false;
    return availableColors[cor];
  }

  void resetar()
  {
    std::fill(availableColors.begin(), availableColors.end(), true);
    corAtribuida = -1;
  }

  friend std::ostream &operator<<(std::ostream &out, const Color &color);
};

std::ostream &operator<<(std::ostream &out, const Color &color)
{
  auto it = std::find_if(color.availableColors.begin(), color.availableColors.end(), [](const auto &c)
                         { return c; });
  out << std::distance(color.availableColors.begin(), it);
  return out;
}

#endif