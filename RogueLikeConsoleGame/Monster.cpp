#include "Monster.h"
#include "Player.h"
#include <ctime>
#include <cmath>

Monster::Monster(const Transform& position, const std::shared_ptr<sf::Sprite> sprite, const int& health, const int& damage) : GameObject(position, sprite, health, damage) {}

void Monster::move(const Transform& targetPosition, std::vector<std::shared_ptr<GameObject>>& objects, const std::vector<std::string> map)
{
    int playerVizible = 5;

    int distToPlayer = sqrt(pow(targetPosition.x - position.x, 2) + pow(targetPosition.y - position.y, 2));
    Transform toPos;
    if (distToPlayer <= playerVizible) {
        int dx = targetPosition.x - position.x;
        int dy = targetPosition.y - position.y;
        if (dx < 0)
        {
            dx = -1;
        }
        else if(dx > 0)
        {
            dx = 1;
        }
        if (dy < 0)
        {
            dy = -1;
        }
        else if (dy > 0)
        {
            dy = 1;
        }

        if (dx == 0)
            toPos = position + Transform{ 0, dy };
        else if (dy == 0)
            toPos = position + Transform{ dx, 0 };
        else {
            int index = rand() % 2;
            toPos = index == 0 ? position + Transform{ dx, 0 } : position + Transform{ 0, dy };
        }
    }
    else {
        Transform offsets[] = { Transform{1, 0}, Transform{-1, 0}, Transform{0, 1}, Transform{0, -1} };
        srand(time(0));
        int index = rand() % 4;
        toPos = position + offsets[index];
    }

    bool isCollide = false;

    for (int i = 0; i < objects.size(); ++i) {
        if (toPos == objects[i]->getPosition())
        {
            if (!objects[i]->collide(*this)) {
                isCollide = true;
            }
        }
    }

    if (!isCollide && map[toPos.y][toPos.x] == '.')
        position = toPos;
}

bool Monster::collide(GameObject& gameObject) {
    return gameObject.collide(*this);
}

bool Monster::collide(Player& player) {
    health -= player.getDamage();
    return false;
}

bool Monster::collide(Monster& monster) {
    return false;
}

bool Monster::collide(Archer& archer) {
    return false;
}