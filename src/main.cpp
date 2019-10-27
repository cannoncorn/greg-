#include "Application.h"

#define WIDTH 640
#define HEIGHT 640
#define NAME "GregTale"
#define FPS 60

Application game;

int main()
{
    game.create(sf::VideoMode(WIDTH, HEIGHT), NAME, sf::Style::Close);
    game.setFramerateLimit(FPS);

    game.load();

    while (game.isOpen())
    {
        sf::Event event;
        while (game.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                game.close();
            }
        }

        game.updatef();

        game.clear(sf::Color(0, 0, 0));
        game.drawf();
        game.display();
    }
}