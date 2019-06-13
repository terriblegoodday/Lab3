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

Bug::Bug(sf::Color newColor, sf::Color newInnerColor, int n, int r) {
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
    this->n = n;
    dx = ((rand() % 1) - 1) * ((rand() % 5) + 1);
    dy = ((rand() % 1) - 1) * ((rand() % 5) + 1);
    seed = (rand() % 4 + 10);
    draw();
    dead = false;
    isStopped = false;
    didMultiply = false;
}

void Bug::draw() {
    shape.setRadius(R);
    shape.setOutlineThickness(3);
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
        innerCircles[i].setPosition(currentPosition.x + cx + R - p, currentPosition.y + R + cy - p);
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

void Bug::repaint() {
    shape.setOutlineColor(color);
    for (auto &innerCircle: innerCircles) {
        innerCircle.setOutlineColor(innerColor);
    }
}

void Bug::die() {
    dead = true;
}

void Bug::stop() {
    dx = 0; dy = 0;
}

void Bug::setdx(int dx) {
    if (dx >= -15 or dx <= 15) this->dx = dx;
}

void Bug::setdy(int dy) {
    if (dy >= -15 or dy <= 15) this->dy = dy;
}

int Bug::getdx() {
    return this->dx;
}

int Bug::getdy () {
    return this->dy;
}

void Bug::setColor(sf::Color color) {
    this->color = color;
    this->repaint();
}

void Bug::setInnerColor(sf::Color color) {
    this->innerColor = color;
    this->repaint();
}

void Bug::setColors(sf::Color color, sf::Color innerColor) {
    this->color = color;
    this->innerColor = innerColor;
    this->repaint();
}
