#pragma once

#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

#include "Button.h"
#include "Attack.h"
#include "HealthBar.h"

class Application : public sf::RenderWindow
{
private:
    sf::Music musicTrack; // the music to be played while fighting

    // The amount of attacks performed by greg
    unsigned int attackCount;

    // The index of the current attack
    unsigned int attackIndex;

    unsigned int gamePhase; // the current thing the player is doing

    bool canSpare; // whether the player can spare greg or not

    sf::Font messageFont; // the font greg speaks in
    sf::Text messageText; // the text that greg is saying
    sf::Clock cutsceneClock; // the timer for when the cutscenes end

    std::string genocideMessage; // what greg says at end of genocide run
    std::string pacifistMessage; // what greg says at end of pacifist run

    sf::Sprite gregSprite; // the image of the enemy
    sf::Texture gregTexture; // the texture applied to the enemy sprite
    
    int gregHp; // gregory's health
    HealthBar gregHpBar; // the health bar for greg

    sf::Texture soulTexture; // re-usable texture for all undertale-style souls
    sf::Sprite playerSoul; // the player's moveable soul
    int playerVel; // the player's speed

    int playerHp; // the player's health
    HealthBar playerHpBar; // the player's HP bar

    sf::RectangleShape attackArea; // the area in which the player is held within

    sf::Texture mercyTexture; // the image for the mercy button
    Button mercyBtn; // the mercy button

    sf::Texture fightTexture; // the image for the fight button
    Button fightBtn; // the fight button

    sf::SoundBuffer hitSoundBuf; // buffer for hit sound
    sf::Sound hitSound; // playerable hit sound object

    /* CUTSCENE SPEECH BUBBLE */
    sf::Texture speechBubbleTexture;
    sf::Sprite speechBubble;

    sf::Texture gameoverTexture; // texture for gameover screen
    sf::Texture genocideTexture; // texture for genocide ending screen
    sf::Texture pacifistTexture; // texture for pacifist ending screen

    sf::Sprite gameover; // gameover screen
    sf::Sprite genocide; // genocide ending screen
    sf::Sprite pacifist; // pacifist ending screen

    /* ATTACK CLOCK */
    sf::Clock attackClock;

    /* ATTACK TEXTURES*/
    sf::Texture iceCreamVanTexture;
    sf::Texture iceConeTexture;
    sf::Texture pencilTexture;

    /* ATTACK SPRITES*/
    Attack iceCreamVan;

    Attack iceCone1;
    Attack iceCone2;
    Attack iceCone3;

    Attack pencil1;
    Attack pencil2;

public:
    Application(); // construct variables and gamestates

    void load(); // called on first frame

    void updatef(); // called every frame before drawing

    void drawf(); // draws the items to the screen

    void nextAttack(); // goes to next attack

    /*
        the different things that can
        be happening to the player
    */
    enum gamePhases {
        CHOOSE, ATTACK,
        GENOCIDECUT, PACIFISTCUT,
        DEATH, PACIFIST, GENOCIDE
    };

    // different attacks
    enum attacks {
        ICECREAMVAN,
        ICECONE,
        PENCILS
    };

protected:
};

#endif // _APPLICATION_H