#include "Button.h"

using namespace std;

bool Button::isClicked(sf::Window &win)
{
    // gets the position of the mouse on the
    // reference passed as parameter 'win'
    sf::Vector2i mousePos = sf::Mouse::getPosition(win);

    cout << clock.getElapsedTime().asSeconds() << endl;

    // if clicked and delay happened
    if (getGlobalBounds().contains(mousePos.x, mousePos.y) & sf::Mouse::isButtonPressed(sf::Mouse::Left) & clock.getElapsedTime().asSeconds() > 0.2)
    {
        clock.restart(); // restart click clock

        return true;
    }
    else // if not clicked
    {
        return false;
    }
}