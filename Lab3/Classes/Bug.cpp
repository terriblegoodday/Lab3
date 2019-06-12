//
//  Bug.cpp
//  Life
//
//  Created by Eduard Dzhumagaliev on 6/5/19.
//  Copyright © 2019 Eduard Dzhumagaliev. All rights reserved.
//

#include "Bug.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "global.hpp"
#include <math.h>


Bug::Bug() {
    x = (random() % 500) + 1;
    y = (random() % 400) + 1;
    n = 10;
    R = 100;
    
    if ((x > WINDOWWIDTH) || (x <= 0)) {
        x = (int)WINDOWWIDTH / 2;
    };
    if ((y > WINDOWHEIGHT) || (y <= 0)) {
        y = (int)WINDOWHEIGHT / 2;
    };
    if ((R < 25) || (R > (int)WINDOWHEIGHT / 2)) {
        R = 25;
    };
    if ((x < R) || (y < R) || (x + R > WINDOWWIDTH) || (y + R) > WINDOWHEIGHT) {
        x = (int)WINDOWWIDTH / 2;
        y = (int)WINDOWHEIGHT / 2;
    };
    
    color = sf::Color::Red;
    innerColor = sf::Color::Blue;
    dx = ((rand() % 1) - 1) * ((rand() % 25) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 25) + 1);
    draw();
    dead = false;
    seed = (rand() % 10 + 1);
    isStopped = false;
    std::cout << "Drew a bug";
    didMultiply = false;
};

Bug::Bug(sf::Color newColor, sf::Color newInnerColor, int newN) {
    x = (random() % (WINDOWWIDTH - 400)) + 1;
    y = (random() % (WINDOWHEIGHT - 400)) + 1;
    R = (random() % 50) + 100;
    
    if ((x > WINDOWWIDTH) || (x <= 0)) {
        x = (int)WINDOWWIDTH / 2;
    };
    if ((y > WINDOWHEIGHT) || (y <= 0)) {
        y = (int)WINDOWHEIGHT / 2;
    };
    if ((R < 25) || (R > (int)WINDOWHEIGHT / 2)) {
        R = 25;
    };
    if ((x < R) || (y < R) || (x + R > WINDOWWIDTH) || (y + R) > WINDOWHEIGHT) {
        x = (int)WINDOWWIDTH / 2;
        y = (int)WINDOWHEIGHT / 2;
    };
    
    color = newColor;
    innerColor = newInnerColor;
    n = newN;
    dx = ((rand() % 1) - 1) * ((rand() % 5) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 5) + 1);
    seed = (rand() % 10 + 1);
    draw();
    dead = false;
    isStopped = false;
    didMultiply = false;
}

void Bug::draw() {
    shape.setRadius(R);
    shape.setOutlineThickness(1);
    shape.setOutlineColor(color);
    shape.setFillColor(sf::Color::Transparent);
    shape.setPosition(x, y);
    
    float phi = M_PI / n; // an angle between two circles
    float r = R * (1-sin(phi)) / (1+sin(phi)); // radius of an inner circle
    float p = r * sin(phi) / (1-sin(phi)); // radius of p of the the steiner chain circles
    
    for (int i = 0; i < n; i++) {
        float cx = cos(2*phi*(i+1) + (t)/4) * (r + p);
        float cy = sin(2*phi*(i+1) + (t)/4) * (r + p);
        sf::Vector2f currentPosition = shape.getPosition();
        sf::Vector2f origin = shape.getOrigin();
        sf::CircleShape circle = sf::CircleShape(p);
        circle.setOutlineThickness(3);
        circle.setOutlineColor(innerColor);
        circle.setFillColor(sf::Color::Transparent);
        circle.setPosition(currentPosition.x + cx + R - p, currentPosition.y + R + cy - p);
        circle.setRadius(p);
        innerCircles.push_back(circle);
    };
    t++;
    
}

void Bug::draw(sf::RenderWindow& window) {
    
    for (auto &shape: innerCircles) {
        window.draw(shape);
    }
    window.draw(shape);

}

void Bug::move() {
    if (!dead && !isStopped)
    {sf::Vector2f currentPosition = shape.getPosition();
        
        if (currentPosition.y < 0) {
            dy = -dy;
        };
        if (currentPosition.x < 0) {
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

void Bug::rotate() {
    float phi = M_PI / n; // an angle between two circles
    float r = R * (1-sin(phi)) / (1+sin(phi)); // radius of an inner circle
    float p = r * sin(phi) / (1-sin(phi)); // radius of p of the the steiner chain circles
    
    for (int i = 0; i < n; i++) {
        float k = p * seed;
        float cx = cos(2*phi*(i+1) + t/k) * (r + p);
        float cy = sin(2*phi*(i+1) + t/k) * (r + p);
        sf::Vector2f currentPosition = shape.getPosition();
        sf::Vector2f origin = shape.getOrigin();
        sf::CircleShape circle = sf::CircleShape(p);
        innerCircles[i].setOutlineThickness(3);
        innerCircles[i].setOutlineColor(innerColor);
        innerCircles[i].setFillColor(sf::Color::Transparent);
        innerCircles[i].setPosition(currentPosition.x + cx + R - p, currentPosition.y + R + cy - p);
        innerCircles[i].setRadius(p);
    };
    t++;
}

bool Bug::meet(Bug& with) {
    sf::Vector2f pos1 = shape.getPosition();
    sf::Vector2f pos2 = with.shape.getPosition();
    int R1 = R; int R2 = with.R;
    float d = std::sqrt(std::pow((pos1.x - pos2.x), 2) + std::pow(pos1.y - pos2.y, 2));
    if (d < (R1 + R2)) {
        return true;
    };
    return false;
}

void Bug::move(int dx, int dy) {
    shape.move(dx, dy);
    for (auto &shape: innerCircles) {
        shape.move(dx, dy);
    }
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
