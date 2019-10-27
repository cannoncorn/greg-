#include "HealthBar.h"

HealthBar::HealthBar()
{
    // the background is red
    background.setFillColor(sf::Color::Red);
}

void HealthBar::draw(sf::RenderTarget &win)
{
    // draws both this and bg to target win
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
    int scaleFactor = this->getSize().x / oldhp;
    this->setSize(sf::Vector2f(this->getSize().x - dmg * scaleFactor, background.getSize().y));
}