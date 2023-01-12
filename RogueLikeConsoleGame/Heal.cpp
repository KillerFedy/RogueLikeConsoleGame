#include "Heal.h"
#include "Player.h"

Heal::Heal(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& increasedHeal) :
    Item(position, sprite), increasedHeal(increasedHeal) {}

bool Heal::collide(Player& player) {
    player.heal(increasedHeal);
    return Item::collide(player);
}