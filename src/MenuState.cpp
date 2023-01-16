#include "MenuState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

#include "ResourceHolder.hpp"
#include "gui/Button.hpp"

namespace gr
{

MenuState::MenuState(StateStack& stateStack, Context context)
    : State(stateStack, context), _bgSprite(context.textures.get(TextureId::TITLE_SCREEN))
{
    auto playBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    playBtn->setString("Play");
    playBtn->setPosition(100, 250);
    playBtn->setCallback([this]() {
        requestStateStackPop();
        requestStateStackPush(StateId::GAME);
    });

    auto settingsBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    settingsBtn->setString("Settings");
    settingsBtn->setPosition(100, 300);
    settingsBtn->setCallback([this]() {
        requestStateStackPop();
        requestStateStackPush(StateId::SETTINGS);
    });

    auto exitBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    exitBtn->setString("Exit");
    exitBtn->setPosition(100, 350);
    exitBtn->setCallback([this]() { requestStateStackClear(); });

    _guiContainer.addComponent(std::move(playBtn));
    _guiContainer.addComponent(std::move(settingsBtn));
    _guiContainer.addComponent(std::move(exitBtn));
}

bool MenuState::handleEvent(const sf::Event& event)
{
    _guiContainer.handleEvent(event);

    return true;
}

bool MenuState::update(sf::Time deltaTime)
{
    return true;
}

void MenuState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.setView(target.getDefaultView());

    target.draw(_bgSprite, states);
    target.draw(_guiContainer, states);
}

} // namespace gr
