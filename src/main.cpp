#include <SFML/Graphics.hpp>
#include "../include/gameInterface/gameInterface.hpp"

int main()
{
    IsoRPG::Game g{};
    int res{g.loop()};
    return res;
}