#include "obj.h"
#include <cstdlib>

Obstacle::Obstacle() {
    _speed = 200;
}

void Obstacle::setTexture(std::string path) {
    if (_texture.loadFromFile(path)) {
        _sprite.setTexture(_texture, true);}
}

void Obstacle::setPosition(float x, float y) {
    _sprite.setPosition({x, y});}

void Obstacle::update(float dt) {
    _sprite.move({-_speed * dt, 0});}

sf::Rect<float> Obstacle::getRect() const {
    return _sprite.getGlobalBounds();}

sf::Sprite& Obstacle::getSprite() {
    return _sprite;}

void Obstacle::setSpeed(float speed) {
    _speed = speed;}


void spawnObstacle(
    std::vector<std::shared_ptr<Obstacle>>& obstacles,
    bool& waitingForTractor,
    float& TractorWaitTimer,
    float& obstacleTimer,
    float& obstacleInterval,
    float dt
    )
    {
    obstacleTimer += dt;
    float zemlaLevel = 500.0;

    if (waitingForTractor) {
        TractorWaitTimer += dt;
        if (TractorWaitTimer >= 2.0) {
            TractorWaitTimer = 0.0;
            waitingForTractor = false;

            bool spawnTractor_And_CapiAir = (std::rand() % 2 == 0);

            auto ob = std::make_shared<Obstacle>();

            if (spawnTractor_And_CapiAir) {
                ob->setTexture("assets/tractor.png");
                ob->getSprite().setScale(3.5, 3.5);
                ob->setSpeed(400.0);
                auto b = ob->getSprite().getGlobalBounds();
                ob->setPosition(850.0, zemlaLevel - b.height);
            } else {
                ob->setTexture("assets/CapyAir.png");
                ob->getSprite().setScale(2.5, 2.5);
                ob->setSpeed(400.0);

                auto b = ob->getSprite().getGlobalBounds();

                float flightY = zemlaLevel - b.height - 60.0;
                ob->setPosition(850.0, flightY);
            }
            obstacles.push_back(ob);

            obstacleInterval = 1.5 + (std::rand() % 1001) / 1000.0;
            obstacleTimer = 0.0;
        }

        return;
    }

    if (obstacleTimer >= obstacleInterval) {
        obstacleTimer = 0.0;


        int r = std::rand() % 10;

        if (r <= 7) {
            auto ob = std::make_shared<Obstacle>();

            int rTex = std::rand() % 3;
            if (rTex == 0) {
                ob->setTexture("assets/kustik.png");
            } else if (rTex == 1) {
                ob->setTexture("assets/kustik2.png");
            } else {
                ob->setTexture("assets/kustik3.png");
            }

            double kustScale = 1.5 + (std::rand() % 6) * 0.1;
            ob->getSprite().setScale(kustScale, kustScale);
            ob->setSpeed(200.0);

            auto b = ob->getSprite().getGlobalBounds();
            ob->setPosition(850.0, zemlaLevel - b.height);
            obstacles.push_back(ob);

            obstacleInterval = 1.5 + (std::rand() % 101) / 100.0;
        } else {
            waitingForTractor = true;
            TractorWaitTimer = 0.0;
        }
    }
}