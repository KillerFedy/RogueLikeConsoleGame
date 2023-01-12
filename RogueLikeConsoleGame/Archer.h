#pragma once
#include "GameObject.h"

class Archer : public GameObject {
public:
    Archer(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage);
    void move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<std::string> map) override;
    bool collide(GameObject& gameObject) override;
    bool collide(Player& player) override;
    bool collide(Monster& monster) override;
    bool collide(Archer& archer) override;
private:
    int arrowTick;
    int shotDistance;
    int timer;
};