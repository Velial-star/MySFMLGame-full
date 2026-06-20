#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>

#include <ctime>

#include "Capybara.h"
#include "obj.h"

int main() {
    sf::RenderWindow window({800, 600}, "Capibara Jump");

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

    sf::Text collisionText;
    collisionText.setFont(font);
    collisionText.setString("Cosanie");
    collisionText.setCharacterSize(40);
    collisionText.setFillColor(sf::Color::Red);
    collisionText.setPosition(300, 200);

    bool showCollision = false;

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

        // прыжок
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            capibara.jump();
        }

        // создание новых препятствий
        obstacleTimer += dt;
        if (obstacleTimer >= obstacleInterval) {
            obstacleTimer = 0.0f;

            auto obstacle = std::make_shared<Obstacle>();
            obstacle->setTexture("assets/obstacle.png");

            float x = 850; // справа за экраном

            // препятствие всегда на полу:
            // zemlaLevel = 500, высота препятствия ~ 50 (подгони под свою текстуру)
            float y = 500 - 50;

            obstacle->setPosition(x, y);
            obstacles.push_back(obstacle);
        }

        // обновление капибары
        capibara.update(dt);

        // обновление препятствий
        for (auto &ob : obstacles) {
            ob->update(dt);
        }

        // проверка коллизий
        sf::Rect<float> capRect = capibara.getRect();
        showCollision = false;

        for (auto &ob : obstacles) {
            sf::Rect<float> obRect = ob->getRect();
            if (capRect.intersects(obRect)) {
                showCollision = true;
                break;
            }
        }

        // удаление препятствий, ушедших за экран
        obstacles.erase(
            std::remove_if(obstacles.begin(), obstacles.end(),
                           [](const std::shared_ptr<Obstacle> &ob) {
                               return ob->getRect().left < -100.0f;
                           }),
            obstacles.end()
        );

        // рисуем
        window.clear();
        window.draw(zemla);

        for (auto &ob : obstacles) {
            window.draw(ob->getSprite());
        }

        window.draw(capibara);

        if (showCollision) {
            window.draw(collisionText);
        }

        window.display();
    }

    return 0;
}