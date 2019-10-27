#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Button.h"
#include "HealthBar.h"

class Application : public sf::RenderWindow
{
private:
    /*
        The index of the current attack to keep
        track of where the player is up to
    */
    int attackIndex;

    int gamePhase; // the current thing the player is doing

    sf::Sprite gregSprite; // the image of the enemy
    sf::Texture gregTexture; // the texture applied to the enemy sprite
    int gregHp; // gregory's health

    HealthBar gregHpBar; // the health bar for greg

    sf::Texture soulTexture; // re-usable texture for all undertale-style souls
    sf::Sprite playerSoul; // the player's moveable soul
    int playerVel; // the player's speed
    int playerHp; // the player's health

    sf::RectangleShape attackArea; // the area in which the player is held within

    sf::Texture mercyTexture; // the image for the mercy button
    Button mercyBtn; // the mercy button

    sf::Texture fightTexture; // the image for the fight button
    Button fightBtn; // the fight button

public:
    Application(); // constructor

    void load(); // called on first frame

    void updatef(); // called every frame before drawing

    void drawf(); // draws the items to the screen

    /*
        the different things that can
        be happening to the player
    */
    enum gamePhases {
        CHOOSE,
        ATTACK
    };

protected:
};

#endif // _APPLICATION_H