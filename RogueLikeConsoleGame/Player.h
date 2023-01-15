#pragma once
#include "GameObject.h"

class Player : public GameObject {
public:
    Player(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map) override;
    void heal(int increasedHeal);
    bool collide(Player& player) override;
    bool collide(GameObject& gameObject) override;
    bool collide(Monster& monster) override;
    bool collide(Archer& archer) override;
};