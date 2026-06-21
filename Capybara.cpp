#include "Capybara.h"


Capybara::Capybara() {
    _sprite.setTexture(_texture);
    _sprite.setScale(_normalScale);
    _speedY = 0;
    _isJumping = false;
    _isPrised = false;
}

void Capybara::setTexture(std::string path) {
    _texture.loadFromFile(path);}
void Capybara::setPosition(float x, float y) {
    _sprite.setPosition({x, y});}

void Capybara::update(float dt, bool prised) {
    auto oldBounds = _sprite.getGlobalBounds();
    float oldFeetY = oldBounds.top + oldBounds.height;

    if (prised && !_isPrised) {
        _isPrised = true;
        _sprite.setScale(_prisedScale);
    } else if (!prised && _isPrised) {
        _isPrised = false;
        _sprite.setScale(_normalScale);
    }

    auto newBounds = _sprite.getGlobalBounds();
    float newFeetY = newBounds.top + newBounds.height;

    float dyFeet = oldFeetY - newFeetY;
    _sprite.move(0.0, dyFeet);

    float gravity = 500.0;
    if (prised) {
        gravity += 1000.0;
    }

    _speedY += gravity * dt;
    _sprite.move({0, _speedY * dt});

    float spriteVisota = _sprite.getTexture()->getSize().y * _sprite.getScale().y;
    float nogiY = _sprite.getPosition().y + spriteVisota;
    float zemlaLevel = 500.;

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
    target.draw(_sprite, states);}

float Capybara::getY() const {
    return _sprite.getPosition().y;}

sf::Rect<float> Capybara::getRect() const {
    return _sprite.getGlobalBounds();}