#include "SettingsState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceHolder.hpp"
#include "Util.hpp"

namespace gr
{

SettingsState::SettingsState(StateStack& stateStack, Context context)
    : State(stateStack, context), _bgSprite(context.textures.get(TextureId::TITLE_SCREEN))
{
    addButtonWithLabel(PlayerInputHandler::Action::MOVE_UP, "Move Up", 150.f);
    addButtonWithLabel(PlayerInputHandler::Action::MOVE_DOWN, "Move Down", 200.f);
    addButtonWithLabel(PlayerInputHandler::Action::MOVE_LEFT, "Move Left", 250.f);
    addButtonWithLabel(PlayerInputHandler::Action::MOVE_RIGHT, "Move Right", 300.f);

    auto backBtn = std::make_unique<gui::Button>(context.fonts, context.textures);
    backBtn->setPosition(80.f, 375.f);
    backBtn->setString("Back");
    backBtn->setCallback([this]() {
        requestStateStackPop();
        requestStateStackPush(StateId::MENU);
    });

    _guiContainer.addComponent(std::move(backBtn));
}

bool SettingsState::handleEvent(const sf::Event& event)
{
    bool isBindingOngoing = false;
    using Action = PlayerInputHandler::Action;
    for (auto action = Action::MOVE_UP; action < Action::TOTAL_COUNT; action = Action(action + 1))
    {
        auto button = _buttons[action];
        if (button->isActive())
        {
            isBindingOngoing = true;
            if (event.type == sf::Event::KeyPressed)
            {
                getContext().playerInputHandler.bindKey(event.key.code, action);
                button->deactivate();
                updateLabels();
            }
            break;
        }
    }

    if (!isBindingOngoing)
        _guiContainer.handleEvent(event);

    return true;
}

bool SettingsState::update(sf::Time deltaTime)
{
    return true;
}

void SettingsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_bgSprite, states);
    target.draw(_guiContainer, states);
}

void SettingsState::addButtonWithLabel(PlayerInputHandler::Action playerAction, const std::string& buttonStr, float y)
{
    const auto ctx = getContext();
    const auto boundKey = ctx.playerInputHandler.getBoundKey(playerAction);

    gui::Button::UPtr button = std::make_unique<gui::Button>(ctx.fonts, ctx.textures);
    gui::Label::UPtr label = std::make_unique<gui::Label>(util::toString(boundKey), ctx.fonts);

    button->setPosition(80.f, y);
    button->setString(buttonStr);
    button->setHoldable(true);

    label->setPosition(300.f, y + 15.f);

    _buttons[playerAction] = button.get();
    _labels[playerAction] = label.get();

    _guiContainer.addComponent(std::move(button));
    _guiContainer.addComponent(std::move(label));
}

void SettingsState::updateLabels()
{
    using Action = PlayerInputHandler::Action;
    for (auto action = Action::MOVE_UP; action < Action::TOTAL_COUNT; action = Action(action + 1))
    {
        auto label = _labels[action];
        label->setString(util::toString(getContext().playerInputHandler.getBoundKey(action)));
    }
}

} // namespace gr
