#ifndef CAPIBARA_CAPIBARA_H
#define CAPIBARA_CAPIBARA_H

#include <string>
#include <SFML/Graphics.hpp>

class Capybara : public sf::Drawable {
    static inline sf::Texture _texture; // общая текстура для всех капибар
    sf::Sprite _sprite;
    float _speedY;
    bool _isJumping;

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Capybara();
    static void setTexture(std::string path);
    void setPosition(float x, float y);
    void update(float dt);
    void jump();
    float getY() const;
    sf::Rect<float> getRect() const;
};

#endif //CAPIBARA_CAPIBARA_H