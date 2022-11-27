#include "Game.hpp"

#include <boxer/boxer.h>

int main()
{
    try
    {
        gr::Game game;
        game.run();
    }
    catch (std::exception& e)
    {
        boxer::show(e.what(), "Error!", boxer::Style::Error);
    }
}
