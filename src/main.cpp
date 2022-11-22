#include <SFML/Graphics.hpp>
#include <boxer/boxer.h>

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                boxer::show("Window will now be closed.", "Close requested");
                window.close();
            }
        }

        window.clear();
        window.display();
    }
}
