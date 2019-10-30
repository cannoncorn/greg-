#pragma once

#ifndef _ATTACK_H
#define _ATTACK_H

#include <SFML/Graphics.hpp>

class Attack : public sf::Sprite
{
public:
    void setInitPos(); // makes the initial position the current position

    void reset(); // sets position to initial position

protected:
    sf::Vector2f initPos; // initial position of attack
};

#endif // _ATTACK_H