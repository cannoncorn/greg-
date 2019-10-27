#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SFML/Graphics.hpp>

class Application : public sf::RenderWindow
{
private:
    sf::Sprite gregSprite;
    sf::Texture gregTexture;

    sf::Texture soulTexture;
    sf::Sprite playerSoul;
    int playerVel;

    sf::RectangleShape attackArea;

public:
    Application();

    void load();

    void updatef();

    void drawf();

protected:
};

#endif // _APPLICATION_H