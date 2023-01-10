#include "MenuState.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <stdexcept>

#include "ResourceHolder.hpp"
#include "Util.hpp"

namespace gr
{

MenuState::MenuState(StateStack& stateStack, Context context)
    : State(stateStack, context), _bgSprite(context.textures.get(TextureId::TITLE_SCREEN)),
      _cursorOption(MenuOption::PLAY)
{
    _texts[MenuOption::PLAY].setString("Play");
    _texts[MenuOption::EXIT].setString("Exit");

    for (int i = 0; i < _texts.size(); ++i)
    {
        auto& text = _texts[i];
        text.setFont(context.fonts.get(FontId::SANSATION));
        util::centerOrigin(text);

        text.setPosition(context.window.getView().getSize() / 2.f + sf::Vector2f{0, 30.f * i});
    }
    updateOptionText();
}

bool MenuState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        const auto keyCode = event.key.code;

        if (keyCode == sf::Keyboard::Enter)
        {
            if (_cursorOption == MenuOption::PLAY)
            {
                requestStateStackPop();
                requestStateStackPush(StateId::GAME);
            }
            else if (_cursorOption == MenuOption::EXIT)
            {
                requestStateStackClear();
            }
            else
            {
                throw std::logic_error("Unknown _cursorOption=" + std::to_string(_cursorOption));
            }
        }

        else if (keyCode == sf::Keyboard::Up)
        {
            _cursorOption =
                static_cast<MenuOption>((_cursorOption - 1 + MenuOption::TOTAL_COUNT) % MenuOption::TOTAL_COUNT);
            updateOptionText();
        }

        else if (keyCode == sf::Keyboard::Down)
        {
            _cursorOption = static_cast<MenuOption>((_cursorOption + 1) % MenuOption::TOTAL_COUNT);
            updateOptionText();
        }
    }

    return true;
}

bool MenuState::update(sf::Time deltaTime)
{
    return true;
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());

    target.draw(_bgSprite);

    for (const auto& text : _texts)
        target.draw(text);
}

void MenuState::updateOptionText()
{
    for (auto& text : _texts)
        text.setFillColor(sf::Color::White);

    _texts[_cursorOption].setFillColor(sf::Color::Red);
}

} // namespace gr
