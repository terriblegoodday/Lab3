//
//  Bug.hpp
//  Life
//
//  Created by Eduard Dzhumagaliev on 6/5/19.
//  Copyright © 2019 Eduard Dzhumagaliev. All rights reserved.
//

#ifndef Bug_hpp
#define Bug_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Bug {
public:
    sf::CircleShape shape;
    bool isStopped;
    void draw();
    void draw(sf::RenderWindow& window);
    void war(Bug& with);
    bool meet(Bug& with);
    bool dead;
    bool didMultiply;
    void hide();
    void move();
    void stop();
    void move(int dx, int dy);
    void die();
    void rotate();
    int16_t x, y, r, R;
    sf::Color color;
    sf::Color innerColor;
    // Contructors
    Bug();
    Bug(sf::Color color, sf::Color innerColor, int newN);
private:
    std::vector<sf::CircleShape> innerCircles;
    int dx, dy, n, t;
    int seed;
};

#endif /* Bug_hpp */
