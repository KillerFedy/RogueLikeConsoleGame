#include "Player.h"
#include "Monster.h"

Player::Player(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}


void Player::move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map)
{
    Transform targetPos = position + targetPosition;
    bool isCollide = false;

    for (int i = 0; i < gameObjects.size(); ++i) {
        if (targetPos == gameObjects[i]->getPosition())
            if (!gameObjects[i]->collide(*this)) {
                isCollide = true;
            }
    }

    if (!isCollide && map[targetPos.y][targetPos.x] == '.')
        position = targetPos;
}

void Player::heal(int increasedHeal) {
    health += increasedHeal;
    health = health > maxHealth ? maxHealth : health;
}


bool Player::collide(GameObject& gameObject) {
    return gameObject.collide(*this);
}

bool Player::collide(Archer& archer) {
    return false;
}

bool Player::collide(Monster& monster) {
    health -= monster.getDamage();
    return false;
}

bool Player::collide(Player& player) {
    return false;
}
