#include "HealthBar.h"

HealthBar::HealthBar()
{
    background.setFillColor(sf::Color::Red);
}

void HealthBar::draw(sf::RenderTarget &win)
{
    win.draw(background);

    if (this->getSize().x > 0)
        win.draw(*this);
}

void HealthBar::resize(sf::Vector2f vec)
{
    setSize(vec);
    background.setSize(vec);
}

void HealthBar::place(sf::Vector2f vec)
{
    setPosition(vec);
    background.setPosition(vec);
}

void HealthBar::setDamage(int oldhp, int dmg)
{
    this->setSize(sf::Vector2f((oldhp - dmg) * 2, background.getSize().y));
}