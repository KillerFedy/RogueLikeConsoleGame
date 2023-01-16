#include "Archer.h"
#include "player.h"
#include <cmath>


Archer::Archer(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage), arrowTick(0), timer(5), shotDistance(6) {}

void Archer::move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map)
{
    
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
