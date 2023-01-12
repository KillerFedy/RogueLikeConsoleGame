#include "Item.h"

Item::Item(const Transform& position, const std::shared_ptr<sf::Sprite> sprite)
    : GameObject(position, sprite, 1, 0) {}

void Item::move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects,
    const std::vector<std::string> map) {}

bool Item::collide(GameObject& gameObject) {
    return gameObject.collide(*this);
}

bool Item::collide(Player& player) {
    health = 0;
    return true;
}

bool Item::collide(Monster& monster) {
    return false;
}

bool Item::collide(Archer& archer) {
    return false;
}