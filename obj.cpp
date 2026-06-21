#include "obj.h"
#include <cstdlib>

Obstacle::Obstacle() {
    _speed = 200; // скорость влево в пикселях/сек
}

void Obstacle::setTexture(std::string path) {
    if (_texture.loadFromFile(path)) {
        _sprite.setTexture(_texture, true); // true — обновить размер по текстуре
    }
}

void Obstacle::setPosition(float x, float y) {
    _sprite.setPosition({x, y});
}

void Obstacle::update(float dt) {
    _sprite.move({-_speed * dt, 0});
}

sf::Rect<float> Obstacle::getRect() const {
    return _sprite.getGlobalBounds();
}

sf::Sprite& Obstacle::getSprite() {
    return _sprite;
}

void Obstacle::setSpeed(float speed) {
    _speed = speed;
}


void spawnObstacle(
    std::vector<std::shared_ptr<Obstacle>>& obstacles,
    bool& waitingForTractor,
    float& TractorWaitTimer,
    float& obstacleTimer,
    float& obstacleInterval,
    float dt
) {
    obstacleTimer += dt;
    float zemlaLevel = 500.0f;

    if (waitingForTractor) {
        // 2 секунды тишины перед машинкой
        TractorWaitTimer += dt;
        if (TractorWaitTimer >= 2.0) {
            TractorWaitTimer = 0.0;
            waitingForTractor = false;

            auto ob = std::make_shared<Obstacle>();
            ob->setTexture("assets/tractor.png");
            ob->getSprite().setScale(3.5, 3.5);
            ob->setSpeed(400.0f);

            auto b = ob->getSprite().getGlobalBounds();
            ob->setPosition(850.0f, zemlaLevel - b.height);
            obstacles.push_back(ob);

            obstacleInterval = 1.5 + (std::rand() % 1001) / 1000.0;
            obstacleTimer = 0.0f;
        }
    } else if (obstacleTimer >= obstacleInterval) {
        obstacleTimer = 0.0f;

        int r = std::rand() % 11; // 0..10 [web:329][web:331]

        if (r <= 9) {
            // куст
            auto ob = std::make_shared<Obstacle>();
            ob->setTexture("assets/kustik.png");
            double kustScale = 1.5 + (std::rand() % 6)*0.1;
            ob->getSprite().setScale(kustScale, kustScale);
            ob->setSpeed(200.0f);

            auto b = ob->getSprite().getGlobalBounds();
            ob->setPosition(850.0f, zemlaLevel - b.height);
            obstacles.push_back(ob);

            obstacleInterval = 1.5f + (std::rand() % 1001) / 1000.0f;
        } else {

            waitingForTractor = true;
            TractorWaitTimer = 0.0f;
        }
    }
}