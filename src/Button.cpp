#include "Button.h"

bool Button::isClicked(sf::Window &win)
{
    // gets the position of the mouse on the
    // reference passed as parameter 'win'
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);

    // if clicked and delay happened
    if (getGlobalBounds().contains(mousePos.x, mousePos.y) & sf::Mouse::isButtonPressed(sf::Mouse::Left) & clickClock.getElapsedTime().asSeconds() > 0.2)
    {
        clickClock.restart(); // restart click clock

        return true;
    }
    else // if not clicked
    {
        return false;
    }
}