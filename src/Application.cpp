#include "Application.h"

using namespace std;

Application::Application()
{
    gamePhase = CHOOSE;

    attackCount = 1;

    playerVel = 3;
    playerHp = 20;

    gregHp = 35;

    canSpare = true;

    attackIndex = ICECREAMVAN;

    genocideMessage += "You are but a mere mortal.\n";
    genocideMessage += "Yet you still defeated me...";

    pacifistMessage += "Maybe there is more to\n";
    pacifistMessage += "to life than killing and\n";
    pacifistMessage += "kidnapping people...";
}

void Application::load()
{
    // initialise music track
    musicTrack.setLoop(true);
    musicTrack.openFromFile("assets/music.wav");

    gregTexture.loadFromFile("assets/greg.png"); // get greg image

    messageFont.loadFromFile("assets/fonts/bst-light.ttf"); // load greg font


    // initialise message text
    messageText.setFont(messageFont);
    messageText.setCharacterSize(20);
    messageText.setStyle(sf::Text::Bold);
    messageText.setFillColor(sf::Color::Black);
    messageText.setPosition(410, 50);

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

    /* CUTSCENE SPEECH BUBBLE */
    speechBubbleTexture.loadFromFile("assets/textbox.png");
    speechBubble.setTexture(speechBubbleTexture);
    speechBubble.setScale(sf::Vector2f(8, 8));
    speechBubble.setPosition(sf::Vector2f(380, 40));

    /* OUTCOME SCREEN TEXTURES */
    gameoverTexture.loadFromFile("assets/gameover.png");
    genocideTexture.loadFromFile("assets/genocide.png");
    pacifistTexture.loadFromFile("assets/pacifist.png");

    /* OUTCOME SCREENS */

    // game over
    gameover.setTexture(gameoverTexture);

    // genocide ending
    genocide.setTexture(genocideTexture);

    // pacifist ending
    pacifist.setTexture(pacifistTexture);

    /* ATTACK TEXTURES */
    iceCreamVanTexture.loadFromFile("assets/icecreamvan.png");
    iceConeTexture.loadFromFile("assets/cone.png");
    pencilTexture.loadFromFile("assets/pencil.png");

    /* ATTACK SPRITES */

    // ice cream van
    iceCreamVan.setTexture(iceCreamVanTexture);
    iceCreamVan.setScale(sf::Vector2f(8, 8));
    iceCreamVan.setPosition(sf::Vector2f(500, 395));
    iceCreamVan.setInitPos();

    // ice cream cones
    const float coneScaleFactor = 2;

    iceCone1.setTexture(iceConeTexture);
    iceCone1.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone1.setPosition(sf::Vector2f(500, 280));
    iceCone1.setInitPos(); // set initial position

    iceCone2.setTexture(iceConeTexture);
    iceCone2.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone2.setPosition(sf::Vector2f(100, 370));
    iceCone2.setInitPos(); // set initial position

    iceCone3.setTexture(iceConeTexture);
    iceCone3.setScale(sf::Vector2f(coneScaleFactor, coneScaleFactor));
    iceCone3.setPosition(sf::Vector2f(500, 450));
    iceCone3.setInitPos(); // set initial position

    // pencils
    const float pencilScaleFactor = 2;

    pencil1.setTexture(pencilTexture);
    pencil1.setScale(sf::Vector2f(pencilScaleFactor, pencilScaleFactor));
    pencil1.setPosition(sf::Vector2f(500, 300));
    pencil1.setInitPos(); // set initial position

    pencil2.setTexture(pencilTexture);
    pencil2.setScale(sf::Vector2f(pencilScaleFactor, pencilScaleFactor));
    pencil2.setPosition(sf::Vector2f(500, 380));
    pencil2.setInitPos(); // set initial position

    musicTrack.play();
}

void Application::drawf()
{
    draw(attackArea); // always on bottom

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
        // if the pencils are attacking
        else if(attackIndex == PENCILS)
        {
            draw(pencil1);
            draw(pencil2); // draw pencils
        }
        
        draw(playerSoul); // draw player
    }
    /*
        draw the death screen
    */
    else if (gamePhase == DEATH)
    {
        draw(gameover);
    }
    /*
        draw the genocide ending screen
    */
    else if (gamePhase == GENOCIDE)
    {
        draw(genocide);
    }
    /*
        draw the pacifist ending screen
    */
    else if (gamePhase == PACIFIST)
    {
        draw(pacifist);
    }
    /*
        draw what is needed for both cutscenes
    */
    else if (gamePhase == PACIFISTCUT | gamePhase == GENOCIDECUT)
    {
        draw(speechBubble);
        draw(messageText);
    }
}

void Application::updatef()
{
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

        // the rect that the player is located within
        sf::FloatRect playerRect = playerSoul.getGlobalBounds();

        // the rect that the playing area is located within
        sf::FloatRect areaRect = attackArea.getGlobalBounds();

        // the thickness of the playing area's border
        float areaThickness = attackArea.getOutlineThickness();
        
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
        // if the pencils are attacking
        else if (attackIndex == PENCILS)
        {
            int velocity = 7; // how fast the pencils move

            pencil1.move(sf::Vector2f(-velocity, 0));
            pencil2.move(sf::Vector2f(-velocity, 0)); // move pencils

            if (pencil1.getGlobalBounds().intersects(playerRect) // if touching pencil 1
            | pencil2.getGlobalBounds().intersects(playerRect)) // if touching pencil 2
            {
                playerHpBar.setDamage(playerHp, 5); // update player HP bar
                playerHp -= 5;

                hitSound.play();

                nextAttack();
            }

            // when attack is over
            if (attackClock.getElapsedTime().asSeconds() > 1.5)
            {
                nextAttack();
            }
        }

        // check for keyboard input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) & playerRect.top > areaRect.top+areaThickness)
        {
            playerSoul.move(sf::Vector2f(0, -playerVel)); // move up
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) & playerRect.left > areaRect.left+areaThickness)
        {
            playerSoul.move(sf::Vector2f(-playerVel, 0)); // move left
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) & playerRect.top+playerRect.height < areaRect.top+areaRect.height-areaThickness)
        {
            playerSoul.move(sf::Vector2f(0, playerVel)); // move down
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) & playerRect.left+playerRect.width < areaRect.left+areaRect.width-areaThickness)
        {
            playerSoul.move(sf::Vector2f(playerVel, 0)); // move right
        }
    }

    /*
        do what needs to be done during
        pacifist ending cutscene
    */
    else if (gamePhase == PACIFISTCUT)
    {
        // set message text string
        messageText.setString(pacifistMessage);
        if (cutsceneClock.getElapsedTime().asSeconds() > 4)
        {
            gamePhase = PACIFIST; // go to end screen
        }
    }

    /*
        do what needs to be done during genocide ending cutscene
    */
    else if (gamePhase == GENOCIDECUT)
    {
        // set message text string
        messageText.setString(genocideMessage);
        if (cutsceneClock.getElapsedTime().asSeconds() > 4)
        {
            gamePhase = GENOCIDE; // go to end screen
        }
    }

    // if the player has no HP
    if (playerHp <= 0)
    {
        gamePhase = DEATH; // death
    }
    // if the player hasnt attacked greg and has survived enough attacks
    else if (canSpare & attackCount > 9 & gamePhase == ATTACK)
    {
        gamePhase = PACIFISTCUT; // true pacifist ending
        cutsceneClock.restart(); // start cutscene end timer
    }
    // if greg has no HP
    else if (gregHp <= 0 & gamePhase == ATTACK)
    {
        gamePhase = GENOCIDECUT; // genocide ending
        cutsceneClock.restart(); // start cutscene end timer
    }
}

void Application::nextAttack()
{
    attackIndex += 1; // go to next attack
    if (attackIndex > 2)
    {
        attackIndex = ICECREAMVAN;
    }

    attackCount += 1; // add 1 to amount of attacks

    gamePhase = CHOOSE; // go back to player choosing phase

    /* RESET PLAYER POSITION */

    playerSoul.setPosition(sf::Vector2f(310, 380));

    /* RESET POSITIONS OF ATTACKS */

    iceCreamVan.reset();

    iceCone1.reset();
    iceCone2.reset();
    iceCone3.reset();

    pencil1.reset();
    pencil2.reset();
}