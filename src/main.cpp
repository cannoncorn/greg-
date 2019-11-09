#include "Application.h"

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

/* Constants for game information */
#define WIDTH 640
#define HEIGHT 640
#define NAME "GregTale"
#define FPS 60

int main()
{
#ifdef _WIN32
    FreeConsole();
#endif // _WIN32

    // the main instance
    Application game;

    game.create(sf::VideoMode(WIDTH, HEIGHT), NAME, sf::Style::Close);
    game.setFramerateLimit(FPS);

    game.load(); // run frame 1 game loading code

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

        // class update before drawing to the screen
        game.updatef();

        game.clear(sf::Color(0, 0, 0)); // clear the screen
        game.drawf(); // draw sprites and shapes to the screen
        game.display(); // update display
    }
}