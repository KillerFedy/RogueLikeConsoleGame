#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

struct Transform {
    int x, y;
    friend const Transform operator+(const Transform& leftPosition, const Transform& rightPosition);
    friend bool operator==(const Transform& leftPosition, const Transform& rightPosition);
    friend bool operator!=(const Transform& leftPosition, const Transform& rightPosition);
};

class Player;
class Monster;
class Archer;

class GameObject {
public:
    GameObject(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void draw(sf::RenderWindow& window);
    Transform getPosition();
    int getHealth();
    int getDamage();
    void hit(const int& damage);
    void changeDamage(const int& damage);
    virtual void move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map) = 0;
    // true - object can move to this point | false - can't
    virtual bool collide(GameObject& gameObject) = 0;
    virtual bool collide(Player& player) = 0;
    virtual bool collide(Monster& monster) = 0;
    virtual bool collide(Archer& archer) = 0;
protected:
    Transform position;
    int health, maxHealth, damage;
private:
    std::shared_ptr<sf::Sprite> spriteRenderer;
};