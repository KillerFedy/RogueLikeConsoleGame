#include "Game.h"
#include "GameSettings.h"

int main() {
    GameSettings& gameSettings = GameSettings::Instance();
    gameSettings.loadConfig("../res/projectsettings.json");

    while (true) {
        Game game(sf::VideoMode(gameSettings.windowWidth, gameSettings.windowHeight),
            gameSettings.windowName, gameSettings.mapPath);
        if (game.startGame() == WindowState::Close)
            break;
    }

    return 0;
}