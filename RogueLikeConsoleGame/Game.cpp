#include "Game.h"
#include "GameSettings.h"
#include "Player.h"

Game::Game(const sf::VideoMode& videoMode, const std::string& windowName, const std::string& mapFile) :
    map(mapFile)
{
    window.create(videoMode, windowName, sf::Style::Close);
}

std::string Game::getInfoString(GameObject* gameObject) {
    return "Health: " + std::to_string(gameObject->getHealth()) + " | " + "Damage: " + std::to_string(gameObject->getDamage());
}

WindowState Game::startGame() {
    GameSettings& gameSettings = GameSettings::Instance();
    GameState gameState = GameState::Game;

    auto mapVec = map.getMap();
    //player in [0]
    auto objects = map.getObjects();
    Player* player = dynamic_cast<Player*>(objects[0].get());

    auto windowSize = window.getSize();
    int mapWidth = mapVec[0].length() * gameSettings.spriteSize;
    int mapHeight = mapVec.size() * gameSettings.spriteSize;
    sf::View camera;
    camera.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));
    sf::View hud;
    hud.reset(sf::FloatRect(0, 0, windowSize.x, windowSize.y));

    sf::Font font;
    font.loadFromFile(gameSettings.fontPath);
    sf::Text healthText("", font, 16);
    healthText.setPosition(5, 0);
    healthText.setString(getInfoString(player));

    sf::Text endText("", font, 100);

    auto playerPos = player->getPosition();

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return WindowState::Close;
            }

            if (gameState == GameState::Win || gameState == GameState::Lose) {
                window.close();
                return WindowState::Restart;
            }

            Transform offset = { 0, 0 };
            bool isMove = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                offset = Transform{ -1, 0 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                offset = Transform{ 1, 0 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                offset = Transform{ 0, -1 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                offset = Transform{ 0, 1 };
                isMove = true;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                isMove = true;
            }

            if (isMove) {
                player->move(offset, objects, mapVec);
                playerPos = player->getPosition();

                for (int i = 1; i < objects.size(); ++i) {
                    objects[i]->move(playerPos, objects, mapVec);
                }

                healthText.setString(getInfoString(player));

                if (player->getHealth() <= 0) {
                    gameState = GameState::Lose;
                    endText.setString("DEAD");
                }
            }

            int i = 0;
            while (i < objects.size()) {
                if (objects[i]->getHealth() <= 0) {
                    objects.erase(objects.begin() + i);
                    continue;
                }
                ++i;
            }
        }

        int camX = playerPos.x * gameSettings.spriteSize, camY = playerPos.y * gameSettings.spriteSize;
        auto cameraSize = camera.getSize();

        if (camX - cameraSize.x / 2 < 0)
            camX = cameraSize.x / 2;
        else if (camX + cameraSize.x / 2 > mapWidth)
            camX = mapWidth - cameraSize.x / 2;

        if (camY - cameraSize.y / 2 < 0)
            camY = cameraSize.y / 2;
        else if (camY + cameraSize.y / 2 > mapHeight)
            camY = mapHeight - cameraSize.y / 2;

        camera.setCenter(camX, camY);
        window.setView(camera);

        window.clear(sf::Color::Black);

        window.setView(camera);
        map.draw(window);
        for (int i = 0; i < objects.size(); ++i)
            objects[i]->draw(window);

        window.setView(hud);
        window.draw(healthText);
        if (gameState == GameState::Win || gameState == GameState::Lose) {
            auto bounds = endText.getLocalBounds();
            endText.setPosition(windowSize.x / 2 - bounds.width / 2, windowSize.y / 2 - bounds.height / 2);
            window.draw(endText);
        }

        window.display();

        if (gameState == GameState::Win || gameState == GameState::Lose)
            sf::sleep(sf::seconds(1));
    }
}