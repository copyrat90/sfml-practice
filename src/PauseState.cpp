#include "PauseState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "ResourceHolder.hpp"
#include "Util.hpp"

namespace gr
{

PauseState::PauseState(StateStack& stateStack, Context context)
    : State(stateStack, context), _darkRect(context.window.getView().getSize()),
      _pauseBigText("Game Paused", context.fonts.get(FontId::SANSATION), 50),
      _pauseSmallDescText("(Press Backspace to return to the main menu)", context.fonts.get(FontId::SANSATION))
{
    _darkRect.setFillColor(sf::Color(0, 0, 0, 128));

    util::centerOrigin(_pauseBigText);
    util::centerOrigin(_pauseSmallDescText);

    const auto& viewSize = context.window.getView().getSize();
    _pauseBigText.setPosition(viewSize / 2.f + sf::Vector2f(0, -30));
    _pauseSmallDescText.setPosition(viewSize / 2.f + sf::Vector2f(0, 30));
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        const auto& keyCode = event.key.code;
        if (keyCode == sf::Keyboard::Escape)
        {
            requestStateStackPop();
        }
        else if (keyCode == sf::Keyboard::Backspace)
        {
            requestStateStackClear();
            requestStateStackPush(StateId::MENU);
        }
    }

    // StateStack 밑에 있는 상태는 handleEvent() 호출 안함
    return false;
}

bool PauseState::update(sf::Time deltaTime)
{
    // StateStack 밑에 있는 상태는 update() 호출 안함
    return false;
}

void PauseState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());

    target.draw(_darkRect, states);
    target.draw(_pauseBigText, states);
    target.draw(_pauseSmallDescText, states);
}

} // namespace gr
