#include <stdexcept>

#include <SFML/Graphics.hpp>
#include <boxer/boxer.h>

#include "ResourceHolder.hpp"

enum class TextureId
{
    SPLASH_RAT,

    MAX_COUNT
};

int main()
{
    sf::RenderWindow window{{1280, 720}, "SFML Practice"};
    window.setFramerateLimit(95);

    gr::ResourceHolder<sf::Texture, TextureId, (int)TextureId::MAX_COUNT> textureHolder;
    try
    {
        textureHolder.loadFromFile(TextureId::SPLASH_RAT, "assets/graphics/splash_rat.png");
    }
    catch (std::runtime_error& e)
    {
        boxer::show(e.what(), "Texture load error");
        return 1;
    }

    sf::Sprite sprite(textureHolder.get(TextureId::SPLASH_RAT));
    sprite.setPosition(100, 100);

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
        window.draw(sprite);
        window.display();
    }
}
