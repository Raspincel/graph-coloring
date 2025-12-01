#ifndef COLOR_H
#define COLOR_H

#include <vector>

class Color
{
private:
  std::vector<bool> availableColors;

public:
  Color(int maxColors) : availableColors(maxColors, true) {};

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