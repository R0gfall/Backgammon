#include "Input.h"


void Input::Update()
{
    _lastFrameKeys.SetMask(_thisFrameKeys);

    _thisFrameKeys.SetBit((int)Key::Left,
        (Keyboard::isKeyPressed(Keyboard::Left)) || (Keyboard::isKeyPressed(Keyboard::A)));

    _thisFrameKeys.SetBit((int)Key::Right,
        (Keyboard::isKeyPressed(Keyboard::Right)) || (Keyboard::isKeyPressed(Keyboard::D)));

    _thisFrameKeys.SetBit((int)Key::Up,
        (Keyboard::isKeyPressed(Keyboard::Up)) || (Keyboard::isKeyPressed(Keyboard::W)));

    _thisFrameKeys.SetBit((int)Key::Down,
        (Keyboard::isKeyPressed(Keyboard::Down)) || (Keyboard::isKeyPressed(Keyboard::S)));

    _thisFrameKeys.SetBit((int)Key::Horizontal,
        (_thisFrameKeys.GetBit((int)Key::Left) || _thisFrameKeys.GetBit((int)Key::Right)));

    _thisFrameKeys.SetBit((int)Key::Vertical,
        (_thisFrameKeys.GetBit((int)Key::Up) || _thisFrameKeys.GetBit((int)Key::Down)));

    _thisFrameKeys.SetBit((int)Key::Esc, Keyboard::isKeyPressed(Keyboard::Escape));

    _thisFrameKeys.SetBit((int)Key::LBracket, Keyboard::isKeyPressed(Keyboard::LBracket));
    _thisFrameKeys.SetBit((int)Key::RBracket, Keyboard::isKeyPressed(Keyboard::RBracket));

    _thisFrameKeys.SetBit((int)Key::Space, Keyboard::isKeyPressed(Keyboard::Space));
    _thisFrameKeys.SetBit((int)Key::LShift, Keyboard::isKeyPressed(Keyboard::LShift));
    _thisFrameKeys.SetBit((int)Key::RShift, Keyboard::isKeyPressed(Keyboard::RShift));

    _thisFrameKeys.SetBit((int)Key::LMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Left));
    _thisFrameKeys.SetBit((int)Key::RMouseButton, sf::Mouse::isButtonPressed(sf::Mouse::Right));

    _thisFrameKeys.SetBit((int)Key::Q, Keyboard::isKeyPressed(Keyboard::Q));
    _thisFrameKeys.SetBit((int)Key::W, Keyboard::isKeyPressed(Keyboard::W));
    _thisFrameKeys.SetBit((int)Key::E, Keyboard::isKeyPressed(Keyboard::E));
    _thisFrameKeys.SetBit((int)Key::R, Keyboard::isKeyPressed(Keyboard::R));
    _thisFrameKeys.SetBit((int)Key::T, Keyboard::isKeyPressed(Keyboard::T));
    _thisFrameKeys.SetBit((int)Key::Y, Keyboard::isKeyPressed(Keyboard::Y));
    _thisFrameKeys.SetBit((int)Key::U, Keyboard::isKeyPressed(Keyboard::U));
    _thisFrameKeys.SetBit((int)Key::I, Keyboard::isKeyPressed(Keyboard::I));
    _thisFrameKeys.SetBit((int)Key::O, Keyboard::isKeyPressed(Keyboard::O));
    _thisFrameKeys.SetBit((int)Key::P, Keyboard::isKeyPressed(Keyboard::P));
    _thisFrameKeys.SetBit((int)Key::A, Keyboard::isKeyPressed(Keyboard::A));
    _thisFrameKeys.SetBit((int)Key::S, Keyboard::isKeyPressed(Keyboard::S));
    _thisFrameKeys.SetBit((int)Key::D, Keyboard::isKeyPressed(Keyboard::D));
    _thisFrameKeys.SetBit((int)Key::F, Keyboard::isKeyPressed(Keyboard::F));
    _thisFrameKeys.SetBit((int)Key::G, Keyboard::isKeyPressed(Keyboard::G));
    _thisFrameKeys.SetBit((int)Key::H, Keyboard::isKeyPressed(Keyboard::H));
    _thisFrameKeys.SetBit((int)Key::J, Keyboard::isKeyPressed(Keyboard::J));
    _thisFrameKeys.SetBit((int)Key::K, Keyboard::isKeyPressed(Keyboard::K));
    _thisFrameKeys.SetBit((int)Key::L, Keyboard::isKeyPressed(Keyboard::L));
    _thisFrameKeys.SetBit((int)Key::Z, Keyboard::isKeyPressed(Keyboard::Z));
    _thisFrameKeys.SetBit((int)Key::X, Keyboard::isKeyPressed(Keyboard::X));
    _thisFrameKeys.SetBit((int)Key::C, Keyboard::isKeyPressed(Keyboard::C));
    _thisFrameKeys.SetBit((int)Key::V, Keyboard::isKeyPressed(Keyboard::V));
    _thisFrameKeys.SetBit((int)Key::B, Keyboard::isKeyPressed(Keyboard::B));
    _thisFrameKeys.SetBit((int)Key::N, Keyboard::isKeyPressed(Keyboard::N));
    _thisFrameKeys.SetBit((int)Key::M, Keyboard::isKeyPressed(Keyboard::M));

}

bool Input::IsKeyPressed(Key keycode)
{
    return _thisFrameKeys.GetBit((int)keycode);
}

bool Input::IsKeyDown(Key keycode)
{
    bool lastFrame = _lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = _thisFrameKeys.GetBit((int)keycode);

    return thisFrame && !lastFrame;
}

bool Input::IsKeyUp(Key keycode)
{
    bool lastFrame = _lastFrameKeys.GetBit((int)keycode);
    bool thisFrame = _thisFrameKeys.GetBit((int)keycode);

    return !thisFrame && lastFrame;
}


Bitmask Input::_thisFrameKeys;
Bitmask Input::_lastFrameKeys;

