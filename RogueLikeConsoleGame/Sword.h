#pragma once
#include "Item.h"

class Sword : public Item {
public:
    Sword(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& damage);
    bool collide(Player& player) override;
private:
    int damage;
};