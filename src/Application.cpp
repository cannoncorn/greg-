#include "Application.h"

Application::Application()
{
    playerVel = 3;
}

void Application::load()
{
    gregTexture.loadFromFile("assets/greg.png");

    gregSprite.setTexture(gregTexture);
    gregSprite.setScale(0.5f, 0.5f);
    gregSprite.setPosition(sf::Vector2f(getSize().x / 2 - 64, 15));

    attackArea.setSize(sf::Vector2f(320, 240));
    attackArea.setPosition(sf::Vector2f(getSize().x / 2 - 160, 280));
    attackArea.setFillColor(sf::Color::Black);
    attackArea.setOutlineColor(sf::Color::White);
    attackArea.setOutlineThickness(5);

    soulTexture.loadFromFile("assets/soul.png");

    playerSoul.setTexture(soulTexture);
    playerSoul.setColor(sf::Color::Red);
    playerSoul.setScale(sf::Vector2f(1.5, 1.5));
    playerSoul.setPosition(sf::Vector2f(360, 360));
}

void Application::drawf()
{
    draw(gregSprite);
    draw(attackArea);
    draw(playerSoul);
}

void Application::updatef()
{
    sf::Vector2f oldPlayerPos = playerSoul.getPosition();

    sf::FloatRect areaRect = attackArea.getGlobalBounds();
    sf::FloatRect playerRect = playerSoul.getGlobalBounds();

    float areaThickness = attackArea.getOutlineThickness();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & playerRect.top > areaRect.top+areaThickness)
        playerSoul.move(sf::Vector2f(0, -playerVel));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & playerRect.left > areaRect.left+areaThickness)
        playerSoul.move(sf::Vector2f(-playerVel, 0));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & playerRect.top+playerRect.height < areaRect.top+areaRect.height-areaThickness)
        playerSoul.move(sf::Vector2f(0, playerVel));
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & playerRect.left+playerRect.width < areaRect.left+areaRect.width-areaThickness)
        playerSoul.move(sf::Vector2f(playerVel, 0));
}