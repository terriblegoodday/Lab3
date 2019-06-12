
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Bug.hpp"
#include "global.hpp"

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Your Life is a Circle");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    std::vector<Bug> bugs;
    for (int i = 0; i < 15; i++) {
        bugs.push_back(Bug(sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), random() % 15 + 10));
    }
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        for (auto &bug: bugs) {
            bug.draw(window);
            bug.move();
            bug.rotate();
        }
        
        sf::sleep(sf::seconds(.0016)); // 60 FPS
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
