#pragma once
#include "GameObject.h"
#include <memory>
#include <vector>
#include <string>

class Map {
public:
    Map(const std::string& mapFile);
    void draw(sf::RenderWindow& window);
    std::vector<std::shared_ptr<GameObject>>& getObjects();
    std::vector<std::string>& getMap();
private:
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::vector<std::string> map;
    sf::Texture tileSet;
    std::shared_ptr<sf::Sprite> empty, wall;
};