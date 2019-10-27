#include "Application.h"

Application::Application()
{
    attackIndex = 0; // start with first attack

    /*
        start by letting the player choose mercy or fight
    */
    gamePhase = CHOOSE;

    playerVel = 3;
}

void Application::load()
{
    gregTexture.loadFromFile("assets/greg.png"); // get greg image

    // initialise the greg sprite
    gregSprite.setTexture(gregTexture);
    gregSprite.setScale(0.5f, 0.5f);
    gregSprite.setPosition(sf::Vector2f(getSize().x / 2 - 64, 15));

    // initialise the area that the player soul can move within
    attackArea.setSize(sf::Vector2f(320, 240));
    attackArea.setPosition(sf::Vector2f(getSize().x / 2 - 160, 280));
    attackArea.setFillColor(sf::Color::Black);
    attackArea.setOutlineColor(sf::Color::White);
    attackArea.setOutlineThickness(5);

    soulTexture.loadFromFile("assets/soul.png"); // get soul image

    // initialise the player's moveable soul
    playerSoul.setTexture(soulTexture);
    playerSoul.setColor(sf::Color::Red);
    playerSoul.setScale(sf::Vector2f(1.5, 1.5));
    playerSoul.setPosition(sf::Vector2f(360, 360));

    mercyTexture.loadFromFile("assets/mercy.png"); // get mercy button image

    // initialise mercy button
    mercyBtn.setTexture(mercyTexture);
    mercyBtn.setScale(sf::Vector2f(1.7, 1.7));
    mercyBtn.setPosition(sf::Vector2f(350, getSize().y-90));
}

void Application::drawf()
{
    draw(gregSprite);
    draw(attackArea);

    if (gamePhase == CHOOSE)
    {
        draw(mercyBtn);
    }

    else if (gamePhase == ATTACK)
    {
        draw(playerSoul);
    }
}

void Application::updatef()
{
    // the rect that the playing area is located within
    sf::FloatRect areaRect = attackArea.getGlobalBounds();

    // the rect that the player is located within
    sf::FloatRect playerRect = playerSoul.getGlobalBounds();

    // the thickness of the playing area's border
    float areaThickness = attackArea.getOutlineThickness();

    /*
        do whatever needs to be done when the player is
        currently choosing their actions
    */
    if (gamePhase == CHOOSE) {

        if (mercyBtn.isClicked(*this))
        {
            gamePhase = ATTACK;
        }
    }

    /*
        do whatever needs to be done when
        the player is being attacked
    */
    else if (gamePhase == ATTACK) {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & playerRect.top > areaRect.top+areaThickness)
            playerSoul.move(sf::Vector2f(0, -playerVel));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & playerRect.left > areaRect.left+areaThickness)
            playerSoul.move(sf::Vector2f(-playerVel, 0));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & playerRect.top+playerRect.height < areaRect.top+areaRect.height-areaThickness)
            playerSoul.move(sf::Vector2f(0, playerVel));
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & playerRect.left+playerRect.width < areaRect.left+areaRect.width-areaThickness)
            playerSoul.move(sf::Vector2f(playerVel, 0));   
    }
}