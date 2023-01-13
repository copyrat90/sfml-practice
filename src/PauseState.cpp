#include "PauseState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "ResourceHolder.hpp"
#include "Util.hpp"
#include "gui/Button.hpp"

namespace gr
{

PauseState::PauseState(StateStack& stateStack, Context context)
    : State(stateStack, context), _darkRect(context.window.getView().getSize()),
      _pauseText("Game Paused", context.fonts.get(FontId::SANSATION), 60)
{
    _darkRect.setFillColor(sf::Color(0, 0, 0, 128));

    util::centerOrigin(_pauseText);
    const auto& viewSize = context.window.getView().getSize();
    const auto pauseTextPos = viewSize / 2.f + sf::Vector2f(0, -50);
    _pauseText.setPosition(pauseTextPos);

    auto returnBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    returnBtn->setString("Return");
    returnBtn->setPosition(pauseTextPos + sf::Vector2f(-100, 70));
    returnBtn->setCallback([this]() { requestStateStackPop(); });

    auto backToMenuBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    backToMenuBtn->setString("Back to menu");
    backToMenuBtn->setPosition(pauseTextPos + sf::Vector2f(-100, 120));
    backToMenuBtn->setCallback([this]() {
        requestStateStackClear();
        requestStateStackPush(StateId::MENU);
    });

    _guiContainer.addComponent(std::move(returnBtn));
    _guiContainer.addComponent(std::move(backToMenuBtn));
}

bool PauseState::handleEvent(const sf::Event& event)
{
    _guiContainer.handleEvent(event);

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
    target.draw(_pauseText, states);
    target.draw(_guiContainer, states);
}

} // namespace gr
