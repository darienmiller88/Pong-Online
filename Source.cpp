#include <iostream>
#include "TitleState.h"
#include "PongGameState.h"
#include "SFML Game engine/States/StateManager.h"
using namespace std;

int main() {
    sf::Vector2u windowSize(800, 500);
    StateManager manager(windowSize, "Pong");

    manager.pushState(std::make_unique<TitleState>(windowSize, manager));
    manager.runGame();
}