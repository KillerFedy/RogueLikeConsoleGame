#include "Sword.h"
#include "Player.h"

Sword::Sword(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& damage) :
    Item(position, sprite), damage(damage) {}

bool Sword::collide(Player& player) {
    player.changeDamage(damage);
    return Item::collide(player);
}