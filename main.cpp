#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include "Capybara.h"
#include "obj.h"

int main() {
    sf::RenderWindow window({800, 600}, "Capibara Jump");

    bool gameOver = false;

    Capybara::setTexture("assets/capibara.png");
    Capybara capibara;
    capibara.setPosition(100, 400);


    sf::RectangleShape zemla;
    zemla.setSize({800, 20});
    zemla.setFillColor(sf::Color(128, 128, 128));
    zemla.setPosition({0, 500});

    std::vector<std::shared_ptr<Obstacle>> obstacles;

    float obstacleTimer = 0.0;
    float obstacleInterval = 2.0;
    bool waitingForTractor = false;
    float TractorWaitTimer = 0.0;

    sf::Font font;
    font.loadFromFile("assets/ofont.ru_Patefon.ttf");

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(200, 200);

    sf::Clock clock;

    std::srand(static_cast<unsigned>(time(nullptr)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            gameOver = false;
            obstacles.clear();
            capibara.setPosition(100, 400);
            obstacleTimer = 0.0;
            clock.restart();
        }

        if (!gameOver) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                capibara.jump();
            }

            bool prised = sf::Keyboard::isKeyPressed(sf::Keyboard::S);

            spawnObstacle(obstacles, waitingForTractor, TractorWaitTimer,
                          obstacleTimer, obstacleInterval, dt);

            capibara.update(dt, prised);
            for (auto &ob : obstacles) {
                ob->update(dt);
            }

            obstacles.erase(
                std::remove_if(obstacles.begin(), obstacles.end(),
                               [](const std::shared_ptr<Obstacle> &ob) {
                                   return ob->getRect().left < -200.0;
                               }),
                obstacles.end()
            );
        }

        sf::Rect<float> capRect = capibara.getRect();

        if (!gameOver) {
            for (auto &ob : obstacles) {
                sf::Rect<float> obRect = ob->getRect();
                if (capRect.intersects(obRect)) {
                    gameOver = true; // игра окончена
                    break;
                }
            }
        }

        for (auto &ob : obstacles) {
            window.draw(ob->getSprite());
        }

        if (gameOver) {
            window.draw(gameOverText);
        }

        window.clear();
        window.draw(zemla);
        window.draw(capibara);
        window.display();
    }

    return 0;
}