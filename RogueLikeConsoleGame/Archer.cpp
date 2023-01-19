#include "Archer.h"
#include "Player.h"
#include <cmath>


Archer::Archer(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage), shotDistance(6) { }

void Archer::move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map)
{
    int distance = (int)sqrt(pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2));
    if (distance <= shotDistance)
    {
        //player.hit(damage);
        gameObjects[0].get()->hit(damage);
    }
}

bool Archer::collide(GameObject& gameObject) {
    return gameObject.collide(*this);
}

bool Archer::collide(Player& player) {
    health -= player.getDamage();
    return false;
}

bool Archer::collide(Monster& monster) {
    return false;
}

bool Archer::collide(Archer& archer) {
    return false;
}
