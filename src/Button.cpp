#include "Button.h"

bool Button::isClicked(sf::Window &win)
{
    /*
        gets the position of the mouse on the
        reference passed as parameter 'win'
    */
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);

    if (getGlobalBounds().contains(mousePos.x, mousePos.y) & sf::Mouse::isButtonPressed(sf::Mouse::Left)) // clicked
        return true;
    else // not clicked
        return false;
}