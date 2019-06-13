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
    void setdx(int dx);
    void setdy(int dx);
    void repaint();
    void setColor(sf::Color color);
    void setInnerColor(sf::Color color);
    void setColors(sf::Color color, sf::Color innerColor);
    int getdx();
    int getdy();
    int16_t x, y, r, R;
    sf::Color color;
    sf::Color innerColor;
    // Contructors
    Bug(sf::Color color, sf::Color innerColor, int n, int r);
private:
    std::vector<sf::CircleShape> innerCircles;
    int n, t;
    int seed;
    int dx, dy;
};

#endif /* Bug_hpp */
