#pragma once
#include "SFML/Graphics.hpp"
#include "Map.h"
#include "GameObject.h"
#include <string>

enum class GameState { Game, Win, Lose };
enum class WindowState { Close, Restart };

class Game {
public:
    Game(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& mapFile);
    WindowState startGame();
private:
    sf::RenderWindow window;
    Map map;
    std::vector<std::shared_ptr<GameObject>> gameObjects;
    std::string getInfoString(GameObject* gameObject);
};