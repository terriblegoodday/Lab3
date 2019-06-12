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
    int16_t x, y, r;
    sf::Color color;
    // Contructors
    Bug();
    Bug(sf::Color color);
    Bug(int16_t xx, int16_t yy, int16_t rr, sf::Color color);
private:
    int dx, dy;
};

#endif /* Bug_hpp */
