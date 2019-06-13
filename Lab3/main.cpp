
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
    
    Bug b1(sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), 4, 500);
    Bug b2 (sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), 5, 30);
    
//    for (int i = 0; i < 5; i++) {
//        bugs.push_back(Bug(sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), sf::Color(random() % 255 + 1, random() % 255 + 1, random() % 255 + 1, 255), random() % 15 + 10, random() % 15 + 10));
//    }
//    bugs[0].setdy(0);
//    bugs[0].setdx(5);
    
    b1.setdx(5);
    b1.setdy(0);
    b2.setdx(0);
    b2.setdy(5);
    
    
    // Start the game loop
    
    int t = 0;
    
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
        
        sf::Color colors[5];
        colors[0] = sf::Color::Red;
        colors[1] = sf::Color::Green;
        colors[2] = sf::Color::Blue;
        colors[3] = sf::Color::Cyan;
        colors[4] = sf::Color::Magenta;

//        for (int i = 0; i < bugs.size(); i++) {
//            bugs[i].draw(window);
//            bugs[i].move();
//            bugs[i].rotate();
//            bugs[i].setColors(colors[(t + i) % 5], colors[(t + i + 1) % 5]);
//        }
    
        b1.draw(window);
        b2.draw(window);
        b1.move();
        b2.move();
        b1.rotate();
        b2.rotate();
        b1.setColors(colors[(t) % 5], colors[(t + 1) % 5]);
    
        sf::sleep(sf::seconds(.0016)); // 60 FPS 😎
        
        // Update the window
        window.display();
        
        t++;
    }

    return EXIT_SUCCESS;
}
