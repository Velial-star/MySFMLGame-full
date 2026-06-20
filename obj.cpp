#include "obj.h"


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

sf::Sprite Obstacle::getSprite() {
    return _sprite;
}