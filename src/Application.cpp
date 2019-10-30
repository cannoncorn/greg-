#include "Application.h"

Application::Application()
{
    attackIndex = 0; // start with first attack

    /*
        start by letting the player choose mercy or fight
    */
    gamePhase = CHOOSE;

    playerVel = 3;
    playerHp = 20;

    gregHp = 20;

    canSpare = true;

    attackIndex = ICECREAMVAN;
}

void Application::load()
{
    gregTexture.loadFromFile("assets/greg.png"); // get greg image

    // initialise the greg sprite
    gregSprite.setTexture(gregTexture);
    gregSprite.setScale(0.45f, 0.45f);
    gregSprite.setPosition(sf::Vector2f(getSize().x / 2 - 64, 10));

    // gregory HP bar
    gregHpBar.resize(sf::Vector2f(200, 20));
    gregHpBar.place(sf::Vector2f((getSize().x / 2) - (gregHpBar.getSize().x / 2), 235));
    gregHpBar.setFillColor(sf::Color::Green);

    // initialise the area that the player soul can move within
    attackArea.setSize(sf::Vector2f(320, 240));
    attackArea.setPosition(sf::Vector2f(getSize().x / 2 - 160, 280));
    attackArea.setFillColor(sf::Color::Transparent);
    attackArea.setOutlineColor(sf::Color::White);
    attackArea.setOutlineThickness(5);

    soulTexture.loadFromFile("assets/soul.png"); // get soul image

    // initialise the player's moveable soul
    playerSoul.setTexture(soulTexture);
    playerSoul.setColor(sf::Color::Red);
    playerSoul.setScale(sf::Vector2f(1.5, 1.5));
    playerSoul.setPosition(sf::Vector2f(310, 380));

    // player HP bar
    playerHpBar.resize(sf::Vector2f(100, 35));
    playerHpBar.place(sf::Vector2f((getSize().x / 2) - (playerHpBar.getSize().x / 2), 560));
    playerHpBar.setFillColor(sf::Color::Yellow);

    fightTexture.loadFromFile("assets/fight.png"); // get fight button image
    mercyTexture.loadFromFile("assets/mercy.png"); // get mercy button image

    // size of buttons relative to size in pixels
    const float buttonScaleFactor = 1.7;

    // initialise fight button
    fightBtn.setTexture(fightTexture);
    fightBtn.setScale(sf::Vector2f(buttonScaleFactor, buttonScaleFactor));
    fightBtn.setPosition(sf::Vector2f(140, getSize().y-90));

    // initialise mercy button
    mercyBtn.setTexture(mercyTexture);
    mercyBtn.setScale(sf::Vector2f(buttonScaleFactor, buttonScaleFactor));
    mercyBtn.setPosition(sf::Vector2f(390, getSize().y-90));

    // initialise the sound to be played when the player is hit
    hitSoundBuf.loadFromFile("assets/hit.wav");
    hitSound.setBuffer(hitSoundBuf);

    /* ATTACK TEXTURES */
    iceCreamVanTexture.loadFromFile("assets/icecreamvan.png");
    iceConeTexture.loadFromFile("assets/cone.png");

    /* ATTACK SPRITES */

    // ice cream van
    iceCreamVan.setTexture(iceCreamVanTexture);
    iceCreamVan.setScale(sf::Vector2f(8, 8));
    iceCreamVan.setPosition(sf::Vector2f(500, 395));

    // ice cream cones
    const float coneScaleFactor = 2;

    iceCone1.setTexture(iceConeTexture);
    iceCone1.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone1.setPosition(sf::Vector2f(500, 280));

    iceCone2.setTexture(iceConeTexture);
    iceCone2.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone2.setPosition(sf::Vector2f(100, 370));

    iceCone3.setTexture(iceConeTexture);
    iceCone3.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone3.setPosition(sf::Vector2f(500, 450));
}

void Application::drawf()
{
    /*
        Health bar has it's own draw
        method where you pass draw target
    */
    gregHpBar.draw(*this);
    playerHpBar.draw(*this);

    draw(gregSprite); // draw greg

    /*
        draws what the player needs
        to choose an option
    */
    if (gamePhase == CHOOSE)
    {
        draw(fightBtn);
        draw(mercyBtn);
    }

    /*
        draws whatever is attacking the player
    */
    else if (gamePhase == ATTACK)
    {
        // if the ice cream van is attacking
        if(attackIndex == ICECREAMVAN)
        {
            draw(iceCreamVan); // draw ice cream van
        }
        // if the ice cream cones are attacking
        else if(attackIndex == ICECONE)
        {
            draw(iceCone1);
            draw(iceCone2);
            draw(iceCone3); // draw ice cream cones
        }
        
        draw(playerSoul); // draw player
    }

    draw(attackArea); // always on bottom
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
    if (gamePhase == CHOOSE)
    {
        // if the player wants to FIGHT
        if (fightBtn.isClicked(*this))
        {
            canSpare = false;

            hitSound.play();

            gregHpBar.setDamage(gregHp, 5);
            gregHp -= 5; // do damage

            gamePhase = ATTACK;
            attackClock.restart();
        }

        // if the player wants to SPARE
        if (mercyBtn.isClicked(*this))
        {
            gamePhase = ATTACK;
            attackClock.restart();
        }
    }

    /*
        do whatever needs to be done when
        the player is being attacked
    */
    else if (gamePhase == ATTACK) {
        
        // if the ice cream van is attacking
        if (attackIndex == ICECREAMVAN)
        {
            iceCreamVan.move(sf::Vector2f(-4, 0));

            // if the player is touching it
            if (iceCreamVan.getGlobalBounds().intersects(playerRect))
            {
                playerHpBar.setDamage(playerHp, 5); // update player HP bar
                playerHp -= 5;

                hitSound.play();
                
                nextAttack();
            }

            // when attack is over
            if (attackClock.getElapsedTime().asSeconds() > 3)
            {
                nextAttack();
            }

        }
        // if the cones are attacking
        else if (attackIndex == ICECONE)
        {
            int velocity = 3; // how fast the ice cream cones move

            iceCone1.move(sf::Vector2f(-velocity, 0));
            iceCone2.move(sf::Vector2f(velocity, 0));
            iceCone3.move(sf::Vector2f(-velocity, 0)); // move cones

            if (iceCone1.getGlobalBounds().intersects(playerRect) // if touching ice cone 1
            | iceCone2.getGlobalBounds().intersects(playerRect) // if touching ice cone 2
            | iceCone3.getGlobalBounds().intersects(playerRect)) // if touching ice cone 3
            {
                playerHpBar.setDamage(playerHp, 5); // update player HP bar
                playerHp -= 5;

                hitSound.play();

                nextAttack();
            }

            // when attack is over
            if (attackClock.getElapsedTime().asSeconds() > 3)
            {
                nextAttack();
            }
        }

        // check for keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & playerRect.top > areaRect.top+areaThickness)
            playerSoul.move(sf::Vector2f(0, -playerVel)); // move up
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & playerRect.left > areaRect.left+areaThickness)
            playerSoul.move(sf::Vector2f(-playerVel, 0)); // move left
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & playerRect.top+playerRect.height < areaRect.top+areaRect.height-areaThickness)
            playerSoul.move(sf::Vector2f(0, playerVel)); // move down
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & playerRect.left+playerRect.width < areaRect.left+areaRect.width-areaThickness)
            playerSoul.move(sf::Vector2f(playerVel, 0)); // move right
    }
}

void Application::nextAttack()
{
    attackIndex += 1; // go to next attack
    gamePhase = CHOOSE; // go back to player choosing phase

    /* RESET PLAYER POSITION */

    playerSoul.setPosition(sf::Vector2f(310, 380));

    /* RESET POSITIONS OF ATTACKS */

    iceCreamVan.setPosition(sf::Vector2f(500, 395));

    iceCone1.setPosition(sf::Vector2f(500, 280));
    iceCone2.setPosition(sf::Vector2f(100, 370));
    iceCone3.setPosition(sf::Vector2f(500, 450));
}