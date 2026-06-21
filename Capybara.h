#ifndef CAPIBARA_CAPIBARA_H
#define CAPIBARA_CAPIBARA_H


#include <string>
#include <SFML/Graphics.hpp>

class Capybara : public sf::Drawable {
    static inline sf::Texture _texture;
    sf::Sprite _sprite;
    float _speedY;
    bool _isJumping;
    bool _isPrised = false;
    sf::Vector2f _normalScale{3.0, 3.0};
    sf::Vector2f _prisedScale{3.0, 2.0};
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    Capybara();
    static void setTexture(std::string path);
    void setPosition(float x, float y);
    void update(float dt, bool prised);
    void jump();
    float getY() const;
    sf::Rect<float> getRect() const;
};
#endif //CAPIBARA_CAPIBARA_H