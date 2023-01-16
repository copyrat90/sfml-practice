#pragma once

#include "State.hpp"

#include <SFML/Graphics/Sprite.hpp>

#include "PlayerInputHandler.hpp"
#include "gui/Button.hpp"
#include "gui/Container.hpp"
#include "gui/Label.hpp"

namespace gr
{

class SettingsState final : public State
{
public:
    SettingsState(StateStack&, Context);

    bool handleEvent(const sf::Event&) override;
    bool update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    void addButtonWithLabel(PlayerInputHandler::Action playerAction, const std::string& buttonStr, float y);
    void updateLabels();

private:
    sf::Sprite _bgSprite;

    gui::Container _guiContainer;
    gui::Button* _buttons[PlayerInputHandler::Action::TOTAL_COUNT];
    gui::Label* _labels[PlayerInputHandler::Action::TOTAL_COUNT];
};

} // namespace gr
