#include "TitleState.hpp"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "ResourceHolder.hpp"
#include "Util.hpp"

namespace gr
{

TitleState::TitleState(StateStack& stateStack, Context context)
    : State(stateStack, context), _bgSprite(context.textures.get(TextureId::TITLE_SCREEN)),
      _text("Press any key to start", context.fonts.get(FontId::SANSATION)), _isTextVisible(true)
{
    util::centerOrigin(_text);
    _text.setPosition(context.window.getView().getSize() / 2.f);
}

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        requestStateStackPop();
        requestStateStackPush(StateId::MENU);
    }

    return true;
}

bool TitleState::update(sf::Time deltaTime)
{
    const sf::Time TEXT_FLICKER_TIME = sf::seconds(0.5);

    _textFlickerTimer += deltaTime;
    if (_textFlickerTimer >= TEXT_FLICKER_TIME)
    {
        _textFlickerTimer -= TEXT_FLICKER_TIME;
        _isTextVisible = !_isTextVisible;
    }

    return true;
}

void TitleState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_bgSprite, states);

    if (_isTextVisible)
        target.draw(_text, states);
}

} // namespace gr
