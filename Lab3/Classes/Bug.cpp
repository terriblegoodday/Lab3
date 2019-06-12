//
//  Bug.cpp
//  Life
//
//  Created by Eduard Dzhumagaliev on 6/5/19.
//  Copyright © 2019 Eduard Dzhumagaliev. All rights reserved.
//

#include "Bug.hpp"
#include "Colony.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "global.hpp"


Bug::Bug() {
    x = (random() % 500) + 1;
    y = (random() % 400) + 1;
    r = (random() % 50) + 1;
    
    if ((x > WINDOWWIDTH) || (x <= 0)) {
        x = (int)WINDOWWIDTH / 2;
    };
    if ((y > WINDOWHEIGHT) || (y <= 0)) {
        y = (int)WINDOWHEIGHT / 2;
    };
    if ((r < 25) || (r > (int)WINDOWHEIGHT / 2)) {
        r = 25;
    };
    if ((x < r) || (y < r) || (x + r > WINDOWWIDTH) || (y + r) > WINDOWHEIGHT) {
        x = (int)WINDOWWIDTH / 2;
        y = (int)WINDOWHEIGHT / 2;
    };
    
    color = sf::Color::Red;
    dx = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    draw();
    dead = false;
    isStopped = false;
    std::cout << "Drew a bug";
    didMultiply = false;
};


Bug::Bug(int16_t xx, int16_t yy, int16_t rr, sf::Color newColor) {
    if ((xx > WINDOWWIDTH) || (xx <= 0)) {
        xx = (int)WINDOWWIDTH / 2;
    };
    if ((yy > WINDOWHEIGHT) || (yy <= 0)) {
        yy = (int)WINDOWHEIGHT / 2;
    };
    if ((rr < 10) || (rr > (int)WINDOWHEIGHT / 2) || (rr > (int)WINDOWWIDTH / 2)) {
        rr = 10;
    };
    if ((xx < rr) || (yy < rr) || ((xx + rr) > WINDOWWIDTH) || ((yy + rr) > WINDOWHEIGHT)) {
        xx = (int)WINDOWWIDTH / 2;
        yy = (int)WINDOWHEIGHT / 2;
    };
    x = xx;
    y = yy;
    r = rr;
    color = newColor;
    dx = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    didMultiply = false;
    dead = false;
    isStopped = false;
    draw();
};

Bug::Bug(sf::Color newColor) {
    x = (random() % WINDOWWIDTH) + 1;
    y = (random() % WINDOWHEIGHT) + 1;
    r = (random() % 50) + 1;
    
    if ((x > WINDOWWIDTH) || (x <= 0)) {
        x = (int)WINDOWWIDTH / 2;
    };
    if ((y > WINDOWHEIGHT) || (y <= 0)) {
        y = (int)WINDOWHEIGHT / 2;
    };
    if ((r < 25) || (r > (int)WINDOWHEIGHT / 2)) {
        r = 25;
    };
    if ((x < r) || (y < r) || (x + r > WINDOWWIDTH) || (y + r) > WINDOWHEIGHT) {
        x = (int)WINDOWWIDTH / 2;
        y = (int)WINDOWHEIGHT / 2;
    };
    
    color = sf::Color::Red;
    dx = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 10) + 1);
    color = newColor;
    didMultiply = false;
    dead = false;
    isStopped = false;
    draw();
}

void Bug::draw() {
    shape.setRadius(r);
    shape.setFillColor(color);
    shape.setPosition(x, y);
}

void Bug::draw(sf::RenderWindow& window) {
    if (!dead) {
        window.draw(shape);
    } else {
        std::cout << "i'm dead" << std::endl;
    }

}

void Bug::move() {
    if (!dead && !isStopped)
    {sf::Vector2f currentPosition = shape.getPosition();
        
        if (currentPosition.y - shape.getRadius() / 2 < 0) {
            dy = -dy;
        };
        if (currentPosition.x - shape.getRadius() / 2 < 0) {
            dx = -dx;
        };
        if (currentPosition.y + shape.getRadius() * 2 > WINDOWHEIGHT) {
            dy = -dy;
        };
        if (currentPosition.x + shape.getRadius() * 2 > WINDOWWIDTH) {
            dx = -dx;
        };
        move(dx, dy);}
}

bool Bug::meet(Bug& with) {
    sf::Vector2f pos1 = shape.getPosition();
    sf::Vector2f pos2 = with.shape.getPosition();
    int r1 = r; int r2 = with.r;
    float d = std::sqrt(std::pow((pos1.x - pos2.x), 2) + std::pow(pos1.y - pos2.y, 2));
    if (d < (r1 + r2)) {
        return true;
    };
    return false;
}

void Bug::move(int dx, int dy) {
    shape.move(dx, dy);
}

void Bug::war(Bug& with) {
    if (meet(with) && color != with.color)  {
        if (r < with.r) {
            die();
        } else {
            with.die();
        }
    }
}

void Bug::die() {
    dead = true;
}

void Bug::stop() {
    dx = 0; dy = 0;
}
