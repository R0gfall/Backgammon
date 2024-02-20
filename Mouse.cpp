#include "Mouse.h"

sf::Vector2f Mouse::GetRelativePosition()
{
    return sf::Vector2f(sf::Mouse::getPosition(Window::Instance()->GetSfWindow()));
}

void Mouse::Update()
{
    _lastFrameKeys.SetMask(_thisFrameKeys);

    _thisFrameKeys.SetBit((int)Key::LMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    _thisFrameKeys.SetBit((int)Key::RMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Right));
}

bool Mouse::IsLMBDown(Key keycode)
{
    bool lastFrame = _lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = _thisFrameKeys.GetBit((int)keycode);

    return thisFrame && !lastFrame;
}

bool Mouse::IsLMBPressed(Key keycode)
{
    return _thisFrameKeys.GetBit((int)keycode);;
}

bool Mouse::IsLMBUp(Key keycode)
{
    bool lastFrame = _lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = _thisFrameKeys.GetBit((int)keycode);

    return !thisFrame && lastFrame;
}

Bitmask Mouse::_thisFrameKeys;
Bitmask Mouse::_lastFrameKeys;
