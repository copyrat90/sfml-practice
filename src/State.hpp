#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/Time.hpp>

#include <memory>

#include "ResourceId.hpp"
#include "StateId.hpp"

namespace sf
{
class RenderWindow;
class Event;
} // namespace sf

namespace gr
{

class StateStack;
class PlayerInputHandler;

class State : public sf::Drawable
{
public:
    using UPtr = std::unique_ptr<State>;

    struct Context
    {
        Context(sf::RenderWindow&, TextureHolder&, FontHolder&, PlayerInputHandler&);

        sf::RenderWindow& window;
        TextureHolder& textures;
        FontHolder& fonts;
        PlayerInputHandler& playerInputHandler;
    };

public:
    State(StateStack&, Context);

    /**
     * @return `bool` 스택 아래쪽 State의 handleEvent()도 호출돼야 하는지 여부
     */
    [[nodiscard]] virtual bool handleEvent(const sf::Event&) = 0;

    /**
     * @return `bool` 스택 아래쪽 State의 update()도 호출돼야 하는지 여부
     */
    [[nodiscard]] virtual bool update(sf::Time deltaTime) = 0;

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override = 0;

protected: // 서브클래스 샌드박스
    Context getContext() const;

    // 구체 State들이 StateStack과 직접 커플링되는 것을 분리
    void requestStateStackPush(StateId);
    void requestStateStackPop();
    void requestStateStackClear();

private:
    StateStack& _stateStack;
    Context _context;
};

} // namespace gr
