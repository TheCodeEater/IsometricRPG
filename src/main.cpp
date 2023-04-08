#include <SFML/Graphics.hpp>

#include "../include/gameInterface/gameInterface.hpp"
#include "../include/gameInterface/gameScreens.hpp"

int main() {
  IsoRPG::Game g{};
  g.setCurrentWindow(new IsoRPG::MainMenu(g.getSFMLWindow()));
  int res{g.loop()};
  return res;
}