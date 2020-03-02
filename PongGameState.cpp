#include "PongGameState.h"
#include "SFML Game engine/States/StateManager.h"

PongGameState::PongGameState(const sf::Vector2u &windowSize, StateManager& manager) :GameState(windowSize, manager){

}

void PongGameState::drawState(sf::RenderWindow &window){

}

void PongGameState::update(float deltaTime){

}

void PongGameState::pause(){

}

void PongGameState::unpause(){

}

void PongGameState::handleInput(StateManager& manager, const sf::Event& e, const sf::RenderWindow& window){

}
