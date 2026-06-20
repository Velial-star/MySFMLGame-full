#ifndef CAPIBARA_OBJ_H
#define CAPIBARA_OBJ_H


#include <string>
#include <SFML/Graphics.hpp>

class Obstacle {
    sf::Sprite _sprite;
    sf::Texture _texture;
    float _speed;

public:

    Obstacle();
    void setTexture(std::string path);
    void setPosition(float x, float y);
    void update(float dt);
    sf::Rect<float> getRect() const;
    sf::Sprite& getSprite();

    void setSpeed(float speed);
};

#endif //CAPIBARA_OBJ_H