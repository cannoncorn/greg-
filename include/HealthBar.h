#pragma once

#ifndef _HEALTHBAR_H
#define _HEALTHBAR_H

#include <SFML/Graphics.hpp>

class HealthBar : public sf::RectangleShape
{
private:
    sf::RectangleShape background; // background

public:
    HealthBar();

    void resize(sf::Vector2f vec); // resizes both self and background

    void place(sf::Vector2f vec); // places both self and background

    void draw(sf::RenderTarget &win); // draws both self and background

    void setDamage(int oldhp, int dmg); // sets size based on hp - dmg

protected:
};

#endif // _HEALTHBAR_H