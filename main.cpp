#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include <ctime>

#include "Capybara.h"
#include "obj.h"

int main() {
    sf::RenderWindow window({800, 600}, "Capibara Jump");

    bool gameOver = false; // игра окончена или нет

    // текстура капибары
    Capybara::setTexture("assets/capibara.png");
    Capybara capibara;
    capibara.setPosition(100, 400);


    // пол
    sf::RectangleShape zemla;
    zemla.setSize({800, 20});
    zemla.setFillColor(sf::Color(128, 128, 128));
    zemla.setPosition({0, 500});

    // список препятствий
    std::vector<std::shared_ptr<Obstacle>> obstacles;

    // таймер для появления новых препятствий
    float obstacleTimer = 0.0f;
    float obstacleInterval = 2.0f; // одно препятствие каждые 2 секунды

    // текст "КОСАНИЕ"
    sf::Font font;
    if (!font.loadFromFile("assets/ofont.ru_Patefon.ttf")) {
        std::cout << "Не удалось загрузить шрифт assets/Pulserifleacadi.ttf\n";
    }


    //текст гейм овер
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER\nPress R to restart");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(200, 200);


    sf::Clock clock;

    // рандом (на будущее, если захочешь разную высоту и т.п.)
    std::srand(static_cast<unsigned>(time(nullptr)));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        // обработка ввода
        // прыжок - только если игра не окончена
        if (!gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            capibara.jump();
        }

        // рестарт игры по R, если игра окончена
        if (gameOver && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
            // сброс состояния игры
            gameOver = false;
            obstacles.clear();

            // вернуть капибару на стартовую позицию
            capibara.setPosition(100, 400);

            // сброс таймера препятствий
            obstacleTimer = 0.0f;

            // сброс часов, чтобы dt не прыгнул
            clock.restart();
        }


        if (!gameOver) {
            // прыжок уже обрабатывается выше

            // создание новых препятствий
            obstacleTimer += dt;
            if (obstacleTimer >= obstacleInterval) {
                obstacleTimer = 0.0f;

                auto obstacle = std::make_shared<Obstacle>();
                obstacle->setTexture("assets/obstacle.png");

                float x = 850; // справа за экраном
                float y = 500 - 50; // на полу
                obstacle->setPosition(x, y);
                obstacles.push_back(obstacle);
            }

            // обновление капибары
            capibara.update(dt);

            // обновление препятствий
            for (auto &ob : obstacles) {
                ob->update(dt);
            }

            // удаление препятствий, ушедших за экран
            obstacles.erase(
                std::remove_if(obstacles.begin(), obstacles.end(),
                               [](const std::shared_ptr<Obstacle> &ob) {
                                   return ob->getRect().left < -100.0f;
                               }),
                obstacles.end()
            );
        }

        // проверка коллизий
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



        // рисуем
        window.clear();
        window.draw(zemla);

        for (auto &ob : obstacles) {
            window.draw(ob->getSprite());
        }

        window.draw(capibara);



        // если игра окончена — показываем экран проигрыша
        if (gameOver) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}