#include "Capybara.h"


Capybara::Capybara() {
    _sprite.setTexture(_texture);
    _sprite.setScale({3, 3});
    _speedY = 0;
    _isJumping = false;
}

void Capybara::setTexture(std::string path) {
    _texture.loadFromFile(path);
}

void Capybara::setPosition(float x, float y) {
    _sprite.setPosition({x, y});
}

void Capybara::update(float dt) {
    // гравитация
    _speedY += 500 * dt;
    _sprite.move({0, _speedY * dt});

    // высота спрайта с учётом масштаба
    float spriteVisota = _sprite.getTexture()->getSize().y * _sprite.getScale().y;

    // позиция "ног"
    float nogiY = _sprite.getPosition().y + spriteVisota;

    // уровень земли
    float zemlaLevel = 500;

    // если ноги ниже земли — ставим на землю
    if (nogiY > zemlaLevel) {
        float newY = zemlaLevel - spriteVisota;
        _sprite.setPosition({_sprite.getPosition().x, newY});
        _speedY = 0;
        _isJumping = false;
    }
}

void Capybara::jump() {
    if (!_isJumping) {
        _speedY = -400;
        _isJumping = true;
    }
}

void Capybara::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_sprite, states);
}

float Capybara::getY() const {
    return _sprite.getPosition().y;
}

sf::Rect<float> Capybara::getRect() const {
    return _sprite.getGlobalBounds();
}