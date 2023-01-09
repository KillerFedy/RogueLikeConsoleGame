#pragma once
#include "Item.h"

class Heal : public Item {
public:
    Heal(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& increasedHeal);
    bool collide(Player& player) override;
private:
    int increasedHeal;
};