#include "GameObject.h"
#include "GameSettings.h"

const Transform operator+(const Transform& leftPosition, const Transform& rightPosition) {
    return Transform{ leftPosition.x + rightPosition.x, leftPosition.y + rightPosition.y };
}

bool operator==(const Transform& leftPosition, const Transform& rightPosition) {
    return leftPosition.x == rightPosition.x && leftPosition.y == rightPosition.y;
}

bool operator!=(const Transform& leftPosition, const Transform& rightPosition) {
    return leftPosition.x != rightPosition.x || leftPosition.y != rightPosition.y;
}

GameObject::GameObject(const Transform& position, std::shared_ptr<sf::Sprite> sprite, const int& health,
    const int& damage) : position(position), spriteRenderer(sprite), health(health), maxHealth(health), damage(damage)
{}

void GameObject::draw(sf::RenderWindow& window) {
    GameSettings& gameSettings = GameSettings::Instance();
    spriteRenderer->setPosition(sf::Vector2f(position.x * gameSettings.spriteSize,
        position.y * gameSettings.spriteSize));

    window.draw(*spriteRenderer);
}

Transform GameObject::getPosition() {
    return position;
}

int GameObject::getHealth() {
    return health;
}

int GameObject::getDamage() {
    return damage;
}

void GameObject::hit(const int& damageSize) {
    if (damageSize > 0)
        health -= damageSize;
}

void GameObject::changeDamage(const int& incSize) {
    damage += incSize;
}