#include "Map.h"
#include "GameSettings.h"
#include "Player.h"
#include "Monster.h"
#include "Archer.h"
#include "Heal.h"
#include "Sword.h"
#include <fstream>

Map::Map(const std::string& mapFile) {
    GameSettings& gameSettings = GameSettings::Instance();
    std::ifstream file(gameSettings.mapPath);

    std::string line;
    while (!file.eof()) {
        std::getline(file, line);
        map.push_back(line);
    }
    file.close();

    tileSet.loadFromFile(gameSettings.tileSetPath);

    empty = std::make_shared<sf::Sprite>(tileSet);
    empty->setTextureRect(sf::IntRect(0, 0, gameSettings.spriteSize, gameSettings.spriteSize));
    empty->setColor(sf::Color(0, 255, 0));

    wall = std::make_shared<sf::Sprite>(tileSet);
    wall->setTextureRect(sf::IntRect(16, 0, gameSettings.spriteSize, gameSettings.spriteSize));

    auto playerSprite = std::make_shared<sf::Sprite>(tileSet);
    playerSprite->setTextureRect(sf::IntRect(16*3, 16 * 19, gameSettings.spriteSize, gameSettings.spriteSize));

    auto monsterSprite = std::make_shared<sf::Sprite>(tileSet);
    monsterSprite->setTextureRect(sf::IntRect(16 * 3, 16 * 20, gameSettings.spriteSize, gameSettings.spriteSize));

    auto archerSprite = std::make_shared<sf::Sprite>(tileSet);
    archerSprite->setTextureRect(sf::IntRect(16 * 2, 16 * 19, gameSettings.spriteSize, gameSettings.spriteSize));

    auto healSprite = std::make_shared<sf::Sprite>(tileSet);
    healSprite->setTextureRect(sf::IntRect(16*6, 16*9, gameSettings.spriteSize, gameSettings.spriteSize));

    auto swordSprite = std::make_shared<sf::Sprite>(tileSet);
    swordSprite->setTextureRect(sf::IntRect(16*3, 16*13, gameSettings.spriteSize, gameSettings.spriteSize));


    std::shared_ptr<GameObject> player;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            bool isObject = false;

            if (map[i][j] == gameSettings.gameObjects["player"]) {
                player = std::make_shared<Player>(Transform{ j, i }, playerSprite, 100, 20);
                gameObjects.push_back(player);
                isObject = true;
            }
            else if (map[i][j] == gameSettings.gameObjects["monster"]) {
                gameObjects.push_back(std::make_shared<Monster>(Transform{ j, i }, monsterSprite, 60, 10));
                isObject = true;
            }
            else if (map[i][j] == gameSettings.gameObjects["archer"]) {
                gameObjects.push_back(std::make_shared<Archer>(Transform{ j, i }, archerSprite, 20, 10));
                isObject = true;
            }
            else if (map[i][j] == gameSettings.gameObjects["heal"]) {
                gameObjects.push_back(std::make_shared<Heal>(Transform{ j, i }, healSprite, 20));
                isObject = true;
            }
            else if (map[i][j] == gameSettings.gameObjects["sword"]) {
                gameObjects.push_back(std::make_shared<Sword>(Transform{ j, i }, swordSprite, 40));
                isObject = true;
            }

            if (isObject)
                map[i][j] = '.';
        }
    }

    for (int i = 0; i < gameObjects.size(); ++i)
        if (gameObjects[i] == player) {
            gameObjects.erase(gameObjects.begin() + i);
            break;
        }

    gameObjects.insert(gameObjects.begin(), player);
}

void Map::draw(sf::RenderWindow& window) {
    GameSettings& gameSettings = GameSettings::Instance();

    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].length(); ++j) {
            if (map[i][j] == gameSettings.gameObjects["empty"]) {
                empty->setPosition(sf::Vector2f(j * gameSettings.spriteSize, i * gameSettings.spriteSize));
                window.draw(*empty);
            }
            else if (map[i][j] == gameSettings.gameObjects["wall"]) {
                wall->setPosition(sf::Vector2f(j * gameSettings.spriteSize, i * gameSettings.spriteSize));
                window.draw(*wall);
            }
        }
    }
}

std::vector<std::shared_ptr<GameObject>>& Map::getObjects() {
    return gameObjects;
}

std::vector<std::string>& Map::getMap() {
    return map;
}
