#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>  
#include <cmath>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#define PI 3.14159265358979323846

void updateArc(sf::ConvexShape& shape, const sf::Vector2f& center, float radius, float startAngle, float endAngle) {
    int pointCount = shape.getPointCount();

    float angleStep = (startAngle <= endAngle)
        ? (endAngle - startAngle) / (pointCount - 2)
        : (360.0f - (startAngle - endAngle)) / (pointCount - 2);

    float angle = startAngle;
    for (int i = 0; i <= pointCount - 2; i++) {
        float radian = angle * (PI / 180.0f);
        shape.setPoint(i + 1, sf::Vector2f(radius * cos(radian), -radius * sin(radian)));
        angle += angleStep;
    }
    shape.setPoint(0, sf::Vector2f(0, 0));
    shape.setFillColor(sf::Color::Yellow);
}

float moveAngleTowardsTarget(float startAngle, float targetAngle, float elapsedTime, float totalTime) {
    float t = elapsedTime / totalTime;
    float differance = targetAngle - startAngle;
    float addedAngel = abs(sin((t * 2 * PI) / 2)) * differance;

    float newAngle = startAngle + addedAngel;
    return newAngle;
}


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Snake", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);


    sf::Clock clock;
    sf::Time timePerFrame = sf::seconds(1.f / 80.f);


    sf::ConvexShape pacMan(50);
    sf::Vector2f center(400, 300);
    pacMan.setPosition(center);
    float radius = 100.f;
    float initialStartAngle = 30.0f;
    float initialEndAngle = 330.0f;
    float mouseOpenAngel = 30;

    float timeDuration = 0.5;

    updateArc(pacMan, center, radius, initialStartAngle, initialEndAngle);


    sf::Clock gameClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                initialStartAngle = 120.f;
                initialEndAngle = 60.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                initialStartAngle = 210.f;
                initialEndAngle = 150.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                initialStartAngle = 300.f;
                initialEndAngle = 240.f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                initialStartAngle = 30.f;
                initialEndAngle = 330.f;
            }
        }

        sf::Time elapsedTime = clock.restart();

        while (elapsedTime > timePerFrame) {

            float time = gameClock.getElapsedTime().asSeconds();

            if (time <= timeDuration) {
                float newAngleStart = moveAngleTowardsTarget(initialStartAngle, initialStartAngle - mouseOpenAngel, time, timeDuration);
                float newAngleEnd = moveAngleTowardsTarget(initialEndAngle, initialEndAngle + mouseOpenAngel, time, timeDuration);
                updateArc(pacMan, center, radius, newAngleStart, newAngleEnd);
            }
            else {
                gameClock.restart();
            }
           
            elapsedTime -= timePerFrame;
        }

        window.clear();

        window.draw(pacMan);

        window.display();
    }

    return 0;
}
